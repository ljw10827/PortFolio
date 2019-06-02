#pragma once

#include "../../Define/KGlobalDefine.h"


class CSceneObject;

//! 씬 관리자
class CSceneManager
{
public: // 소멸자

	virtual ~CSceneManager(void);

public:		// public 함수

	//! 싱글턴
	DECLARE_SINGLETON(CSceneManager);

	//! 초기화
	virtual void init(void);

public:		// getter

	//! 씬 객체를 반환한다
	CSceneObject * getSceneObject(void);
	
	//! 

	//! 씬을 변경한다
	virtual void replaceSceneObject(CSceneObject *sceneObject);

private:	// private 변수

	CSceneObject * _sceneObject = nullptr;

	CSceneObject * _nextSceneObject = nullptr;

};