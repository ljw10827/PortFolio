using System.Collections;
using System.Collections.Generic;
using UnityEngine;
using UnityEngine.UI;

public class CInventoryPopup : CComponent
{
	public GameObject[] m_oFrames = null;

	public void OnEnable()
	{
		var oItemList = CItemStorage.Instance.GetItemInfoList();

		for(int i = 0; i < oItemList.Count; ++i)
		{
			if (oItemList[i].m_nAmount <= 0)
			{
				this.CleanInventory(oItemList[i].m_oName, oItemList[i].m_nSlot);
				continue;
			}

			else
			{
				this.SetItemSlot(oItemList[i].m_nSlot, oItemList[i].m_oName, oItemList[i].m_nAmount);
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

	private void SetItemSlot(int a_nSlot, string a_oItemName, int a_oAmount)
	{
		var CurrentFrame = m_oFrames[a_nSlot / 9];
		var oItemList = CItemStorage.Instance.GetItemInfoList();

		if (CurrentFrame.transform.Find(a_oItemName) == null)
		{
			var oItem = Function.CreateCopiedGameObject(a_oItemName, "Prefabs/WaitScene/Item/" + a_oItemName, CurrentFrame);
			var oPosition = oItem.transform.localPosition;
			oPosition = new Vector3(-301.0f + ((a_nSlot - 1) * 87.0f), 0.0f, 0.0f);
			oItem.transform.localPosition = oPosition;

			var oText = oItem.GetComponentInChildren<Text>();
			oText.text = a_oAmount.ToString();
		}


		else
		{
			var oItem = CurrentFrame.transform.Find(a_oItemName).gameObject;

			var oPosition = oItem.transform.localPosition;
			oPosition = new Vector3(-301.0f + ((a_nSlot - 1) * 87.0f), 0.0f, 0.0f);
			oItem.transform.localPosition = oPosition;

			var oText = oItem.GetComponentInChildren<Text>();
			oText.text = a_oAmount.ToString();
		}
	}

	private void CleanInventory(string a_oItemName, int a_nSlot)
	{
		var CurrentFrame = m_oFrames[a_nSlot / 9];
		var oItemList = CItemStorage.Instance.GetItemInfoList();

		if (CurrentFrame.transform.Find(a_oItemName) != null)
		{
			var oItem = CurrentFrame.transform.Find(a_oItemName);
			Destroy(oItem.gameObject);
		}
	}

	public void OnTouchMakingButton(Button a_oSender)
	{
		var oNotice = Function.CreateCopiedGameObject("MakingPopup", "Prefabs/WaitScene/Popups/MakingPopup", CSceneManager.UIRoot);
		oNotice.SetActive(true);

		if (this.gameObject.activeSelf)
		{
			this.gameObject.SetActive(false);
			CSoundManager.Instance.PlayEffectSound("Sounds/Effect/ButtonClickEffect");
		}
	}

}

