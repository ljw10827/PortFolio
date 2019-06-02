#pragma once

#include "../../Define/KGlobalDefine.h"
#include "../Base/CRenderObject.h"

//! ���� �޽�
class CStaticMesh : public CRenderObject
{
public:

	//! �Ű�����
	struct STParameters
	{
		std::string meshFilePath;
		std::string effectFilePath;
	};

public:			// ������

	//! ������
	explicit CStaticMesh(const STParameters &parameters);

public:			// public �Լ�
	
	virtual void preDrawObject(void) override;

	//! ��ü�� �׸���
	virtual void doDrawObject(void) override;

	virtual void postDrawObject(void) override;

private:		// private ����

	STStaticMesh _staticMesh;
	LPD3DXEFFECT _effect = nullptr;
	LPDIRECT3DTEXTURE9 _texture = nullptr;
};