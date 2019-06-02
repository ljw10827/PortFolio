#include "bossRoom.h"

#include "../Global/Utility/Manage/CWindowManager.h"
#include "../Global/Utility/Base/CDirect3DApplication.h"
#include "../Global/Utility/Manage/CDeviceManager.h"
#include "../Global/Utility/Manage/CResourcesManager.h"
#include "../Global/Utility/Object/CStaticMesh.h"
#include "../Global/Utility/Object/CCamera.h"

#include "../Global/Utility/Object/CSkinnedMesh.h"
#include "../Global/Utility/Object/CStaticMesh_AlphaControl.h"
#include "../Global/Utility/UI/CSprite_MapUI.h"

#include "../Global/Utility/Manage/CInputManager.h"
#include "../Global/Utility/Manage/CTimeManager.h"

bossRoom::bossRoom(void)
{
}

bossRoom::~bossRoom(void)
{
}


void bossRoom::init(void)
{
	m_pSphere = createSphere();
	m_pEffect = GET_EFEECT("Resources/Effects/Example_27.fx");
	m_pCubeTexture = GET_CUBETEXTURE("Resources/MapResources/skyBox/temple/Texture1.dds");

	m_pStaticTemple[0] = this->createStaticMeshMap("Resources/MapResources/bossRoom/temple/1/temple1.x");
	m_pStaticTemple[0]->setScale(D3DXVECTOR3(1.0f, 1.0f, 1.0f));
	m_pStaticTemple[0]->setPosition(D3DXVECTOR3(0.0f, 0.0f, 0.0f));

	m_pStaticTemple[1] = this->createStaticMeshMap("Resources/MapResources/bossRoom/temple/1/temple1.x");
	m_pStaticTemple[1]->setScale(D3DXVECTOR3(1.0f, 1.0f, 1.0f));
	m_pStaticTemple[1]->setPosition(D3DXVECTOR3(0.0f, 0.0f, 0.0f));
	m_pStaticTemple[1]->rotateByYAxis(180);

	m_pStaticTemple[2] = this->createStaticMeshMap("Resources/MapResources/bossRoom/temple/2/temple2.x");
	m_pStaticTemple[2]->setScale(D3DXVECTOR3(1.0f, 1.0f, 1.0f));
	m_pStaticTemple[2]->setPosition(D3DXVECTOR3(0.0f, 0.0f, 0.0f));

	m_pStaticTemple[3] = this->createStaticMeshMap("Resources/MapResources/bossRoom/temple/2/temple2.x");
	m_pStaticTemple[3]->setScale(D3DXVECTOR3(1.0f, 1.0f, 1.0f));
	m_pStaticTemple[3]->setPosition(D3DXVECTOR3(0.0f, 0.0f, 0.0f));
	m_pStaticTemple[3]->rotateByYAxis(180);

	m_pStaticFloor = this->createStaticMeshMapAlpha("Resources/MapResources/bossRoom/floor/5/floor5.x");
	m_pStaticFloor->setPosition(D3DXVECTOR3(0.0f, -8.0f, 0.0f));
	m_pStaticFloor->setScale(D3DXVECTOR3(10.0f, 10.0f, 10.0f));

	m_pBoss = this->createSkinnedMesh();
	m_pBoss->setScale(D3DXVECTOR3(0.1f, 0.1f, 0.1f));
	m_pBoss->setPosition(D3DXVECTOR3(0.0f, 20.0f, 1.0f));
	m_pBoss->setDebugEnable(true, EDebugType::Box);

	// 이 크기가 커지면 레이더에서 잡히는 거리는 실제로 상당한 거리가 있는 느낌으로 된다.
	m_totalMapSize.cx = 512;
	m_totalMapSize.cy = 512;

	m_RadarSize.cx = 193;
	m_RadarSize.cy = 194;
	m_RadarBaseSize.cx = 256;
	m_RadarBaseSize.cy = 256;
	
	m_pRadar = new CSprite_MapUI("Resources/MapResources/wowTestMapEx/Rader.tga");
	m_pRadar->SetMapUIPosition(D3DXVECTOR3(GET_WINDOW_SIZE().cx - m_RadarSize.cx / 2, m_RadarSize.cy / 2, 0.0f));

	m_pRadarBase = new CSprite_MapUI("Resources/MapResources/wowTestMapEx/RaderBase.png");
	m_pRadarBase->SetMapUIPosition(m_pRadar->getPosition());

	m_pEnemy = new CSprite_MapUI("Resources/MapResources/wowTestMapEx/enemy.png");

	auto EnemyPersentX = (m_pBoss->getPosition().x + m_totalMapSize.cx / 2.0f) / m_totalMapSize.cx;
	auto EnemyPersentY = 1 - (m_pBoss->getPosition().z + m_totalMapSize.cy / 2.0f) / m_totalMapSize.cy;

	D3DXMATRIXA16 stOffsetMatrix;
	D3DXMatrixTranslation(&stOffsetMatrix,
		m_RadarBaseSize.cx * EnemyPersentX - m_RadarBaseSize.cx / 2.0f,
		m_RadarBaseSize.cy * EnemyPersentY - m_RadarBaseSize.cy / 2.0f,
		0);
	m_pEnemy->SetMapUIOffsetPosition(stOffsetMatrix);
	m_pEnemy->SetMapUIPosition(D3DXVECTOR3(m_pRadar->GetMapUIPosition().x, m_pRadar->GetMapUIPosition().y, 0.0f));
}

