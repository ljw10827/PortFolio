using System.Collections;
using System.Collections.Generic;
using UnityEngine;
using UnityEngine.UI;

public class ChapterOneScene : CSceneManager
{
	public GameObject m_oRewardPanel = null;
	public GameObject m_oLosePanel = null;
	public Text[] m_oTextList = null;

	public override void Awake()
	{
		base.Awake();
		CSoundManager.Instance.StopBackgroundSound();
		CSoundManager.Instance.PlayBackgroundSound("Sounds/BG/DungeonBG");

		m_oRewardPanel.SetActive(false);
		m_oLosePanel.SetActive(false);
	}


	public void OnTouchExitButton(Button a_oSender)
	{
		Color oColorBlack = Color.black;
		Initiate.Fade("WaitScene", oColorBlack, 0.2f);
	}

	public void SetRewardItem()
	{
		for (int i = 0; i < m_oTextList.Length; ++i)
		{
			var nRandomValue = Random.Range(1, 4);
			this.Reward(m_oTextList[i].transform.parent.name, nRandomValue);
			m_oTextList[i].text = nRandomValue.ToString();
		}
	}

	public void OnEnablePanel()
	{
		if (!m_oRewardPanel.activeSelf)
		{
			m_oRewardPanel.SetActive(true);
			this.SetRewardItem();
			CItemStorage.Instance.SaveItemList();
		}
	}


	public void OnEnableLosePanel()
	{
		if (!m_oLosePanel.activeSelf)
		{
			m_oLosePanel.SetActive(true);
		}
	}

	private void Reward(string a_oItemName, int a_nAmount)
	{
		var oItemList = CItemStorage.Instance.GetItemInfoList();
		var oCurrentSlot = oItemList[0].m_nSlot;


		for (int i = 0; i < oItemList.Count; ++i)
		{
			oCurrentSlot = oItemList[i].m_nSlot > oCurrentSlot ? oItemList[i].m_nSlot : oCurrentSlot;
		}


		for (int i = 0; i < oItemList.Count; ++i)
		{
			if (oItemList[i].m_oName == a_oItemName)
			{
				var stItemInfo = new CItemStorage.STItemInfo();

				stItemInfo.m_nID = oItemList[i].m_nID;
				stItemInfo.m_oName = oItemList[i].m_oName;
				stItemInfo.m_nAmount = oItemList[i].m_nAmount + a_nAmount;

				if (oItemList[i].m_nSlot == 0)
				{
					stItemInfo.m_nSlot = oCurrentSlot + 1;

				}

				else
				{
					stItemInfo.m_nSlot = oItemList[i].m_nSlot;
				}

				oItemList[i] = stItemInfo;
				break;
			}
		}
	}
}
