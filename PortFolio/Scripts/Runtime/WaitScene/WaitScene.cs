using System.Collections;
using System.Collections.Generic;
using UnityEngine;
using UnityEngine.UI;
using GooglePlayGames;
using GooglePlayGames.BasicApi;


//컨트롤a 컨트롤c하면 복사됨ui
public class WaitScene : CSceneManager
{
	public GameObject m_oInventory = null;
	public GameObject m_oShop = null;
	public GameObject m_oStage = null;
	public GameObject m_oCard = null;
	public GameObject m_oHeroPopup = null;
	public Text[] m_oGoldText = null;
	public Text[] m_oCashText = null;
	public Text[] m_oPlayerText = null;

	public override void Awake()
	{
		base.Awake();
		CSoundManager.Instance.StopBackgroundSound();
		CSoundManager.Instance.PlayBackgroundSound("Sounds/BG/WaitBG");
		this.SettingText();

		var oCardList = CCardStorage.Instance.m_oCardInfoList;

		for (int i = 0; i < oCardList.Count; ++i)
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
		}
	}


	public void OnTouchHeroButton(Button a_oSender)
	{
		if (!m_oHeroPopup.activeSelf)
		{
			m_oHeroPopup.SetActive(true);
			CSoundManager.Instance.PlayEffectSound("Sounds/Effect/ButtonClickEffect");
		}
	}

	public void OnTouchCardButton(Button a_oSender)
	{
		if (!m_oCard.activeSelf)
		{
			m_oCard.SetActive(true);
			CSoundManager.Instance.PlayEffectSound("Sounds/Effect/ButtonClickEffect");
		}
	}

	public void OnTouchInvenButton(Button a_oSender)
	{
		if (!m_oInventory.activeSelf)
		{
			m_oInventory.SetActive(true);
			CSoundManager.Instance.PlayEffectSound("Sounds/Effect/ButtonClickEffect");
		}
	}

	public void OnTouchShopButton(Button a_oSender)
	{
		if (!m_oShop.activeSelf)
		{
			m_oShop.SetActive(true);
			CSoundManager.Instance.PlayEffectSound("Sounds/Effect/ButtonClickEffect");
		}
	}

	public void OnTouchDungeonButton(Button a_oSender)
	{
		if (!m_oStage.activeSelf)
		{
			m_oStage.SetActive(true);
			CSoundManager.Instance.PlayEffectSound("Sounds/Effect/ButtonClickEffect");
		}
	}

	public void SettingText()
	{
		var oPlayerList = CPlayerStorage.Instance.m_oPlayerInfoList;

		for (int i = 0; i < m_oCashText.Length; ++i)
		{
			m_oCashText[i].text = oPlayerList[0].m_nCash.ToString();
			m_oGoldText[i].text = oPlayerList[0].m_nMoney.ToString();
			m_oPlayerText[i].text = oPlayerList[0].m_oName.ToString();
		}
	}

		

}
