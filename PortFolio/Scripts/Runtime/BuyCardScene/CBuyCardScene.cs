using System.Collections;
using System.Collections.Generic;
using UnityEngine;
using UnityEngine.UI;

//쿼터니안 오일러 

public class CBuyCardScene : CSceneManager
{
	public GameObject[] m_oCardArray = null;
	public GameObject m_oExitButton = null;
	private GameObject m_oCard = null;
	private bool m_bIsCardRotate = false;

	public override void Awake()
	{
		base.Awake();
		CSoundManager.Instance.StopBackgroundSound();
		m_bIsCardRotate = false;
		this.BuyCard();
		m_oExitButton.SetActive(false);
	}

	public override void Update()
	{
		base.Update();

		if (m_bIsCardRotate)
		{
			m_oCard.transform.Rotate(0.0f, 180 * Time.deltaTime, 0.0f);

			if (m_oCard.transform.localEulerAngles.y >= 180.0f)
			{
				var oCardEuler = m_oCard.transform.localEulerAngles;
				oCardEuler.y = 180.0f;
				m_oCard.transform.localEulerAngles = oCardEuler;

				m_oExitButton.SetActive(true);

				m_bIsCardRotate = false;
			}
		}
	}

	public void OnTouchCardBack()
	{
		m_bIsCardRotate = true;
		CSoundManager.Instance.PlayEffectSound("Sounds/Effect/EnterEffect");
	}

	public void OnTouchExitButton()
	{
		//사운드 넣기
		CSoundManager.Instance.PlayEffectSound("Sounds/Effect/EnterEffect");
		//리스트 돌아서 양 조절 

		Function.LateCall((a_oParams) =>
		{
			Initiate.Fade("WaitScene", Color.black, 1.5f);
		}, 1.0f);

	}

	private void BuyCard()
	{
		var oCount = CCardStorage.Instance.m_oCardInfoList.Count;
		var oCardList = CCardStorage.Instance.m_oCardInfoList;
		var oCurrentSlot = oCardList[0].m_nSlot;
		var nIndex = 0;


		var nRandomNumber = Random.Range(0, 5);
		for (int i = 0; i < oCardList.Count; ++i)
		{
			if (m_oCardArray[nRandomNumber].name == oCardList[i].m_oName)
			{
				nIndex = i;
			}
		}

		if (oCardList[nIndex].m_nAmount >= 1)
		{
			while (oCardList[nIndex].m_nAmount >= 1)
			{
				nRandomNumber = Random.Range(0, 5);
				for (int i = 0; i < oCardList.Count; ++i)
				{
					if (m_oCardArray[nRandomNumber].name == oCardList[i].m_oName)
					{
						nIndex = i;
					}

				}

				if (oCardList[nIndex].m_nAmount <= 0)
				{
					break;
				}
			}
		}

		for (int i = 0; i < oCardList.Count; ++i)
		{
			oCurrentSlot = oCardList[i].m_nSlot > oCurrentSlot ? oCardList[i].m_nSlot : oCurrentSlot;
		}


		var stCardInfo = new CCardStorage.STCardInfo();
		stCardInfo.m_nID = oCardList[nIndex].m_nID;
		
		stCardInfo.m_nAmount = oCardList[nIndex].m_nAmount + 1;
		stCardInfo.m_nAtk = oCardList[nIndex].m_nAtk;
		stCardInfo.m_nDef = oCardList[nIndex].m_nDef;
		stCardInfo.m_fHp = oCardList[nIndex].m_fHp;
		stCardInfo.m_fDelay = oCardList[nIndex].m_fDelay;
		stCardInfo.m_nLV = oCardList[nIndex].m_nLV;

		stCardInfo.m_bIsSelect = oCardList[nIndex].m_bIsSelect;
		stCardInfo.m_oName = oCardList[nIndex].m_oName;

		if (oCardList[nIndex].m_nSlot == 0)
		{
			stCardInfo.m_nSlot = oCurrentSlot + 1;

		}

		else
		{
			stCardInfo.m_nSlot = oCardList[nIndex].m_nSlot;
		}


		oCardList[nIndex] = stCardInfo;

		m_oCard = m_oCardArray[nRandomNumber];
		m_oCard.SetActive(true);

		CCardStorage.Instance.SaveCardList();
	}
}
