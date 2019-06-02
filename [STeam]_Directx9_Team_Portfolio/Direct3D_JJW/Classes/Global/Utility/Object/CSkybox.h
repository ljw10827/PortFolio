#pragma once

#include "../../Define/KGlobalDefine.h"
#include "../Base/CRenderObject.h"

//! ��ī�̹ڽ�
class CSkybox : public CRenderObject
{
public:

	//! �Ű�����
	struct STParameters
	{
		float radius;

		std::string effectFilePath;
		std::string cubeTextureFilePath;
	};
	
public:				// ������

	//! ������
	explicit CSkybox(const STParameters &parameters);

public:				// public �Լ�

	//! ��ü�� �׸���
	virtual void doDrawObject(void) override;

private:			// private �Լ�

	//! �޽ø� �����Ѵ�
	LPD3DXMESH CreateMesh(const float radius);

private:			// private ����

	LPD3DXMESH _mesh = nullptr;

	LPD3DXEFFECT _effect = nullptr;
	LPDIRECT3DCUBETEXTURE9 _cubeTexture = nullptr;
};
