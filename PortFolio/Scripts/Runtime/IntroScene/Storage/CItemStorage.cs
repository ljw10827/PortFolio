using System.Collections;
using System.Collections.Generic;
using UnityEngine;
using System.IO;
using System.Runtime.Serialization.Formatters.Binary;


public class CItemStorage : CSingleton<CItemStorage>
{
	[System.Serializable]
	public struct STItemInfo
	{
		public int m_nID;
		public string m_oName;
		public int m_nSlot;
		public int m_nAmount;
	}

	private List<STItemInfo> m_oItemInfoList = null;
	
	

	public override void Awake()
	{
		base.Awake();
		m_oItemInfoList = new List<STItemInfo>();

		var oFileName = Application.persistentDataPath + "/ItemInfoList.json";

		if (this.LoadItemListFromFile(oFileName) == null)
		{
			this.LoadOriginItemInfoListFromFile("Datas/GameData/OriginItemList");
			this.SaveItemListToFile(m_oItemInfoList, oFileName);
		}
		
		m_oItemInfoList = this.LoadItemListFromFile(oFileName);
	}


	public List<STItemInfo> GetItemInfoList()
	{
		return m_oItemInfoList;
	}

	

	public void LoadOriginItemInfoListFromFile(string a_oFilepath)
	{
		var oTextAsset = Resources.Load<TextAsset>(a_oFilepath);
		var oJSONRoot = SimpleJSON.JSON.Parse(oTextAsset.text);

		var oItemInfoList = oJSONRoot["OriginItemList"];

		for (int i = 0; i < oItemInfoList.Count; ++i)
		{
			var oInfoList = oItemInfoList[i];

			var stItemInfo = new STItemInfo();

			stItemInfo.m_nID = int.Parse(oInfoList["ID"]);
			stItemInfo.m_oName = oInfoList["Name"];
			stItemInfo.m_nSlot = int.Parse(oInfoList["Slot"]);
			stItemInfo.m_nAmount = int.Parse(oInfoList["Amount"]);

			m_oItemInfoList.Add(stItemInfo);
		}
	}

	private void SaveItemListToFile(List<STItemInfo> a_oItemList,
		string a_oFilepath)
	{
		var oWriteStream = new FileStream(a_oFilepath, FileMode.OpenOrCreate, FileAccess.Write);
		var oBinaryFormatter = new BinaryFormatter();

		try
		{
			oBinaryFormatter.Serialize(oWriteStream, a_oItemList);
		}
		finally
		{
			oWriteStream.Close();
		}

	}

	public void SaveItemList()
	{
		var oFilepath = Application.persistentDataPath + "/ItemInfoList.json";

		var oWriteStream = new FileStream(oFilepath, FileMode.OpenOrCreate, FileAccess.Write);
		var oBinaryFormatter = new BinaryFormatter();

		try
		{
			oBinaryFormatter.Serialize(oWriteStream, m_oItemInfoList);
		}
		finally
		{
			oWriteStream.Close();
		}
	}

	public List<STItemInfo> LoadItemListFromFile(string a_oFilepath)
	{
		List<STItemInfo> oItemList = null;


		if (!File.Exists(a_oFilepath))
		{
			Function.ShowLog("파일이 없다.");
			return oItemList;
		}

		else
		{
		var oReadStream = new FileStream(a_oFilepath, FileMode.Open, FileAccess.Read);
		var oBinaryFormatter = new BinaryFormatter();
		
			try
			{
				oItemList = (List<STItemInfo>)oBinaryFormatter.Deserialize(oReadStream);
			}
			finally
			{
				oReadStream.Close();
			}
		}

		return oItemList;
	}

	public void RemoveAmount(string a_oItemName, int a_nAmount)
	{
		for (int i = 0; i < m_oItemInfoList.Count; ++i)
		{
			if (m_oItemInfoList[i].m_oName == a_oItemName)
			{
				var stItemInfo = new CItemStorage.STItemInfo();

				stItemInfo.m_nID = m_oItemInfoList[i].m_nID;
				stItemInfo.m_oName = m_oItemInfoList[i].m_oName;
				stItemInfo.m_nAmount = m_oItemInfoList[i].m_nAmount - a_nAmount;
				stItemInfo.m_nSlot = m_oItemInfoList[i].m_nSlot;

				m_oItemInfoList[i] = stItemInfo;

				if (m_oItemInfoList[i].m_nAmount == 0)
				{
					this.ChangeSlot();
				}
				break;
			}
		}

	}

	public void ChangeSlot()
	{
		var nIndex = 0;

		for (int i = 0; i < m_oItemInfoList.Count; ++i)
		{
			if (m_oItemInfoList[i].m_nAmount == 0 && m_oItemInfoList[i].m_nSlot != 0)
			{
				nIndex = i;
				break;
			}
		}

		for (int i = 0; i < m_oItemInfoList.Count; ++i)
		{

			if (m_oItemInfoList[nIndex].m_nSlot >= m_oItemInfoList[i].m_nSlot)
			{
				continue;
			}

			else
			{
				var stItemInfo = new CItemStorage.STItemInfo();

				stItemInfo.m_nID = m_oItemInfoList[i].m_nID;
				stItemInfo.m_oName = m_oItemInfoList[i].m_oName;
				stItemInfo.m_nAmount = m_oItemInfoList[i].m_nAmount;
				stItemInfo.m_nSlot = m_oItemInfoList[i].m_nSlot - 1;

				m_oItemInfoList[i] = stItemInfo;
			}
			
		}

		var stLastItemInfo = new CItemStorage.STItemInfo();

		stLastItemInfo.m_nID = m_oItemInfoList[nIndex].m_nID;
		stLastItemInfo.m_oName = m_oItemInfoList[nIndex].m_oName;
		stLastItemInfo.m_nAmount = m_oItemInfoList[nIndex].m_nAmount;
		stLastItemInfo.m_nSlot = 0;

		m_oItemInfoList[nIndex] = stLastItemInfo;
	}

	public int GetItem(string a_oName)
	{
		int nIndex = 0;
		for (int i = 0; i < this.m_oItemInfoList.Count; ++i)
		{
			if (m_oItemInfoList[i].m_oName == a_oName)
			{
				nIndex = i;
				break;
			}
		}

		return nIndex;
	}

}


