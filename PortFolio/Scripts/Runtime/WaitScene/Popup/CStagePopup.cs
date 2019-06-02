using System.Collections;
using System.Collections.Generic;
using UnityEngine;
using UnityEngine.UI;

public class CStagePopup : CComponent
{
	private enum EChapter
	{
		CHAPTER_1 = 1,
		CHAPTER_2,
		CHAPTER_3,
		CHAPTER_FINAL,
		NONE = 5
	};

	public GameObject m_oRightArrow = null;
	public GameObject m_oLeftArrow = null;
	public Image m_oChapterFrame = null;

	private EChapter m_eChapter = EChapter.NONE;
	private string m_oBaseFilepath = "";
	private string m_oChapterScene = "";
	

	public override void Awake()
	{
		base.Awake();
		m_eChapter = EChapter.CHAPTER_1;
		m_oBaseFilepath = "Textures/WaitScene/PopupComponent/StagePopup/";
		m_oChapterScene = "Chapter1-" + (int)m_eChapter + "Scene";
		var Filepath = m_oBaseFilepath + "Chapter1-" + (int)m_eChapter + "Frame";
		Function.ShowLog(Filepath);
		this.SettingPopup();
	}

	public override void Update()
	{
		base.Update();
		this.SettingPopup();
	}

	public void OnTouchRightArrow(Button a_oSender)
	{
		m_eChapter++;
		m_oChapterScene = "Chapter1-" + (int)m_eChapter + "Scene";
		CSoundManager.Instance.PlayEffectSound("Sounds/Effect/ClickEffect");
	}

	public void OnTouchLeftArrow(Button a_oSender)
	{
		m_eChapter--;
		m_oChapterScene = "Chapter1-" + (int)m_eChapter + "Scene";
		CSoundManager.Instance.PlayEffectSound("Sounds/Effect/ClickEffect");
	}

	public void OnTouchStartButton(Button a_oSender)
	{
		Color oColorBlack = Color.black;
		Initiate.Fade(m_oChapterScene, oColorBlack, 1.5f);
		CSoundManager.Instance.PlayEffectSound("Sounds/Effect/EnterEffect");
	}

	public void OnTouchExitButton(Button a_oSender)
	{
		if (this.gameObject.activeSelf)
		{
			this.gameObject.SetActive(false);
			CSoundManager.Instance.PlayEffectSound("Sounds/Effect/ClickObject");
		}
	}

	private void SettingPopup()
	{
		m_oLeftArrow.SetActive(m_eChapter > EChapter.CHAPTER_1);
		m_oRightArrow.SetActive(m_eChapter < EChapter.CHAPTER_FINAL);
		m_oChapterFrame.sprite = CResourceManager.Instance.GetSpriteForKey(m_oBaseFilepath + "Chapter1-" + (int)m_eChapter + "Frame");
	}
}
