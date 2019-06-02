#pragma once

#include "../../Global/Define/KGlobalDefine.h"
#include "../../Global/Utility/Base/CUIObject.h"

class CSprite_MapUI : public CUIObject
{
public:

	//UI를 그린다
	// doDrawUI는 UI최상위 객체 CUIObject가 제공하는 하위 클래스가 그릴수 있게 하는 함수이다.
	virtual void doDrawUI(void) override;

public:

	explicit CSprite_MapUI(const std::string & a_path);

	void SetMapUIRotation(float _angle);

	void SetMapUIPosition(D3DXVECTOR3 _vec3);

	void SetMapUIOffsetPosition(D3DXMATRIXA16 &_offsetMatrix);

	void SetMapUIBaseWorldMatrix(D3DXMATRIXA16 &_offeWorldMatrix);

	D3DXVECTOR3 GetMapUIPosition();

	void SetUIParrentObject(CSprite_MapUI * a_nParrentObject);

	bool _isDie = false;
	bool _isDraw = false;

private:
	SIZE m_stTextureSize;
	LPDIRECT3DTEXTURE9 m_pTexture = nullptr;

	float radarRotate = 0.0f;
	D3DXVECTOR3 radarPosition;
	D3DXMATRIXA16 offsetMatrix;
	D3DXMATRIXA16 BaseWorldMatrix;
	


	// 계층 구조를 위한 변수!
// 부모
	CSprite_MapUI* m_pParrentObjectUI = nullptr;
	// 자식
	std::vector<CSprite_MapUI *> m_childObjectListUI;
};