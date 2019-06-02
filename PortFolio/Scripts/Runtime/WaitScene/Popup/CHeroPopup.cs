using System.Collections;
using System.Collections.Generic;
using UnityEngine;
using UnityEngine.UI;

public class CHeroPopup : CComponent
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

	public void OnTouchMiniCharacter(string a_oCardName)
	{
		var oOriginCard = Function.CreateCopiedGameObject(a_oCardName, "Prefabs/WaitScene/Card/Stat/" + a_oCardName, CSceneManager.UIRoot);
		CSoundManager.Instance.PlayEffectSound("Sounds/Effect/ClickObject");
	}

	public void OnTouchSelectButton(GameObject a_oSender)
	{
		var oStatPopup = Function.CreateCopiedGameObject("StatPopup", "Prefabs/WaitScene/Popups/StatPopup", CSceneManager.UIRoot);
		var oCStatPopup = oStatPopup.GetComponent<CStatPopup>();
		oCStatPopup.m_oName = a_oSender.name;

		CSoundManager.Instance.PlayEffectSound("Sounds/Effect/ClickObject");
		Destroy(a_oSender);
	}

	public void OnTouchPrevButton(GameObject a_oSender)
	{
		Destroy(a_oSender);
		CSoundManager.Instance.PlayEffectSound("Sounds/Effect/ClickObject");
	}

	private void SetItemSlot(int a_nSlot, string a_oCardName)
	{
		var CurrentFrame = m_oFrames[a_nSlot / 9];

		if (CurrentFrame.transform.Find(a_oCardName) == null)
		{
			var oItem = Function.CreateCopiedGameObject(a_oCardName, "Prefabs/WaitScene/Card/Hero/" + a_oCardName, CurrentFrame);
			var oPosition = oItem.transform.localPosition;
			oPosition = new Vector3(-301.0f + ((a_nSlot - 1) * 87.0f), 0.0f, 0.0f);
			oItem.transform.localPosition = oPosition;
		}
	}

}
