#pragma once

#include "../../Define/KGlobalDefine.h"
#include "../Base/CRenderObject.h"

//! 스카이박스
class CSkybox : public CRenderObject
{
public:

	//! 매개변수
	struct STParameters
	{
		float radius;

		std::string effectFilePath;
		std::string cubeTextureFilePath;
	};
	
public:				// 생성자

	//! 생성자
	explicit CSkybox(const STParameters &parameters);

public:				// public 함수

	//! 객체를 그린다
	virtual void doDrawObject(void) override;

private:			// private 함수

	//! 메시를 생성한다
	LPD3DXMESH CreateMesh(const float radius);

private:			// private 변수

	LPD3DXMESH _mesh = nullptr;

	LPD3DXEFFECT _effect = nullptr;
	LPDIRECT3DCUBETEXTURE9 _cubeTexture = nullptr;
};
