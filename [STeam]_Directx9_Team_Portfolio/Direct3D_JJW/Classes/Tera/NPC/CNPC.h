#pragma once

#include "../../Global/Define/KGlobalDefine.h"
#include "../../Global/Utility/Base/CRenderObject.h"

class CSkinnedMesh;
class CSprite;
class CQuestPopup;

//! 플레이어 클래스
class CNPC : public CRenderObject
{
public:
	enum class ENpcKind
	{
		NONE,
		NPC,
		ANIMAL
	};

public:			// 생성자

	//! 생성자
	explicit CNPC(const std::string & npcName);

	//! 소멸자
	virtual ~CNPC(void);

public:			// getter & setter

	//! 플레이어 드로우 여부를 설정한다.
	void setVisible(bool isVisible);


public:			// 인터페이스

	//! 초기화 한다
	void init(void);

	//! 업데이트 
	virtual void update(void) final override;

	void Move(void);

	void Animation(void);

private:

	//! 스킨드 메시를 생성한다
	CSkinnedMesh * CreateSkinnedMesh(void);

private:			// private 변수

	bool _isVisible = false;

	CSkinnedMesh * _skinnedMesh = nullptr;

	std::string _name = "";

	float _changeDirTime = 0.0f;
	float _changeDirTimer = 0.0f;

	D3DXVECTOR3 _direction;

	float _changeAnimTime = 0.0f;
	float _changeAnimTimer = 0.0f;

	D3DXVECTOR3 _playerPosition;

	bool _isMoveAnimal = false;

	float _moveSpeed = 0.0f;
	float _moveTime = 0.0f;
	float _moveTimer = 0.0f;

	ENpcKind _npcKind;
};