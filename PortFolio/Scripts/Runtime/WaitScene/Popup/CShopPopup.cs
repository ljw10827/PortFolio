using System.Collections;
using System.Collections.Generic;
using UnityEngine;
using UnityEngine.UI;
// 버튼위에 이미지가 있을경우 버튼 터치가 안먹음
// 그럴떈 이미지에 raycast target을 false로

/*
 * JSON 파일에서 검, 사과, 인벤토리 몇번째 칸 등등등 갯수 와 이름을 가진 파일로 만든다
 * Singleton 하나 만들어서 파일로 부터 불러온 값을 저장시킨다.
 * 그걸 토대로 인벤토리 
 * 
 * SimpleJSon.JSONNode o;
 * 
 * 플레이어 정보에 넣을수 있는 가장 가까운 인벤토리 칸을 추가.
 * 
 * 
 */
public class CShopPopup : CComponent
{
	public GameObject m_oOriginNotice = null;

	public override void Awake()
	{
		base.Awake();
	}


	public void OnTouchShopFrame(GameObject a_oSender)
	{
		var oParentName = a_oSender.name;

		var oNotice = Function.CreateCopiedGameObject("Notice", m_oOriginNotice, this.gameObject);
		var oNoticePopup = oNotice.GetComponentInChildren<CNoticePopup>();

		oNoticePopup.m_oItemName = oParentName;

		CSoundManager.Instance.PlayEffectSound("Sounds/Effect/ClickObject");

	}

	public void OnTouchBackButton(Button a_oSender)
	{
		if (this.gameObject.activeSelf)
		{
			this.gameObject.SetActive(false);
			CSoundManager.Instance.PlayEffectSound("Sounds/Effect/ClickObject");
		}
	}


	public void Purchase(string a_oItemName)
	{
		this.PurchaseItem(a_oItemName);
	}


	private void PurchaseItem(string a_oItemName)
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

		CItemStorage.Instance.SaveItemList();
		CPlayerStorage.Instance.MoneyMinus(500);
		CSceneManager.CurrentSceneManager.SendMessage("SettingText");
	}

}
