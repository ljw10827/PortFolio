#pragma once

#include "../../Global/Define/KGlobalDefine.h"
#include "../../Global/Utility/Base/CRenderObject.h"

class CSkinnedMesh;
class CSprite;
class CQuestPopup;

//! �÷��̾� Ŭ����
class CNPC : public CRenderObject
{
public:
	enum class ENpcKind
	{
		NONE,
		NPC,
		ANIMAL
	};

public:			// ������

	//! ������
	explicit CNPC(const std::string & npcName);

	//! �Ҹ���
	virtual ~CNPC(void);

public:			// getter & setter

	//! �÷��̾� ��ο� ���θ� �����Ѵ�.
	void setVisible(bool isVisible);


public:			// �������̽�

	//! �ʱ�ȭ �Ѵ�
	void init(void);

	//! ������Ʈ 
	virtual void update(void) final override;

	void Move(void);

	void Animation(void);

private:

	//! ��Ų�� �޽ø� �����Ѵ�
	CSkinnedMesh * CreateSkinnedMesh(void);

private:			// private ����

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