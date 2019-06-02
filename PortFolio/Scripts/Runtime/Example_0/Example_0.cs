using System.Collections;
using System.Collections.Generic;
using UnityEngine;
using UnityEngine.UI;
using UnityEngine.SceneManagement;

//! Example 0
public class Example_0 : CSceneManager {
	public Text[] m_oTexts = null;

	//! 초기화
	public override void Awake() {
		base.Awake();
		for(int i = 1; i < SceneManager.sceneCountInBuildSettings; ++i)
		{
			var oSceneName = SceneUtility.GetScenePathByBuildIndex(i);
			var oSplit = oSceneName.Split('/');
			m_oTexts[i - 1].text = oSplit[oSplit.Length - 1];
		}
		
	}

	//! 상태를 갱신한다
	public override void Update() {
		base.Update();
	}

	public void OnTouchButton(Button a_oSender)
	{
		var oButtons = CSceneManager.UIRoot.GetComponentsInChildren<Button>();

		for (int i = 0; i < oButtons.Length; ++i)
		{
			if (oButtons[i] == a_oSender)
			{
				CSceneChanger.Instance.ChangeScene((ESceneIndex)(i + 1), null);
				break;
			}
		}
	}
}
