using System.Collections;
using System.Collections.Generic;
using UnityEngine;
using UnityEngine.UI;

public class CMixNoticePopup : CComponent
{
	public string m_oItemName = "";
	public CMakingPopup m_oMakingPopup = null;

	public override void Awake()
	{
		base.Awake();
		Function.LateCall((a_oParams) =>
		{
			var oParent = this.transform.Find("Frame").gameObject;

			if (m_oItemName == "Sword")
			{
				var oContents = Function.CreateCopiedGameObject("SwordContents", "Prefabs/WaitScene/MixContents/SwordContents", oParent);
			}

			else if (m_oItemName == "Ring")
			{
				var oContents = Function.CreateCopiedGameObject("RingContents", "Prefabs/WaitScene/MixContents/RingContents", oParent);
			}

			else
			{
				var oContents = Function.CreateCopiedGameObject("ArmorContents", "Prefabs/WaitScene/MixContents/ArmorContents", oParent);
			}
		}, 0.0f);
	}


	public void OnTouchNoticeYesButton(Button a_oSender)
	{
		m_oMakingPopup.Mix(m_oItemName);
		Destroy(this.gameObject);
		CSoundManager.Instance.PlayEffectSound("Sounds/Effect/ClickObject");
	}

	public void OnTouchNoticeNoButton(Button a_oSender)
	{
		Destroy(this.gameObject);
		CSoundManager.Instance.PlayEffectSound("Sounds/Effect/ClickObject");
	}
}
