using System.Collections;
using System.Collections.Generic;
using UnityEngine;
using UnityEngine.UI;
public class CCardPopup : CComponent
{
	public GameObject[] m_oFrames = null;

	public void OnEnable()
	{
		var oCardList = CCardStorage.Instance.m_oCardInfoList;

		for (int i = 0; i < oCardList.Count; ++i)
		{
			if (oCardList[i].m_nAmount <= 0)
			{
				continue;
			}

			else
			{
				this.SetItemSlot(oCardList[i].m_nSlot, oCardList[i].m_oName);
			}

		}

	
	}


	public void OnTouchBackButton(Button a_oSender)
	{
		if (this.gameObject.activeSelf)
		{
			this.gameObject.SetActive(false);
			CSoundManager.Instance.PlayEffectSound("Sounds/Effect/ClickObject");

		}
	}

	public void OnTouchBuyButton(Button a_oSender)
	{
		if (this.gameObject.activeSelf)
		{
			this.gameObject.SetActive(false);
		}

		Initiate.Fade("BuyCardScene", Color.black, 1.5f);
		CPlayerStorage.Instance.CashMinus(500);
		CSoundManager.Instance.PlayEffectSound("Sounds/Effect/EnterEffect");
		CSceneManager.CurrentSceneManager.SendMessage("SettingText");

	}

	public void OnTouchMiniCharacter(string a_oCardName)
	{
		var oOriginCard = Function.CreateCopiedGameObject(a_oCardName, "Prefabs/WaitScene/Card/Origin/" + a_oCardName, CSceneManager.UIRoot);
		CSoundManager.Instance.PlayEffectSound("Sounds/Effect/ClickObject");
	}

	public void OnTouchSelectButton(GameObject a_oSender)
	{
		var oCardList = CCardStorage.Instance.m_oCardInfoList;

		for (int i = 0; i < oCardList.Count; ++i)
		{
			if (oCardList[i].m_oName == a_oSender.name)
			{
				var stCardInfo = new CCardStorage.STCardInfo();
				stCardInfo.m_nID = oCardList[i].m_nID;
				stCardInfo.m_nSlot = oCardList[i].m_nSlot;
				stCardInfo.m_nAmount = oCardList[i].m_nAmount;
				stCardInfo.m_nAtk = oCardList[i].m_nAtk;
				stCardInfo.m_nDef = oCardList[i].m_nDef;
				stCardInfo.m_fHp = oCardList[i].m_fHp;
				stCardInfo.m_fDelay = oCardList[i].m_fDelay;
				stCardInfo.m_nLV = oCardList[i].m_nLV;


				stCardInfo.m_bIsSelect = true;
				stCardInfo.m_oName = oCardList[i].m_oName;

				oCardList[i] = stCardInfo;

				Destroy(a_oSender);
				break;
			}
		}

		CSoundManager.Instance.PlayEffectSound("Sounds/Effect/ClickObject");
	}

	public void OnTouchPrevButton(GameObject a_oSender)
	{
		var oCardList = CCardStorage.Instance.m_oCardInfoList;

		for (int i = 0; i < oCardList.Count; ++i)
		{
			if (oCardList[i].m_oName == a_oSender.name)
			{
				var stCardInfo = new CCardStorage.STCardInfo();
				stCardInfo.m_nID = oCardList[i].m_nID;
				stCardInfo.m_nSlot = oCardList[i].m_nSlot;
				stCardInfo.m_nAmount = oCardList[i].m_nAmount;
				stCardInfo.m_nAtk = oCardList[i].m_nAtk;
				stCardInfo.m_nDef = oCardList[i].m_nDef;
				stCardInfo.m_fHp = oCardList[i].m_fHp;
				stCardInfo.m_fDelay = oCardList[i].m_fDelay;
				stCardInfo.m_nLV = oCardList[i].m_nLV;


				stCardInfo.m_bIsSelect = false;
				stCardInfo.m_oName = oCardList[i].m_oName;

				oCardList[i] = stCardInfo;

				Destroy(a_oSender);
				break;
			}
		}

		CSoundManager.Instance.PlayEffectSound("Sounds/Effect/ClickObject");
	}

	private void SetItemSlot(int a_nSlot, string a_oCardName)
	{
		var CurrentFrame = m_oFrames[a_nSlot / 8];

		if (CurrentFrame.transform.Find(a_oCardName) == null)
		{
			var oItem = Function.CreateCopiedGameObject(a_oCardName, "Prefabs/WaitScene/Card/Mini/" + a_oCardName, CurrentFrame);
			var oPosition = oItem.transform.localPosition;
			oPosition = new Vector3(-301.0f + ((a_nSlot - 1) * 87.0f), 0.0f, 0.0f);
			oItem.transform.localPosition = oPosition;
		}
	}

}
