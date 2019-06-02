using System.Collections;
using System.Collections.Generic;
using UnityEngine;
using UnityEngine.UI;

public class CStatPopup : CComponent
{
	//[HideInInspector]
	public string m_oName = null;

	public Text[] m_oTextArray = null;
	private string[] m_oTextLVUp = null;

	public override void Start()
	{
		base.Start();
		m_oTextLVUp = new string[5];

		m_oTextLVUp[0] = "아이템 : 검 1개 필요합니다.";
		m_oTextLVUp[1] = "아이템 : 갑옷 1개 필요합니다.";
		m_oTextLVUp[2] = "아이템 : 반지 1개 필요합니다.";
		m_oTextLVUp[3] = "아이템 : " +
			"검, 갑옷, 반지 1개씩 필요합니다.";
		m_oTextLVUp[4] = "더 이상 강화할수 없습니다.";

		
		var oList = CCardStorage.Instance.m_oCardInfoList;

		for (int i = 0; i < oList.Count; ++i)
		{
			if (oList[i].m_oName == m_oName)
			{
				m_oTextArray[0].text = oList[i].m_nAtk.ToString();
				m_oTextArray[1].text = oList[i].m_nDef.ToString();
				m_oTextArray[2].text = oList[i].m_fDelay.ToString();
				m_oTextArray[3].text = oList[i].m_oName.ToString();
				
				m_oTextArray[m_oTextArray.Length - 1].text = m_oTextLVUp[oList[i].m_nLV - 1];
				break;
			}
		}
	}

	public void OnTouchEnhanceButton()
	{
		var oList = CCardStorage.Instance.m_oCardInfoList;
		for (int i = 0; i < oList.Count; ++i)
		{
			if (oList[i].m_oName == this.m_oName)
			{
				this.Enhance(i);
			}
		}

	}

	private void Enhance(int a_nIndex)
	{
		var oList = CCardStorage.Instance.m_oCardInfoList;
		var oItemList = CItemStorage.Instance.GetItemInfoList();
		int nLevel = oList[a_nIndex].m_nLV;

		if (nLevel == 1)
		{
			var nIndex = CItemStorage.Instance.GetItem("Sword");


			if (oItemList[nIndex].m_nAmount < 1)
			{
				//DO NOTHING
			}

			else
			{
				CItemStorage.Instance.RemoveAmount("Sword", 1);
				CCardStorage.Instance.LevelUp(m_oName);
				this.LevelUpText();
			}
		}

		else if (nLevel == 2)
		{
			var nIndex = CItemStorage.Instance.GetItem("Armor");


			if (oItemList[nIndex].m_nAmount < 1)
			{
				//DO NOTHING
			}

			else
			{
				CItemStorage.Instance.RemoveAmount("Armor", 1);
				CCardStorage.Instance.LevelUp(m_oName);
				this.LevelUpText();
			}
		}

		else if (nLevel == 3)
		{
			var nIndex = CItemStorage.Instance.GetItem("Ring");


			if (oItemList[nIndex].m_nAmount < 1)
			{
				//DO NOTHING
			}

			else
			{
				CItemStorage.Instance.RemoveAmount("Ring", 1);
				CCardStorage.Instance.LevelUp(m_oName);
				this.LevelUpText();
			}
		}

		else if (nLevel == 4)
		{
			var nArmorIndex = CItemStorage.Instance.GetItem("Armor");
			var nRingIndex = CItemStorage.Instance.GetItem("Ring");
			var nSwordIndex = CItemStorage.Instance.GetItem("Sword");

			if (oItemList[nArmorIndex].m_nAmount >= 1 && oItemList[nRingIndex].m_nAmount >= 1 
				&& oItemList[nSwordIndex].m_nAmount >= 1)
			{
				CItemStorage.Instance.RemoveAmount("Sword", 1);
				CItemStorage.Instance.RemoveAmount("Ring", 1);
				CItemStorage.Instance.RemoveAmount("Armor", 1);
				CCardStorage.Instance.LevelUp(m_oName);
				this.LevelUpText();
			}

			else
			{
				//DO NOTHING
			}

			CItemStorage.Instance.SaveItemList();

		}

		else if (nLevel >= 5)
		{
			//DO NOTHING
		}

	}

	public void OnTouchExitButton()
	{
		CSoundManager.Instance.PlayEffectSound("Sounds/Effect/ButtonClickEffect");
		Destroy(this.gameObject);
	}

	private void LevelUpText()
	{
		var oList = CCardStorage.Instance.m_oCardInfoList;

		for (int i = 0; i < oList.Count; ++i)
		{
			if (oList[i].m_oName == m_oName)
			{
				m_oTextArray[0].text = oList[i].m_nAtk.ToString();
				m_oTextArray[1].text = oList[i].m_nDef.ToString();
				m_oTextArray[2].text = oList[i].m_fDelay.ToString();
				m_oTextArray[3].text = oList[i].m_oName.ToString();
				m_oTextArray[4].text = oList[i].m_nLV.ToString();

				m_oTextArray[m_oTextArray.Length - 1].text = m_oTextLVUp[oList[i].m_nLV - 1];
				break;
			}
		}

		CCardStorage.Instance.SaveCardList();
	}


}
