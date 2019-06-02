using System.Collections;
using System.Collections.Generic;
using UnityEngine;
using UnityEngine.UI;

public class CController : CComponent
{
	public CPlayer[] m_oPlayers = new CPlayer[3];
	public CButton[] m_oButtons = new CButton[6];
	public CEnemy[] m_oEnemies = new CEnemy[3];

	public Transform[] m_oEnemiesTransforms = null;
	public Transform[] m_oPlayerTransforms = null;

	public bool m_bIsAttack = true;

	private bool m_bIsPlayerOver = false;
	private bool m_bIsEnemyOver = false;

	public override void Awake()
	{
		base.Awake();

		var oCharacters = CSceneManager.ObjectRoot.transform.Find("Characters").gameObject;
		var oAtkButtons = GameObject.Find("AtkButtons");


		var oList = CCardStorage.Instance.m_oCardInfoList;
		for (int i = 0; i < oList.Count; ++i)
		{
			if (oList[i].m_bIsSelect)
			{
				var oParentButton = Function.CreateCopiedGameObject(oList[i].m_oName, "Prefabs/BattleUI/Character_01", oAtkButtons);
				var oPlayer = Function.CreateCopiedGameObject(oList[i].m_oName, "Prefabs/Character/" + oList[i].m_oName, oCharacters);

				var oButtonOne = oParentButton.transform.Find("Button_01").GetComponent<CButton>();
				var oButtonTwo = oParentButton.transform.Find("Button_02").GetComponent<CButton>();

				for (int j = 0; j < m_oButtons.Length; ++j)
				{
					if (m_oButtons[j] == null)
					{
						m_oButtons[j] = oButtonOne;
						m_oButtons[j + 1] = oButtonTwo;

						m_oPlayers[j / 2] = oPlayer.GetComponent<CPlayer>();
						m_oPlayers[j / 2].m_oHpGauge = oParentButton.transform.Find("CharacterGauge").GetComponent<Image>();
						m_oPlayers[j / 2].m_oCharacterImage = oParentButton.transform.Find("CharacterImage").GetComponent<Image>();

						m_oPlayers[j / 2].m_oCharacterImage.sprite = CResourceManager.Instance.GetSpriteForKey("Textures/WaitScene/Card/Mini/" + m_oPlayers[j / 2].gameObject.name);

						break;
					}
				}

			}
		}

		for (int i = 0; i < m_oPlayers.Length; ++i)
		{
			var oPlayerPosition = m_oPlayers[i].transform.localPosition;
			oPlayerPosition.z = m_oPlayerTransforms[i].localPosition.z;

			m_oPlayers[i].transform.localPosition = oPlayerPosition;
		}


		for (int i = 0; i < 6; ++i)
		{
			if (i % 2 == 0)
			{
				var oPosition = m_oButtons[i].transform.parent.localPosition;
				oPosition.x = 398.0f * (i / 2);
				m_oButtons[i].transform.parent.localPosition = oPosition;
			}

			m_oButtons[i].m_oCharacterName = m_oPlayers[i / 2].gameObject.name;
			m_oButtons[i].m_oSkillName = m_oPlayers[i / 2].gameObject.name + ((i % 2) + 1);



			m_oButtons[i].SettingOnClick(this);
		}

		m_bIsAttack = true;
		
		Function.LateCall((a_oParams) =>
		{
			for (int i = 0; i < m_oButtons.Length; ++i)
			{
				m_oButtons[i].m_fSkillDelay = m_oPlayers[i / 2].m_fDelay;
			}
		}, 0.0f);


	}

	public override void Update()
	{
		base.Update();

		if (m_bIsEnemyOver || m_bIsPlayerOver)
		{
			if (m_bIsEnemyOver)
			{
				CSceneManager.CurrentSceneManager.SendMessage("OnEnablePanel");
			}

			else
			{
				CSceneManager.CurrentSceneManager.SendMessage("OnEnableLosePanel");
			}

			return;
		}


		for (int i = 0; i < m_oEnemies.Length; ++i)
		{
			if (m_oEnemies[i].m_bAttackEnable)
			{
				this.EnemyAttack(m_oEnemies[i]);
			}

			m_oEnemies[i].m_bIsAttack = this.m_bIsAttack;
		}
	}

	public void PlayerAttack(CButton a_oSender)
	{
		if (m_bIsPlayerOver || m_bIsEnemyOver)
		{
			return;
		}

		if (m_bIsAttack && !a_oSender.m_bIsCooldown)
		{ 
			for (int i = 0; i < m_oButtons.Length; ++i)
			{
				if (a_oSender == m_oButtons[i])
				{
					if (m_oPlayers[i / 2].m_bIsDeath)
					{
						return;
					}
					var oRandomNumber = Random.Range(0, 3);

					if (m_oEnemies[oRandomNumber].m_bIsDeath)
					{
						while (m_oEnemies[oRandomNumber].m_bIsDeath)
						{
							oRandomNumber = Random.Range(0, 3);

							if (!m_oEnemies[oRandomNumber].m_bIsDeath)
							{
								break;
							}
						}

					}

					if (a_oSender.name == "Button_01")
					{
						m_oPlayers[i / 2].MovePlayer(1, m_oEnemiesTransforms[oRandomNumber].localPosition);
						m_oButtons[i].SkillCoolDown();
					}

					else
					{
						m_oPlayers[i / 2].MovePlayer(2, m_oEnemiesTransforms[oRandomNumber].localPosition);
						m_oButtons[i].SkillCoolDown();
					}
					break;
				}
			}
			m_bIsAttack = false;
		}
	}

	public void EnemyAttack(CEnemy a_oEnemy)
	{
		if (m_bIsAttack && a_oEnemy.m_bAttackEnable)
		{
			if (a_oEnemy.m_bIsDeath)
			{
				return;
			}

			var nSkillNumber = Random.Range(1, 3);
			var oRandomPlayer = Random.Range(0, 3);
			if (m_oPlayers[oRandomPlayer].m_bIsDeath)
			{
				while (m_oPlayers[oRandomPlayer].m_bIsDeath)
				{
					oRandomPlayer = Random.Range(0, 3);

					if (!m_oPlayers[oRandomPlayer].m_bIsDeath)
					{
						break;
					}
				}

			}
			a_oEnemy.MoveEnemy(nSkillNumber, m_oPlayerTransforms[oRandomPlayer].localPosition);


			m_bIsAttack = false;
		}
	}

	public void ReturnPlayer(CPlayer a_oPlayer)
	{
		a_oPlayer.ReturnPlayer();

		Function.LateCall((a_oParams) =>
		{
			for (int i = 0; i < m_oEnemies.Length; ++i)
			{
				if (!m_oEnemies[i].m_bIsDeath)
				{
					return;
				}
			}

			m_bIsEnemyOver = true;
		}, 0.0f);
	}

	public void ReturnEnemy(CEnemy a_oEnemy)
	{
		a_oEnemy.ReturnEnemy();

		for (int i = 0; i < m_oPlayers.Length; ++i)
		{
			if (!m_oPlayers[i].m_bIsDeath)
			{
				return;
			}
		}

		m_bIsPlayerOver = true;
	}
}

