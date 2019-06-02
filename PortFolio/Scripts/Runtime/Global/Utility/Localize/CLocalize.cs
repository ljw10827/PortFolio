using System.Collections;
using System.Collections.Generic;
using UnityEngine;
using UnityEngine.UI;

//! 지역화
public class CLocalize : CComponent {
	#if NGUI
	private UILabel m_oLabel = null;
	#else
	private Text m_oText = null;
	#endif			// #if NGUI

	private string m_oLocalizeKey = "";

	//! 초기화
	public override void Awake() {
		base.Awake();

#if NGUI
		m_oLabel = this.GetComponentInChildren<UILabel>();
#else
		m_oText = this.GetComponentInChildren<Text>();
#endif			// #if NGUI

		Function.LateCall((a_oParams) => {
#if NGUI
			m_oLocalizeKey = m_oLabel.text;
#else
			m_oLocalizeKey = m_oText.text;
#endif            // #if NGUI

			this.ResetLocalize();
		}, 0.0f);
	}

	//! 상태를 갱신한다
	public override void Update() {
		base.Update();
	}

	//! 지역화를 리셋한다
	public void ResetLocalize() {
#if NGUI
		m_oLabel.text = CLocalizeManager.Instance.GetStringForKey(m_oLocalizeKey);
#else
		m_oText.text = CLocalizeManager.Instance.GetStringForKey(m_oLocalizeKey);
#endif           // #if NGUI
	}
}