void bossRoom::update(void)
{
	for (int i = 0; i < 4; ++i)
	{
		m_pStaticTemple[i]->update();
	}

	m_pStaticFloor->update();

	m_pEnemy->update();

	this->radarSetting(m_pBoss->getPosition());

	m_pBoss->update();

	auto oAnimationNameList = m_pBoss->getAnimationNameList();

	if (IS_KEY_PRESSED(DIK_1))
	{
		m_pBoss->PlayAnimation("BreathFront", false, [=](const std::string &animName)->void {
			m_pBoss->PlayAnimation("Wait", true);
		});
	}
	if (IS_KEY_PRESSED(DIK_2))
	{
		m_pBoss->PlayAnimation("BreathFlankRightStart", false, [=](const std::string &animName)->void {
			m_pBoss->PlayAnimation("BreathFlankRightLoop", false, [=](const std::string &animName)->void {
				m_pBoss->PlayAnimation("BreathFlankRightEnd", false, [=](const std::string &animName)->void {
					m_pBoss->PlayAnimation("Wait", true);
				});
			});
		});
	}
	if (IS_KEY_PRESSED(DIK_3))
	{
		m_pBoss->PlayAnimation("BreathFlankLeftStart", false, [=](const std::string &animName)->void {
			m_pBoss->PlayAnimation("BreathFlankLeftLoop", false, [=](const std::string &animName)->void {
				m_pBoss->PlayAnimation("BreathFlankLeftEnd", false, [=](const std::string &animName)->void {
					m_pBoss->PlayAnimation("Wait", true); 
				});
			});
		});
	}
	if (IS_KEY_PRESSED(DIK_4))
	{
		m_pBoss->PlayAnimation("BlowRightStart", false, [=](const std::string &animName)->void {
			m_pBoss->PlayAnimation("BlowRightShot", false, [=](const std::string &animName)->void {
				m_pBoss->PlayAnimation("BlowRightEnd", false, [=](const std::string &animName)->void {
					m_pBoss->PlayAnimation("Wait", true); 
				});
			});
		});
	}
	if (IS_KEY_PRESSED(DIK_5))
	{
		m_pBoss->PlayAnimation("BlowLeftStart", false, [=](const std::string &animName)->void {
			m_pBoss->PlayAnimation("BlowLeftShot", false, [=](const std::string &animName)->void {
				m_pBoss->PlayAnimation("BlowLeftEnd", false, [=](const std::string &animName)->void {
					m_pBoss->PlayAnimation("Wait", true);
				});
			});
		});
	}
	if (IS_KEY_PRESSED(DIK_6))
	{
		m_pBoss->PlayAnimation("BlowHeadStart", false, [=](const std::string &animName)->void {
			m_pBoss->PlayAnimation("BlowHeadShot", false, [=](const std::string &animName)->void {
				m_pBoss->PlayAnimation("BlowHeadR", false, [=](const std::string &animName)->void {
					m_pBoss->PlayAnimation("Wait", true);
				});
			});
		});
	}
	if (IS_KEY_PRESSED(DIK_7))
	{
		m_pBoss->PlayAnimation("BlowBatterStart", false, [=](const std::string &animName)->void {
			m_pBoss->PlayAnimation("BlowBatterShot01", false, [=](const std::string &animName)->void {
				m_pBoss->PlayAnimation("BlowBatterR", false, [=](const std::string &animName)->void {
					m_pBoss->PlayAnimation("Wait", true);
				});
			});
		});
	}
	if (IS_KEY_PRESSED(DIK_8))
	{
		m_pBoss->PlayAnimation("BlowBatterShot02Start", false, [=](const std::string &animName)->void {
			m_pBoss->PlayAnimation("BlowBatterShot02End", false, [=](const std::string &animName)->void {
				m_pBoss->PlayAnimation("BlowBatterR", false, [=](const std::string &animName)->void {
					m_pBoss->PlayAnimation("Wait", true);
				});
			});
		});
	}
	if (IS_KEY_PRESSED(DIK_9))
	{
		m_pBoss->PlayAnimation("Phase4_BlowLeft", false, [=](const std::string &animName)->void {
			m_pBoss->PlayAnimation("Wait", true);
		});
	}
	if (IS_KEY_PRESSED(DIK_0))
	{
		m_pBoss->PlayAnimation("Phase4_BlowRight", false, [=](const std::string &animName)->void {
			m_pBoss->PlayAnimation("Wait", true);
		});
	}
	if (IS_KEY_PRESSED(DIK_Z))
	{
		m_pBoss->PlayAnimation("BreathJumpStart", false, [=](const std::string &animName)->void {
			m_pBoss->PlayAnimation("BreathJumpLoop", false, [=](const std::string &animName)->void {
				m_pBoss->PlayAnimation("BreathJumpEnd", false);
			});
		});
	}
	if (IS_KEY_PRESSED(DIK_X))
	{
		m_pBoss->PlayAnimation("BreathJumpShot", false, [=](const std::string &animName)->void {
			m_pBoss->PlayAnimation("BreathJumpShotLoop", false, [=](const std::string &animName)->void {
				m_pBoss->PlayAnimation("BreathJumpShotEnd", false, [=](const std::string &animName)->void {
					m_pBoss->PlayAnimation("BreathJumpLoop", true);
				});
			});
		});
	}
	if (IS_KEY_PRESSED(DIK_C))
	{
		m_pBoss->PlayAnimation("BreathJumpShot", false, [=](const std::string &animName)->void {
			m_pBoss->PlayAnimation("BreathJumpShotEnd", false, [=](const std::string &animName)->void {
				m_pBoss->PlayAnimation("BreathJumpLoop", false);
			});
		});
	}
	if (IS_KEY_PRESSED(DIK_V))
	{
		m_pBoss->PlayAnimation("End01", false, [=](const std::string &animName)->void {
			m_pBoss->PlayAnimation("FlyHighLoop", false, [=](const std::string &animName)->void {
				m_pBoss->PlayAnimation("FlyHighEnd", false, [=](const std::string &animName)->void {
					m_pBoss->PlayAnimation("Wait", false);
				});
			});
		});
	}

	if (IS_KEY_PRESSED(DIK_F))
	{
		m_pBoss->PlayAnimation("AngryStart", false, [=](const std::string &animName)->void {
			m_pBoss->PlayAnimation("AngryLoop", false, [=](const std::string &animName)->void {
				m_pBoss->PlayAnimation("AngryEnd", false);
			});
		});
	}
	if (IS_KEY_PRESSED(DIK_G))
	{
		m_pBoss->PlayAnimation("Groggy", true);
	}
	if (IS_KEY_PRESSED(DIK_H))
	{
		m_pBoss->PlayAnimation("Flinch", true);
	}
	if (IS_KEY_PRESSED(DIK_J))
	{
		m_pBoss->PlayAnimation("Phase4_End01", false);
	}
	if (IS_KEY_PRESSED(DIK_T))
	{
		m_pBoss->PlayAnimation("RoundAtk01R", false, [=](const std::string &animName)->void {
			m_pBoss->PlayAnimation("RoundAtk01Start", false, [=](const std::string &animName)->void {
				m_pBoss->PlayAnimation("RoundAtk01End", false, [=](const std::string &animName)->void {
					m_pBoss->PlayAnimation("Wait", true);
				});
			});
		});
	}
}

