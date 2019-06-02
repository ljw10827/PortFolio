using System.Collections;
using System.Collections.Generic;
using UnityEngine;

public class CBoss : CComponent
{
	public Animator m_oAnimator = null;
	public float m_fDelay = 0.0f;
	public int m_nWeaponNumber = 0;
	public bool m_bAttackEnable = false;
	public bool m_bIsAttack = false;
	public bool m_bIsEnemyTrigger { get; set; }
	public float m_fCurrentHp = 0.0f;
	public bool m_bIsDeath = false;

	public Transform m_oHpGauge = null;

	private float m_fOriginDelay = 0.0f;
	private Vector3 m_oOriginPosition;

	private int m_nAtk = 0;
	private int m_nDef = 0;
	private float m_fMaxHp = 0.0f;

	public override void Awake()
	{
		base.Awake();

		var oCharacters = GameObject.Find("Characters");

		var oController = oCharacters.GetComponent<CBossController>();
		this.m_bIsAttack = oController.m_bIsAttack;

		m_bIsEnemyTrigger = false;

		//적 리스트 만들어서 생성하기.
		var oList = CEnemyStorage.Instance.m_oEnemyInfoPair;
		var oEnemyInfo = oList[this.gameObject.name];

		this.m_fDelay = oEnemyInfo.m_fDelay;
		this.m_nAtk = oEnemyInfo.m_nAtk;
		this.m_nDef = oEnemyInfo.m_nDef;
		this.m_fMaxHp = oEnemyInfo.m_fHp;
		this.m_fCurrentHp = this.m_fMaxHp;



		this.m_oOriginPosition = this.gameObject.transform.localPosition;
		this.m_fOriginDelay = this.m_fDelay;

		m_oAnimator.SetInteger("Weapon", m_nWeaponNumber);
		m_oAnimator.SetFloat("Velocity Z", 1.0f);
	}

	public override void Update()
	{
		base.Update();

		if (!this.m_bIsAttack)
		{
			return;
		}

		if (!m_bAttackEnable)
		{
			m_fDelay -= Time.deltaTime;

			if (m_fDelay <= 0)
			{
				m_bAttackEnable = true;
				m_fDelay = m_fOriginDelay;
			}
		}
	}

	public void MoveEnemy(Vector3 a_oPosition)
	{
		//움직이고 도착후에 공격.
		m_oAnimator.SetBool("Moving", true);

		iTween.MoveTo(this.gameObject, iTween.Hash(
			 "position", (a_oPosition * 0.01f),
			 "Time", 1.0f,
			 "OnComplete", "AttackEnemy",
			 "OnCompleteTarget", this.gameObject,
			 "Space", Space.Self,
			 "easetype", iTween.EaseType.linear));

		//animation 비헤이버에 attackenable false 추가. 
	}

	public void AttackEnemy()
	{

		m_oAnimator.SetBool("Moving", false);

		m_oAnimator.SetTrigger("Attack1Trigger");

	}
	public void OnTriggerStay(Collider a_oCollider)
	{
		if (a_oCollider.gameObject.tag == "Player")
		{
			var oPlayer = a_oCollider.GetComponentInParent<CPlayer>();

			if (!oPlayer.m_bIsPlayerTrigger)
			{
				//Enemy에 최상단에 박스콜라이더.
				return;
			}

			else
			{
				oPlayer.m_bIsPlayerTrigger = false;
				this.Damage(oPlayer.DamageCalculate());
			}
		}
	}

	public void ReturnEnemy()
	{
		var oCharacters = CSceneManager.ObjectRoot.transform.Find("Characters");
		var oController = oCharacters.GetComponent<CBossController>();

		m_oAnimator.SetBool("Moving", true);

		if (!oController.m_bIsAttack)
		{
			iTween.MoveTo(this.gameObject, iTween.Hash(
			"position", this.m_oOriginPosition * 0.01f,
			"Time", 1.0f,
			"OnComplete", "ReturnEnd",
			"OnCompleteTarget", this.gameObject,
			"onCompleteParams", oController,
			 "easetype", iTween.EaseType.linear));

		}
	}

	public void DoAttack()
	{
		this.m_bIsEnemyTrigger = true;
	}

	public int DamageCalculate()
	{
		return Random.Range(this.m_nAtk, this.m_nAtk + 15);
	}

	private void ReturnEnd(CBossController a_oController)
	{
		this.transform.Rotate(0.0f, 180.0f, 0.0f);
		m_oAnimator.SetBool("Moving", false);
		m_bIsEnemyTrigger = false;
		a_oController.m_bIsAttack = true;
	}

	private void Damage(int a_nDamage)
	{
		var nCurrentDamage = a_nDamage - this.m_nDef;

		Mathf.Max(nCurrentDamage, 0.0f);

		m_fCurrentHp = this.m_fCurrentHp - nCurrentDamage;

		float fPercent = m_fCurrentHp / m_fMaxHp;

		var nScale = m_oHpGauge.localScale;
		var nScaleX = nScale.x * fPercent;
		nScaleX = Mathf.Max(nScaleX, 0.0f);
		nScale.x = nScaleX;
		m_oHpGauge.localScale = nScale;


		if (nScaleX > 0)
		{
			m_oAnimator.SetTrigger("GetHit1Trigger");
		}

		else
		{
			if (!m_bIsDeath)
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
