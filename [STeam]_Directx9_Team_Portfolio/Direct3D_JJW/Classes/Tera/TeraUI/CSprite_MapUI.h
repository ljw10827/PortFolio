#pragma once

#include "../../Global/Define/KGlobalDefine.h"
#include "../../Global/Utility/Base/CUIObject.h"

class CSprite_MapUI : public CUIObject
{
public:

	//UI�� �׸���
	// doDrawUI�� UI�ֻ��� ��ü CUIObject�� �����ϴ� ���� Ŭ������ �׸��� �ְ� �ϴ� �Լ��̴�.
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
	


	// ���� ������ ���� ����!
// �θ�
	CSprite_MapUI* m_pParrentObjectUI = nullptr;
	// �ڽ�
	std::vector<CSprite_MapUI *> m_childObjectListUI;
};