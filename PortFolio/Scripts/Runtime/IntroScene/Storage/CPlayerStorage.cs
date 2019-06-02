using System.Collections;
using System.Collections.Generic;
using UnityEngine;
using System.IO;
using System.Runtime.Serialization.Formatters.Binary;


public class CPlayerStorage : CSingleton<CPlayerStorage>
{
	[System.Serializable]
	public struct STPlayerInfo
	{
		public int m_nID;
		public string m_oName;
		public int m_nMoney;
		public int m_nCash;
	}

	public List<STPlayerInfo> m_oPlayerInfoList { get; set; }

	public override void Awake()
	{
		base.Awake();
		m_oPlayerInfoList = new List<STPlayerInfo>();
		var oFileName = Application.persistentDataPath + "/PlayerInfoList.json";

		if (this.LoadItemListFromFile(oFileName) == null)
		{
			this.LoadOriginItemInfoListFromFile("Datas/GameData/PlayerInfoList");
			this.SaveItemListToFile(m_oPlayerInfoList, oFileName);
		}

		m_oPlayerInfoList = this.LoadItemListFromFile(oFileName);

	}

	public void LoadOriginItemInfoListFromFile(string a_oFilepath)
	{
		var oTextAsset = Resources.Load<TextAsset>(a_oFilepath);
		var oJSONRoot = SimpleJSON.JSON.Parse(oTextAsset.text);

		var oPlayerInfoList = oJSONRoot["PlayerInfoList"];

		for (int i = 0; i < oPlayerInfoList.Count; ++i)
		{
			var oInfoList = oPlayerInfoList[i];

			var stPlayerInfo = new STPlayerInfo();

			stPlayerInfo.m_nID = int.Parse(oInfoList["ID"]);
			stPlayerInfo.m_nMoney = int.Parse(oInfoList["Money"]);
			stPlayerInfo.m_nCash= int.Parse(oInfoList["Cash"]);

			stPlayerInfo.m_oName = oInfoList["Name"];

			m_oPlayerInfoList.Add(stPlayerInfo);
		}
	}

	private void SaveItemListToFile(List<STPlayerInfo> a_oPlayerList,
		string a_oFilepath)
	{
		var oWriteStream = new FileStream(a_oFilepath, FileMode.OpenOrCreate, FileAccess.Write);
		var oBinaryFormatter = new BinaryFormatter();

		try
		{
			oBinaryFormatter.Serialize(oWriteStream, a_oPlayerList);
		}
		finally
		{
			oWriteStream.Close();
		}

	}

	public List<STPlayerInfo> LoadItemListFromFile(string a_oFilepath)
	{
		List<STPlayerInfo> oPlayerList = null;


		if (!File.Exists(a_oFilepath))
		{
			Function.ShowLog("파일이 없다.");
			return oPlayerList;
		}

		else
		{
			var oReadStream = new FileStream(a_oFilepath, FileMode.Open, FileAccess.Read);
			var oBinaryFormatter = new BinaryFormatter();

			try
			{
				oPlayerList = (List<STPlayerInfo>)oBinaryFormatter.Deserialize(oReadStream);
			}
			finally
			{
				oReadStream.Close();
			}
		}

		return oPlayerList;
	}

	public void MoneyMinus(int a_nPrice)
	{
		var stPlayerInfo = new STPlayerInfo();

		stPlayerInfo.m_nID = m_oPlayerInfoList[0].m_nID;
		stPlayerInfo.m_nMoney = m_oPlayerInfoList[0].m_nMoney - a_nPrice;
		stPlayerInfo.m_nCash = m_oPlayerInfoList[0].m_nCash;

		stPlayerInfo.m_oName = m_oPlayerInfoList[0].m_oName;

		m_oPlayerInfoList[0] = stPlayerInfo;

		this.SavePlayerInfo();
	}

	public void CashMinus(int a_nPrice)
	{
		var stPlayerInfo = new STPlayerInfo();

		stPlayerInfo.m_nID = m_oPlayerInfoList[0].m_nID;
		stPlayerInfo.m_nMoney = m_oPlayerInfoList[0].m_nMoney;
		stPlayerInfo.m_nCash = m_oPlayerInfoList[0].m_nCash - a_nPrice;

		stPlayerInfo.m_oName = m_oPlayerInfoList[0].m_oName;

		m_oPlayerInfoList[0] = stPlayerInfo;

		this.SavePlayerInfo();
	}

	public void SavePlayerInfo()
	{
		var oFilepath = Application.persistentDataPath + "/PlayerInfoList.json";

		var oWriteStream = new FileStream(oFilepath, FileMode.OpenOrCreate, FileAccess.Write);
		var oBinaryFormatter = new BinaryFormatter();

		try
		{
			oBinaryFormatter.Serialize(oWriteStream, m_oPlayerInfoList);
		}
		finally
		{
			oWriteStream.Close();
		}
	}
}


