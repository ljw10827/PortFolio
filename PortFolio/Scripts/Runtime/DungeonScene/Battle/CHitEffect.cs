using System.Collections;
using System.Collections.Generic;
using UnityEngine;

public class CHitEffect : CComponent
{

	public Transform m_oPlayerTransform = null;
	public GameObject m_oSkillEffect = null;

	private GameObject m_oParent = null;
	

	public override void Awake()
	{
		base.Awake();

		m_oParent = CSceneManager.ObjectRoot;

		m_oSkillEffect = Function.CreateCopiedGameObject(m_oSkillEffect.name, m_oSkillEffect, m_oParent);


		m_oSkillEffect.SetActive(false);

		m_oParent = CSceneManager.ObjectRoot;
	}

	public void HitEffect()
	{
		m_oSkillEffect.SetActive(true);

		var oPosition = m_oPlayerTransform.localPosition;
		oPosition.x += 50.0f;

		m_oSkillEffect.transform.localPosition = oPosition;

		Function.LateCall((a_oParams) =>
		{
			if (m_oSkillEffect.activeSelf)
			{
				m_oSkillEffect.SetActive(false);
			}
		}, 1.0f);

	}
}