void bossRoom::draw(void)
{
	this->skyBoxDraw();

	for (int i = 0; i < 4; ++i)
	{
		m_pStaticTemple[i]->draw();
	}
	m_pStaticFloor->draw();

	//GET_DEVICE()->SetRenderState(D3DRS_ALPHABLENDENABLE, true);
	//m_pSinnedMeshFloor->draw();

	m_pBoss->draw();
}

void bossRoom::drawUI(void)
{
	m_pRadar->drawUI();

	if (bIsEnemyDraw)
	{
		m_pEnemy->drawUI();
	}
}

void bossRoom::skyBoxDraw(void)
{
	D3DXMATRIXA16 stWorldMatrix;
	D3DXMatrixIdentity(&stWorldMatrix);
	GET_DEVICE()->SetTransform(D3DTS_WORLD, &stWorldMatrix);

	D3DXMATRIXA16 stViewMatrix = GET_CAMERA()->getviewMatirx();
	D3DXMATRIXA16 stProjectionMatrix = GET_CAMERA()->getProjectionMatrix();

	m_pEffect->SetMatrix("g_stWorldMatrix", &stWorldMatrix);
	m_pEffect->SetMatrix("g_stViewMatrix", &stViewMatrix);
	m_pEffect->SetMatrix("g_stProjectionMatrix", &stProjectionMatrix);
	m_pEffect->SetTexture("g_CubeTexture", m_pCubeTexture);
	m_pEffect->SetTechnique("MyTechnique");

	UINT nNumger = 0;
	m_pEffect->Begin(&nNumger, 0);

	for (int i = 0; i < nNumger; ++i)
	{
		m_pEffect->BeginPass(i);

		m_pSphere->DrawSubset(0);

		m_pEffect->EndPass();
	}
	m_pEffect->End();
}

