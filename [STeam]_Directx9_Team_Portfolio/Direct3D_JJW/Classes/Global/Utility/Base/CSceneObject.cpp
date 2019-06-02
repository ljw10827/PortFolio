#include "CSceneObject.h"
#include "CRenderObject.h"
#include "CUIObject.h"
#include "../../../Tera/Map/CTeraMap.h"

float CSceneObject::_completeInitCount = 0.0f;

CSceneObject::~CSceneObject(void)
{
	SAFE_DELETE(_player);
	SAFE_DELETE(_map);
	SAFE_DELETE(_teraUI);
}

void CSceneObject::init(void)
{

	// Do Nothing
}

void CSceneObject::update(void)
{
	CObject::update();
	_isUpdateEnd = false;
}

void CSceneObject::draw(void)
{
	_isDrawEnd = false;

	for (auto childObject : m_oChildObjectList) {

		// 일반적인 오브젝트를 그린다
		auto renderObject = dynamic_cast<CRenderObject *>(childObject);

		if (renderObject != nullptr) {
			renderObject->draw();
		}

		// 테라 맵을 그린다
		auto mapObject = dynamic_cast<CTeraEffect *>(childObject);

		if (mapObject != nullptr) {
			mapObject->draw();
		}
	}

	_isDrawEnd = true;
}

void CSceneObject::drawUI(void)
{
	_isDrawUIEnd = false;

	// UI를 그린다.
	for (auto childObject : m_oChildObjectList) {
		auto renderObject = dynamic_cast<CUIObject *>(childObject);

		if (renderObject != nullptr) {
			renderObject->drawUI();
		}

		// 캐릭터에 있는 UI를 그린다.
		auto monsterObject = dynamic_cast<CRenderObject *>(childObject);

		if (monsterObject != nullptr) {
			monsterObject->drawUI();
		}
	}

	_isDrawUIEnd = true;
}

