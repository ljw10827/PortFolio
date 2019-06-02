#pragma once

#include "../../Define/KGlobalDefine.h"


class CSceneObject;

//! �� ������
class CSceneManager
{
public: // �Ҹ���

	virtual ~CSceneManager(void);

public:		// public �Լ�

	//! �̱���
	DECLARE_SINGLETON(CSceneManager);

	//! �ʱ�ȭ
	virtual void init(void);

public:		// getter

	//! �� ��ü�� ��ȯ�Ѵ�
	CSceneObject * getSceneObject(void);
	
	//! 

	//! ���� �����Ѵ�
	virtual void replaceSceneObject(CSceneObject *sceneObject);

private:	// private ����

	CSceneObject * _sceneObject = nullptr;

	CSceneObject * _nextSceneObject = nullptr;

};