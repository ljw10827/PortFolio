using System.Collections;
using System.Collections.Generic;
using UnityEngine;
using System.IO;
using System.Runtime.Serialization.Formatters.Binary;

public class CEnemyStorage : CSingleton<CEnemyStorage>
{
	[System.Serializable]
	public struct STEnemyInfo
	{
		public int m_nID;
		public string m_oName;
		public int m_nAtk;
		public int m_nDef;
		public float m_fHp;
		public float m_fDelay;
	}

	public Dictionary<string, STEnemyInfo> m_oEnemyInfoPair { get; set; }


	public override void Awake()
	{
		base.Awake();
		m_oEnemyInfoPair = new Dictionary<string, STEnemyInfo>();
		var oFileName = Application.persistentDataPath + "/EnemyInfoList";

		if (this.LoadEnemyListFromFile(oFileName) == null)
		{
			this.LoadOriginEnemyInfoListFromFile("Datas/GameData/OriginEnemyInfoList");
			this.SaveEnemyListFile(m_oEnemyInfoPair, oFileName);
		}

		m_oEnemyInfoPair = this.LoadEnemyListFromFile(oFileName);


	}

	public void LoadOriginEnemyInfoListFromFile(string a_oFilepath)
	{
		var oTextAsset = Resources.Load<TextAsset>(a_oFilepath);
		var oJSONRoot = SimpleJSON.JSON.Parse(oTextAsset.text);

		var oEnemyInfoList = oJSONRoot["OriginEnemyInfoList"];

		for (int i = 0; i < oEnemyInfoList.Count; ++i)
		{
			var oInfoList = oEnemyInfoList[i];

			var stEnemyInfo = new STEnemyInfo();

			stEnemyInfo.m_nID = int.Parse(oInfoList["ID"]);
			stEnemyInfo.m_oName = oInfoList["Name"];
			stEnemyInfo.m_fDelay = float.Parse(oInfoList["Delay"]);
			stEnemyInfo.m_nAtk = int.Parse(oInfoList["Atk"]);
			stEnemyInfo.m_nDef = int.Parse(oInfoList["Def"]);
			stEnemyInfo.m_fHp = float.Parse(oInfoList["Hp"]);

			m_oEnemyInfoPair.Add(stEnemyInfo.m_oName, stEnemyInfo);
		}
	}

	public Dictionary<string, STEnemyInfo> LoadEnemyListFromFile(string a_oFilepath)
	{
		Dictionary<string, STEnemyInfo> oEnemyList = null;

		if (!File.Exists(a_oFilepath))
		{
			return oEnemyList;
		}

		else
		{
			var oReadStream = new FileStream(a_oFilepath, FileMode.Open, FileAccess.Read);
			var oBinaryFormatter = new BinaryFormatter();

			try
			{
				oEnemyList = (Dictionary<string, STEnemyInfo>)oBinaryFormatter.Deserialize(oReadStream);
			}

			finally
			{
				oReadStream.Close();
			}
		}

		return oEnemyList;

	}

	private void SaveEnemyListFile(Dictionary<string, STEnemyInfo> a_oEnemyList, string a_oFilepath)
	{
		var oWriteStream = new FileStream(a_oFilepath, FileMode.OpenOrCreate, FileAccess.Write);
		var oBinaryFormatter = new BinaryFormatter();

		try
		{
			oBinaryFormatter.Serialize(oWriteStream, a_oEnemyList);
		}

		finally
		{
			oWriteStream.Close();
		}
	}

}
