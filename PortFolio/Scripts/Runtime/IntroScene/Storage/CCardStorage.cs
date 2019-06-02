using System.Collections;
using System.Collections.Generic;
using UnityEngine;
using System.IO;
using System.Runtime.Serialization.Formatters.Binary;

public class CCardStorage : CSingleton<CCardStorage>
{
	[System.Serializable]
	public struct STCardInfo
	{
		public int m_nID;
		public string m_oName;
		public int m_nAtk;
		public int m_nDef;
		public float m_fHp;
		public bool m_bIsSelect;
		public int m_nSlot;
		public int m_nAmount;
		public float m_fDelay;
		public int m_nLV;
	}

	public List<STCardInfo> m_oCardInfoList { get; set; }

	public override void Awake()
	{
		
		base.Awake();
		m_oCardInfoList = new List<STCardInfo>();

		var oFileName = Application.persistentDataPath + "/CardInfoList.json";

		if (this.LoadItemListFromFile(oFileName) == null)
		{
			this.LoadOriginItemInfoListFromFile("Datas/GameData/OriginCardInfoList");
			this.SaveItemListToFile(m_oCardInfoList, oFileName);
		}

		m_oCardInfoList = this.LoadItemListFromFile(oFileName);

	}


	public void LoadOriginItemInfoListFromFile(string a_oFilepath)
	{
		var oTextAsset = Resources.Load<TextAsset>(a_oFilepath);
		var oJSONRoot = SimpleJSON.JSON.Parse(oTextAsset.text);

		var oCardInfoList = oJSONRoot["OriginCardInfoList"];

		for (int i = 0; i < oCardInfoList.Count; ++i)
		{
			var oInfoList = oCardInfoList[i];

			var stCardInfo = new STCardInfo();

			stCardInfo.m_nID = int.Parse(oInfoList["ID"]);
			stCardInfo.m_nSlot = int.Parse(oInfoList["Slot"]);
			stCardInfo.m_nAmount = int.Parse(oInfoList["Amount"]);
			stCardInfo.m_nAtk = int.Parse(oInfoList["Atk"]);
			stCardInfo.m_nDef = int.Parse(oInfoList["Def"]);
			stCardInfo.m_fHp = float.Parse(oInfoList["Hp"]);
			stCardInfo.m_fDelay = float.Parse(oInfoList["Delay"]);
			stCardInfo.m_nLV = int.Parse(oInfoList["LV"]);

			stCardInfo.m_bIsSelect = bool.Parse(oInfoList["Select"]);
			stCardInfo.m_oName = oInfoList["Name"];

			m_oCardInfoList.Add(stCardInfo);
		}
	}

	private void SaveItemListToFile(List<STCardInfo> a_oCardList,
		string a_oFilepath)
	{
		var oWriteStream = new FileStream(a_oFilepath, FileMode.OpenOrCreate, FileAccess.Write);
		var oBinaryFormatter = new BinaryFormatter();

		try
		{
			oBinaryFormatter.Serialize(oWriteStream, a_oCardList);
		}
		finally
		{
			oWriteStream.Close();
		}

	}

	public List<STCardInfo> LoadItemListFromFile(string a_oFilepath)
	{
		List<STCardInfo> oCardList = null;


		if (!File.Exists(a_oFilepath))
		{
			Function.ShowLog("파일이 없다.");
			return oCardList;
		}

		else
		{
			var oReadStream = new FileStream(a_oFilepath, FileMode.Open, FileAccess.Read);
			var oBinaryFormatter = new BinaryFormatter();

			try
			{
				oCardList = (List<STCardInfo>)oBinaryFormatter.Deserialize(oReadStream);
			}
			finally
			{
				oReadStream.Close();
			}
		}

		return oCardList;
	}

	public void LevelUp(string a_oName)
	{
		for (int i = 0; i < this.m_oCardInfoList.Count; ++i)
		{
			if (m_oCardInfoList[i].m_oName == a_oName)
			{
				if (m_oCardInfoList[i].m_nLV >= 5)
				{
					break;
				}

				var stCardInfo = new STCardInfo();
				stCardInfo.m_nID = m_oCardInfoList[i].m_nID;
				stCardInfo.m_nSlot = m_oCardInfoList[i].m_nSlot;
				stCardInfo.m_nAmount = m_oCardInfoList[i].m_nAmount;
				stCardInfo.m_nAtk = m_oCardInfoList[i].m_nAtk + 5;
				stCardInfo.m_nDef = m_oCardInfoList[i].m_nDef + 5;
				stCardInfo.m_fHp = m_oCardInfoList[i].m_fHp;
				stCardInfo.m_fDelay = m_oCardInfoList[i].m_fDelay - 0.3f;
				stCardInfo.m_nLV = m_oCardInfoList[i].m_nLV + 1;


				stCardInfo.m_bIsSelect = true;
				stCardInfo.m_oName = m_oCardInfoList[i].m_oName;

				m_oCardInfoList[i] = stCardInfo;
			}
		}
	}

	public void SaveCardList()
	{
		var oFilepath = Application.persistentDataPath + "/CardInfoList.json";

		var oWriteStream = new FileStream(oFilepath, FileMode.OpenOrCreate, FileAccess.Write);
		var oBinaryFormatter = new BinaryFormatter();

		try
		{
			oBinaryFormatter.Serialize(oWriteStream, m_oCardInfoList);
		}
		finally
		{
			oWriteStream.Close();
		}
	}
}
