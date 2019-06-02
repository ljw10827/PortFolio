#include "CSprite_MapUI.h"

#include "../../Global/Utility/Manager/CResourceManager.h"
			
#include "../../Global/Utility/Base/CDirect3DApplication.h"
			
#include "../../Global/Utility/Manager/CDeviceManager.h"

CSprite_MapUI::CSprite_MapUI(const std::string & a_path)
{
	m_pTexture = GET_SPRITE_TEXTURE(a_path);

	D3DSURFACE_DESC stSurfaceDesc;
	m_pTexture->GetLevelDesc(0, &stSurfaceDesc);

	m_stTextureSize.cx = stSurfaceDesc.Width;
	m_stTextureSize.cy = stSurfaceDesc.Height;

	radarRotate = 0;
	radarPosition.x = 0;
	radarPosition.y = 0;
	radarPosition.z = 0;

	D3DXMatrixIdentity(&offsetMatrix);
	D3DXMatrixIdentity(&BaseWorldMatrix);
}

void CSprite_MapUI::SetMapUIRotation(float _angle)
{
	radarRotate = _angle;
}

void CSprite_MapUI::SetMapUIPosition(D3DXVECTOR3 _vec3)
{
	radarPosition = _vec3;
}

void CSprite_MapUI::SetMapUIOffsetPosition(D3DXMATRIXA16 &_offsetMatrix)
{
	offsetMatrix = _offsetMatrix;
}

void CSprite_MapUI::SetMapUIBaseWorldMatrix(D3DXMATRIXA16 & _offeWorldMatrix)
{
	BaseWorldMatrix = _offeWorldMatrix;
}

D3DXVECTOR3 CSprite_MapUI::GetMapUIPosition()
{
	return radarPosition;
}

void CSprite_MapUI::SetUIParrentObject(CSprite_MapUI * a_nParrentObject)
{
	assert(m_pParrentObjectUI == nullptr);
	m_pParrentObjectUI = a_nParrentObject;
}

void CSprite_MapUI::doDrawUI(void)
{
	CUIObject::doDrawUI();

	//for (auto pChildObject : m_childObjectList)
	//{
	//	pChildObject->update();
	//}

	RECT stTextureRect = {
		0,0,m_stTextureSize.cx, m_stTextureSize.cy
	};

	D3DXMATRIXA16 stRotationZ;
	D3DXMatrixRotationZ(&stRotationZ, D3DXToRadian(radarRotate));

	D3DXMATRIXA16 stTranslation;
	D3DXMatrixTranslation(&stTranslation, radarPosition.x, radarPosition.y, radarPosition.z);

	GET_SPRITE()->Begin(D3DXSPRITE_ALPHABLEND |
		D3DXSPRITE_SORT_DEPTH_BACKTOFRONT);

	D3DXMATRIXA16 stWorldMatrix;
	stWorldMatrix = offsetMatrix * stRotationZ * stTranslation;

	GET_DEVICE()->SetTransform(D3DTS_WORLD, &stWorldMatrix);

	GET_SPRITE()->Draw(m_pTexture,
		&stTextureRect,
		&D3DXVECTOR3(stTextureRect.right / 2, stTextureRect.bottom / 2, 0.0f),
		&m_stPosition,
		_color);

	GET_SPRITE()->End();

	/*D3DXMatrixIdentity(&stWorldMatrix);
	GET_DEVICE()->SetTransform(D3DTS_WORLD, &stWorldMatrix);*/
}