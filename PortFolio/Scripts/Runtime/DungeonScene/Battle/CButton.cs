using System.Collections;
using System.Collections.Generic;
using UnityEngine;
using UnityEngine.UI;

public class CButton : CComponent
{
	public float m_fSkillDelay = 0.0f;
	public bool m_bIsCooldown = false;
	public string m_oCharacterName = "";
	public string m_oSkillName = "";
	private float m_fOriginDelay = 5.0f;
	private Image m_oCooldownImage = null;

	public override void Awake()
	{
		base.Awake();

		Function.LateCall((a_oParams) =>
		{
			var oFilepath = "Textures/BattleScene/SkillIcons/Color/" + m_oSkillName;
			var oSkillImage = this.GetComponent<Image>();
			m_oCooldownImage = this.transform.Find("CooldownImage").GetComponent<Image>();

			m_oCooldownImage.type = Image.Type.Filled;
			m_oCooldownImage.fillMethod = Image.FillMethod.Radial360;
			m_oCooldownImage.fillOrigin = 2;
			m_oCooldownImage.fillAmount = 1;

			oSkillImage.sprite = CResourceManager.Instance.GetSpriteForKey(oFilepath);
			m_oCooldownImage.sprite = CResourceManager.Instance.GetSpriteForKey(oFilepath);
			m_oCooldownImage.gameObject.SetActive(false);
		}, 0.0f);
		
		
		this.transform.parent.name = m_oCharacterName;
		Function.LateCall((a_oParams) =>
		{
			m_fOriginDelay = m_fSkillDelay;
			m_fSkillDelay = Mathf.Max(0.0f, m_fSkillDelay);
		}, 0.01f);
		
		
	}

	public override void Update()
	{
		base.Update();

		if (m_bIsCooldown)
		{
			m_oCooldownImage.gameObject.SetActive(true);
			m_fSkillDelay -= Time.deltaTime;

			if (m_fSkillDelay <= 0)
			{
				m_bIsCooldown = false;
				m_fSkillDelay = m_fOriginDelay;
				m_oCooldownImage.fillAmount = 1.0f;
				m_oCooldownImage.gameObject.SetActive(false);
			}

			float fPercent = m_fSkillDelay / m_fOriginDelay;

			m_oCooldownImage.fillAmount = fPercent;

		}
	}

	public void SkillCoolDown()
	{
		m_bIsCooldown = true;
	}

	public void SettingOnClick(CController a_oController)
	{
		var oButton = this.GetComponent<Button>();
		oButton.onClick.AddListener(() => a_oController.PlayerAttack(this));
	}

	public void SettingOnBossClick(CBossController a_oController)
	{
		var oButton = this.GetComponent<Button>();
		oButton.onClick.AddListener(() => a_oController.PlayerAttack(this));
	}
}
