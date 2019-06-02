using System.Collections;
using System.Collections.Generic;
using UnityEngine;
using UnityEngine.UI;

public class CNoticePopup : CComponent
{
	public string m_oItemName = "";
	public CShopPopup m_oShopPopup = null;

	public override void Awake()
	{
		base.Awake();
	}

	public void OnTouchNoticeYesButton(Button a_oSender)
	{
		m_oShopPopup.Purchase(m_oItemName);
		Destroy(this.gameObject);
		CSoundManager.Instance.PlayEffectSound("Sounds/Effect/ClickObject");
	}

	public void OnTouchNoticeNoButton(Button a_oSender)
	{
		Destroy(this.gameObject);
		CSoundManager.Instance.PlayEffectSound("Sounds/Effect/ClickObject");
	}
}