LPD3DXMESH bossRoom::createSphere(void)
{
	LPD3DXMESH p_Mesh = nullptr;
	LPD3DXBUFFER pAdj = nullptr;

	D3DXCreateSphere(GET_DEVICE(), 350, 100, 50, &p_Mesh, &pAdj);

	// 법선 계산!
	D3DXComputeNormals(p_Mesh, (DWORD*)pAdj->GetBufferPointer());

	return p_Mesh;
}

CStaticMesh * bossRoom::createStaticMeshMap(std::string Filepath)
{
	CStaticMesh::STParameters stParameters = {
		Filepath,
		"Resources/Effects/Example_24.fx"
	};

	return new CStaticMesh(stParameters);
}

CStaticMesh_AlphaControl * bossRoom::createStaticMeshMapAlpha(std::string Filepath)
{
	CStaticMesh_AlphaControl::STParameters stParameters = {
	Filepath,
	"Resources/Effects/Example_24_AlphaControl.fx"
	};

	return new CStaticMesh_AlphaControl(stParameters, 0.6);
}

CSkinnedMesh * bossRoom::createSkinnedMesh(void)
{
	CSkinnedMesh::STParameters stParameters = {
		"Resources/MapResources/M_Vergos/Vergos.x",
		"Resources/Effects/Example_29.fx",
		"Dummy_root"
	};

	return new CSkinnedMesh(stParameters);
}

void bossRoom::radarSetting(const D3DXVECTOR3 & a_rtPosition)
{
	auto playerPersentX = (GET_CAMERA()->getPosition().x + m_totalMapSize.cx / 2.0f) / m_totalMapSize.cx;
	auto playerPersentY = 1 - (GET_CAMERA()->getPosition().z + m_totalMapSize.cy / 2.0f) / m_totalMapSize.cy;

	auto playerXPosition = m_RadarSize.cx * playerPersentX;
	auto playerYPosition = m_RadarSize.cy * playerPersentY;

	if (IS_MOUSE_DOWN((int)EMouseInput::RIGHT_BUTTON))
	{
		if (IS_MOUSE_PRESSED((int)EMouseInput::RIGHT_BUTTON))
		{
			m_stPrevMousePosition = GET_MOUSE_POSITION();
		}

		// 현재 마우스 위치 확인
		auto stMousePosition = GET_MOUSE_POSITION();
		m_pRadarAngle += stMousePosition.x - m_stPrevMousePosition.x;
		m_pRadarBase->SetMapUIRotation(-m_pRadarAngle);
		m_pEnemy->SetMapUIRotation(-m_pRadarAngle);
		m_stPrevMousePosition = stMousePosition;
	}

	auto moveLengthX = playerXPosition - m_RadarSize.cx / 2.0f;
	auto moveLengthY = playerYPosition - m_RadarSize.cy / 2.0f;

	auto EnemyPersentX = (a_rtPosition.x + m_totalMapSize.cx / 2.0f) / m_totalMapSize.cx;
	auto EnemyPersentY = 1 - (a_rtPosition.z + m_totalMapSize.cy / 2.0f) / m_totalMapSize.cy;

	auto enemyLocationX = -(m_RadarBaseSize.cx / 2.0f - m_RadarBaseSize.cx * EnemyPersentX) - moveLengthX;
	auto enemyLocationY = -(m_RadarBaseSize.cy / 2.0f - m_RadarBaseSize.cy * EnemyPersentY) - moveLengthY;

	D3DXMATRIXA16 stOffsetMatrix;
	D3DXMatrixTranslation(&stOffsetMatrix,
		enemyLocationX,
		enemyLocationY,
		0);
	m_pEnemy->SetMapUIOffsetPosition(stOffsetMatrix);

	auto enemyTruePositionX = m_pEnemy->GetMapUIPosition().x - enemyLocationX;
	auto enemyTruePositionY = m_pEnemy->GetMapUIPosition().y - enemyLocationY;
	D3DXVECTOR3 stenemyTruePosition = {
		enemyTruePositionX,
		enemyTruePositionY,
		0.0f
	};

	auto radarVisitDitance = m_pRadar->GetMapUIPosition() - stenemyTruePosition;
	if (D3DXVec3Length(&radarVisitDitance) <= m_RadarSize.cx / 2 - 25) // 레이더안의 원의 반지름을 얼추 맞추기 위한 조정
	{
		bIsEnemyDraw = true;
	}
	else
	{
		bIsEnemyDraw = false;
	}
}
