using System.Collections;
using System.Collections.Generic;
using UnityEngine;
using UnityEngine.UI;

public class IntroScene : CSceneManager
{
	public Text m_oTouchText = null;
	private bool bIsPlusAlpha = true;
	private float m_fValue = 1.0f;

	public override void Awake()
	{
		base.Awake();
		CSoundManager.Instance.PlayBackgroundSound("Sounds/BG/IntroBG");

		var oTextColor = m_oTouchText.color;
		oTextColor.a = 0;
		m_oTouchText.color = oTextColor;

		iTween.ScaleBy(m_oTouchText.transform.gameObject, iTween.Hash("amount", new Vector3 (1.1f, 1.1f, 1.1f),
				"time", 0.5f,
				"easeType", iTween.EaseType.linear,
				"loopType", iTween.LoopType.pingPong));
	}

	public override void Update()
	{
		base.Update();
		this.ChangeAlphaText();
	}

	public void OnTouchText()
	{
		Color oColorBlack = Color.black;
		CSoundManager.Instance.PlayEffectSound("Sounds/Effect/EnterEffect");

		Initiate.Fade("WaitScene", oColorBlack, 0.5f);
	}

	private void ChangeAlphaText()
	{
		var oTextColor = m_oTouchText.color;
		oTextColor.a += Time.deltaTime * m_fValue;
		oTextColor.a = Mathf.Clamp(oTextColor.a, 0.0f, 1.0f);

		if (oTextColor.a <= 0.0f || oTextColor.a >= 1.0f)
		{
			m_fValue = -1.0f * m_fValue;
		}

		m_oTouchText.color = oTextColor;
	}
	
}
