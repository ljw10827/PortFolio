using System.Collections;
using System.Collections.Generic;
using UnityEngine;
using UnityEngine.UI;

// hp float로 수정.(enemy같이)
//public으로 캐릭터이미지넣고 awake에서 이미지 경로 넣기.
//게이지도 넣어야될거같은데?
// awake는 컴포넌트를 부착하면 바로 실행 start는 한프레임뒤에 실행.

public class CPlayer : CComponent
{
	public Animator m_oAnimator = null;
	public float m_fDelay = 0.0f;
	public float m_fMaxHp = 0.0f;
	public int m_nWeaponnumber = 0;

	[HideInInspector]
	public bool m_bIsPlayerTrigger { get; set; }
	[HideInInspector]
	public bool m_bIsDeath = false;

	private Vector3 m_oOriginPosition;
	private float m_fCurrentHp = 0.0f;
	private int m_nAtk = 0;
	private int m_nDef = 0;
	private GameObject m_oPet = null;


	public Image m_oHpGauge = null;
	public Image m_oCharacterImage = null;

	public override void Awake()
	{
		base.Awake();

		
		Function.LateCall((a_oParams) =>
		{
			this.m_oOriginPosition = this.gameObject.transform.localPosition;
			this.m_bIsPlayerTrigger = false;

			var oCardList = CCardStorage.Instance.m_oCardInfoList;

			for (int i = 0; i < oCardList.Count; ++i)
			{
				if (oCardList[i].m_oName == this.gameObject.name)
				{
					m_fDelay = oCardList[i].m_fDelay;
					m_nAtk = oCardList[i].m_nAtk;
					m_nDef = oCardList[i].m_nDef;
					m_fMaxHp = oCardList[i].m_fHp;
				}

			}

			this.m_fCurrentHp = this.m_fMaxHp;

			if (this.gameObject.name == "Elf")
			{
				m_oPet = this.GetComponentInChildren<Animation>(true).gameObject;
			}

			m_oAnimator.SetInteger("Weapon", m_nWeaponnumber);
			m_oAnimator.SetFloat("Velocity Z", 1.0f);
			this.transform.Rotate(0.0f, 90.0f, 0.0f);

		}, 0.0f);
		

	}

	public void MovePlayer(int a_nSkillNumber, Vector3 a_oPosition)
	{
		//움직이고 도착후에 공격.
		m_oAnimator.SetBool("Moving", true);
		if (this.m_oPet != null)
		{
			m_oPet.SetActive(true);
		}

		iTween.MoveTo(this.gameObject, iTween.Hash(
			"position", (a_oPosition * 0.01f),
			"Time", 1.0f,
			 "OnComplete", "AttackPlayer",
			 "OnCompleteTarget", this.gameObject,
			 "onCompleteParams", a_nSkillNumber,
			 "Space", Space.Self,
			 "easetype", iTween.EaseType.linear));

	}

	public void AttackPlayer(int a_nSkillNumber)
	{

		m_oAnimator.SetBool("Moving", false);

		if (a_nSkillNumber == 1)
		{
			m_oAnimator.SetTrigger("Attack1Trigger");
		}

		else if (a_nSkillNumber == 2)
		{
			m_oAnimator.SetTrigger("Attack3Trigger");

			if (this.m_oPet != null)
			{
				m_oPet.SetActive(false);
			}

		}


	}

	public void ReturnPlayer()
	{
		var oParent = this.transform.parent;
		var oController = oParent.GetComponent<CController>();

		m_oAnimator.SetBool("Moving", true);

		if (this.m_oPet != null)
		{
			m_oPet.SetActive(true);
		}

		if (!oController.m_bIsAttack)
		{
			iTween.MoveTo(this.gameObject, iTween.Hash(
			"position", (this.m_oOriginPosition* 0.01f),
			"Time", 1.0f,
			"OnComplete", "ReturnEnd",
			"OnCompleteTarget", this.gameObject,
			"onCompleteParams", oController,
			 "Space", Space.Self,
			 "easetype", iTween.EaseType.linear));
		}
	}

	public void ReturnBossPlayer()
	{
		var oParent = this.transform.parent;
		var oController = oParent.GetComponent<CBossController>();

		m_oAnimator.SetBool("Moving", true);

		if (this.m_oPet != null)
		{
			m_oPet.SetActive(true);
		}

		if (!oController.m_bIsAttack)
		{
			iTween.MoveTo(this.gameObject, iTween.Hash(
			"position", (this.m_oOriginPosition * 0.01f),
			"Time", 1.0f,
			"OnComplete", "ReturnBossEnd",
			"OnCompleteTarget", this.gameObject,
			"onCompleteParams", oController,
			 "Space", Space.Self,
			 "easetype", iTween.EaseType.linear));

		}
	}

	private void ReturnBossEnd(CBossController a_oController)
	{
		this.transform.Rotate(0.0f, 180.0f, 0.0f);
		m_oAnimator.SetBool("Moving", false);
		a_oController.m_bIsAttack = true;
		this.m_bIsPlayerTrigger = false;

		if (this.m_oPet != null)
		{
			m_oPet.SetActive(false);
		}
	}

	private void ReturnEnd(CController a_oController)
	{
		this.transform.Rotate(0.0f, 180.0f, 0.0f);
		m_oAnimator.SetBool("Moving", false);
		a_oController.m_bIsAttack = true;
		this.m_bIsPlayerTrigger = false;

		if (this.m_oPet != null)
		{
			m_oPet.SetActive(false);
		}
	}

	public void OnTriggerStay(Collider a_oCollider)
	{
		if (a_oCollider.gameObject.tag == "Enemy")
		{
			var oEnemy = a_oCollider.GetComponentInParent<CEnemy>();
			if (!oEnemy.m_bIsEnemyTrigger)
			{
				return;
			}

			else
			{
				oEnemy.m_bIsEnemyTrigger = false;
				this.Damage(oEnemy.DamageCalculate());
			}

		}
	}

	public void DoAttack()
	{
		this.m_bIsPlayerTrigger = true;
	}

	public int DamageCalculate()
	{
		return Random.Range(this.m_nAtk, this.m_nAtk + 15);
	}

	public void BossDamage(int a_nDamage)
	{
		this.Damage(a_nDamage);
	}

	private void Damage(int a_nDamage)
	{
		var nCurrentDamage = a_nDamage - this.m_nDef;
		m_fCurrentHp = this.m_fCurrentHp - nCurrentDamage;

		float fPercent = m_fCurrentHp / m_fMaxHp;

		m_oHpGauge.fillAmount = fPercent;

		if(fPercent > 0)
		{
			m_oAnimator.SetTrigger("GetHit1Trigger");
		}

		else
		{
			if(!m_bIsDeath)
			{
				m_oAnimator.SetTrigger("Death1Trigger");
				m_bIsDeath = true;
			}
			
		}

		var oDamageEffect = Function.CreateCopiedGameObject("damageFlash", "Prefabs/BattleObject/damageFlash", CSceneManager.ObjectRoot);

		var oPosition = new Vector3(this.transform.localPosition.x, this.transform.localPosition.y + 60, this.transform.localPosition.z);

		oDamageEffect.transform.localPosition = oPosition;
		CSoundManager.Instance.PlayEffectSound("Sounds/Effect/HitEffect");
	}


}
