using System.Collections;
using System.Collections.Generic;
using UnityEngine;

//! 스프라이트 애니메이션
public class CSpriteAnimation : CComponent
{
	private bool m_bIsLoop = false;
	private bool m_bIsPlaying = false;

	private float m_fSkipTime = 0.0f;
	private float m_fDelayPerUnit = 0.0f;

	private int m_nIndex = 0;
	private CSprite m_oSprite = null;
	private string[] m_oFilepaths = null;

	//! 초기화
	public override void Awake()
	{
		base.Awake();
		m_oSprite = this.GetComponent<CSprite>();
	}

	//! 상태를 갱신한다
	public override void Update()
	{
		base.Update();

		if (m_bIsPlaying)
		{
			m_fSkipTime += Time.deltaTime;

			if (m_fSkipTime >= m_fDelayPerUnit)
			{
				m_fSkipTime = 0.0f;

				if (m_nIndex < m_oFilepaths.Length - 1)
				{
					var oFilepath = m_oFilepaths[++m_nIndex];
					m_oSprite.SetSprite(oFilepath);
				}
				else
				{
					if (!m_bIsLoop)
					{
						this.StopAnimation();
					}
					else
					{
						this.PlayAnimation(m_oFilepaths,
							m_fDelayPerUnit,
							m_bIsLoop);
					}
				}
			}
		}
	}

	//! 애니메이션을 재생한다
	public void PlayAnimation(string[] a_oFilepaths,
		float a_fDelayPerUnit,
		bool a_bIsLoop)
	{
		m_oFilepaths = a_oFilepaths;
		this.StopAnimation();

		m_bIsLoop = a_bIsLoop;
		m_bIsPlaying = true;
		m_fDelayPerUnit = a_fDelayPerUnit;
	}

	//! 애니메이션을 정지한다
	public void StopAnimation()
	{
		m_nIndex = 0;
		m_fSkipTime = 0.0f;
		m_bIsPlaying = false;

		var oFilepath = m_oFilepaths[m_nIndex];
		m_oSprite.SetSprite(oFilepath);
	}
}
