#include "CSceneManager.h"

CSceneManager::~CSceneManager(void)
{
	SAFE_DELETE(_sceneObject);
}

void CSceneManager::init(void)
{
}

CSceneObject * CSceneManager::getSceneObject()
{
	return _sceneObject;
}

void CSceneManager::replaceSceneObject(CSceneObject * sceneObject)
{
	SAFE_DELETE(_sceneObject);
	_sceneObject = sceneObject;
}
