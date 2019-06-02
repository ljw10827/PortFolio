#include "CRenderObject.h"
#include "../Manager/CDeviceManager.h"
#include "../Manager/CResourceManager.h"
#include "../Debug/CDebugDraw.h"
#include "../Base/CUIObject.h"
#include "../../../Tera/Player/CPlayer.h"
#include "../../../Tera/Monster/CMonster.h"

CRenderObject::CRenderObject(void)
	:
	m_bIsVisible(true)
{
	D3DXMatrixIdentity(&_shadowMatrix);
	ZeroMemory(&_shadowMaterial, sizeof(_shadowMaterial));

	_shadowMaterial.Diffuse = D3DXCOLOR(0.0f, 0.0f, 0.0f, 0.15f);
}

CRenderObject::~CRenderObject(void)
{
	SAFE_DELETE(_debugDraw);
}

void CRenderObject::drawUI(void)
{
	// 자식 객체 상태 갱신
	for (auto pChildObject : m_oChildObjectList) {

		auto renderObject = dynamic_cast<CUIObject *>(pChildObject);

		if (renderObject != nullptr && renderObject->getVisible()) {
			renderObject->drawUI();
		}
	}
}

void CRenderObject::draw(void)
{
	if (m_bIsVisible) {
		this->preDrawObject();
		this->doDrawObject();
		this->postDrawObject();

		if (_isShadowEnable) {
			this->preDrawShadow();
			this->doDrawShadow();
			this->postDrawShadow();
		}
	}

	if (_isDebugEnable && _debugDraw != nullptr) {
		_debugDraw->draw();
	}

	// 자식 UI 객체를 그린다
	for (auto childObject : m_oChildObjectList) {
		auto renderObject = dynamic_cast<CRenderObject *>(childObject);

		if (renderObject != nullptr) {

			if (m_bIsVisible) {
				renderObject->draw();
			}
		}
	}
}

void CRenderObject::setDebugEnable(const bool isEnable, const EDebugType debugType)
{
	if (_isDebugEnable != isEnable) {
		_isDebugEnable = isEnable;

		if (!isEnable) {
			SAFE_DELETE(_debugDraw);
		}
		else {
			_debugDraw = new CDebugDraw(this, debugType);
		}
	}
}

void CRenderObject::setShadowEnable(const bool isShadowEnable)
{
	if (_isShadowEnable != isShadowEnable) {
		_isShadowEnable = isShadowEnable;

		if (_isShadowEnable) {
			_shadowMesh = this->CreateShadowMesh();
		}
	}
}

void CRenderObject::setShadowMaterial(const D3DMATERIAL9 & shadowMaterial)
{
	_shadowMaterial = shadowMaterial;
}

void CRenderObject::setShadowMatrix(const D3DXMATRIXA16 & shadowMatrix)
{
	_shadowMatrix = shadowMatrix;
}

void CRenderObject::preDrawObject(void)
{
	// Do Nothing
}

void CRenderObject::doDrawObject(void)
{
	// Do Nothing
}

void CRenderObject::postDrawObject(void)
{
	// Do Nothing
}

void CRenderObject::preDrawShadow(void)
{
	GET_DEVICE()->SetRenderState(D3DRS_LIGHTING, true);

	GET_DEVICE()->SetRenderState(D3DRS_ALPHABLENDENABLE, true);
	GET_DEVICE()->SetRenderState(D3DRS_SRCBLEND, D3DBLEND_SRCALPHA);
	GET_DEVICE()->SetRenderState(D3DRS_DESTBLEND, D3DBLEND_INVSRCALPHA);

}

void CRenderObject::doDrawShadow(void)
{
	// Do Nothing
	
}

void CRenderObject::postDrawShadow(void)
{
	GET_DEVICE()->SetRenderState(D3DRS_LIGHTING, true);
	GET_DEVICE()->SetRenderState(D3DRS_ALPHABLENDENABLE, false);
}

LPD3DXMESH CRenderObject::CreateShadowMesh(void)
{
	LPD3DXMESH mesh = GET_MESH("DefaultShadowMesh");

	if (mesh != nullptr) {
		return mesh;
	}

	//! 메시를 생성한다
	D3DXCreateSphere(GET_DEVICE(),
		0.5f,
		25,
		25,
		&mesh,
		nullptr);

	GET_RESOURCE_MANAGER()->AddMeshForKey("DefaultShadowMesh", mesh);
	return mesh;
}
