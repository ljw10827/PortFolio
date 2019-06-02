using System.Collections;
using System.Collections.Generic;
using UnityEngine;

//! 스프라이트
public class CSprite : CComponent
{
	private SpriteRenderer m_oSpriteRenderer = null;
	private CSpriteAnimation m_oSpriteAnimation = null;

	//! 초기화
	public override void Awake()
	{
		base.Awake();

		m_oSpriteRenderer = Function.AddComponent<SpriteRenderer>(this.gameObject);
		m_oSpriteAnimation = Function.AddComponent<CSpriteAnimation>(this.gameObject);
	}


	//! 스프라이트를 변경한다
	public void SetSprite(string a_oFilepath)
	{
		var oSprite = CResourceManager.Instance.GetSpriteForKey(a_oFilepath);
		m_oSpriteRenderer.sprite = oSprite;
	}

	//! 애니메이션을 재생한다
	public void PlayAnimation(string[] a_oFilepaths, 
		float a_fDelayPerUnit, 
		bool a_bIsLoop = false)
	{
		m_oSpriteAnimation.PlayAnimation(a_oFilepaths,
			a_fDelayPerUnit,
			a_bIsLoop);
	}

	//! 애니메이션을 정지한다
	public void StopAnimation()
	{
		m_oSpriteAnimation.StopAnimation();
	}
}
