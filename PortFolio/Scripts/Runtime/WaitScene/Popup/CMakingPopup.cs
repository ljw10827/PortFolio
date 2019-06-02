using System.Collections;
using System.Collections.Generic;
using UnityEngine;
using UnityEngine.UI;

public class CMakingPopup : CComponent
{

	public Text[] m_oTexts = null;

	public override void Awake()
	{
		base.Awake();

		var oPlayerInfo = CPlayerStorage.Instance.m_oPlayerInfoList;

		m_oTexts[0].text = oPlayerInfo[0].m_nMoney.ToString();
		m_oTexts[1].text = oPlayerInfo[0].m_nCash.ToString();
		m_oTexts[2].text = oPlayerInfo[0].m_oName;
	}


	public void OnTouchMakingFrame(GameObject a_oSender)
	{
		var oParentName = a_oSender.name;

		var oNotice = Function.CreateCopiedGameObject("Notice", "Prefabs/WaitScene/Popups/MixNotice", this.gameObject);
		var oNoticePopup = oNotice.GetComponentInChildren<CMixNoticePopup>();

		oNoticePopup.m_oItemName = oParentName;

		CSoundManager.Instance.PlayEffectSound("Sounds/Effect/ClickObject");
	}

	public void OnTouchBackButton(Button a_oSender)
	{
		Destroy(this.gameObject);
		CSoundManager.Instance.PlayEffectSound("Sounds/Effect/ClickObject");
	}

	public void Mix(string a_oItemName)
	{
		this.MixItem(a_oItemName);
	}

	private void MixItem(string a_oItemName)
	{
		var oItemStorage = CItemStorage.Instance;
		var oList = oItemStorage.GetItemInfoList();



		if (a_oItemName == "Sword")
		{
			if (CurrentItemAmount("Ingots") >= 2 && CurrentItemAmount("Scroll") >= 2 && CurrentItemAmount("Apple") >= 2)
			{
				oItemStorage.RemoveAmount("Ingots", 2);
				oItemStorage.RemoveAmount("Scroll", 2);
				oItemStorage.RemoveAmount("Apple", 2);

				this.SetMakingItem(a_oItemName);
			}
		}

		else if (a_oItemName == "Ring")
		{
			if (CurrentItemAmount("Gem") >= 2 && CurrentItemAmount("Scroll") >= 2 && CurrentItemAmount("Book") >= 2)
			{
				oItemStorage.RemoveAmount("Gem", 2);
				oItemStorage.RemoveAmount("Scroll", 2);
				oItemStorage.RemoveAmount("Book", 2);

				this.SetMakingItem(a_oItemName);
			}
		}

		else if (a_oItemName == "Armor")
		{
			if (CurrentItemAmount("Gem") >= 2 && CurrentItemAmount("Scroll") >= 2 && CurrentItemAmount("Apple") >= 2)
			{
				oItemStorage.RemoveAmount("Gem", 2);
				oItemStorage.RemoveAmount("Scroll", 2);
				oItemStorage.RemoveAmount("Apple", 2);

				this.SetMakingItem(a_oItemName);
			}
		}

		else
		{
			return;
		}

		CItemStorage.Instance.SaveItemList();
	}


	private int CurrentItemAmount(string a_oItemName)
	{
		var oItemList = CItemStorage.Instance.GetItemInfoList();

		for (int i = 0; i < oItemList.Count; ++i)
		{
			if (oItemList[i].m_oName == a_oItemName)
			{
				return oItemList[i].m_nAmount;
			}
		}

		return 0;
	}

	private void SetMakingItem(string a_oItemName)
	{
		var oItemList = CItemStorage.Instance.GetItemInfoList();
		var oCurrentSlot = oItemList[0].m_nSlot;
		CSoundManager.Instance.PlayEffectSound("Sounds/Effect/MixEffect");

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
				stItemInfo.m_nAmount = oItemList[i].m_nAmount + 1;

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
