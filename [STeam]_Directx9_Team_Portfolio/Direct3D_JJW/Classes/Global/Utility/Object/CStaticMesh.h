#pragma once

#include "../../Define/KGlobalDefine.h"
#include "../Base/CRenderObject.h"

//! 정적 메시
class CStaticMesh : public CRenderObject
{
public:

	//! 매개변수
	struct STParameters
	{
		std::string meshFilePath;
		std::string effectFilePath;
	};

public:			// 생성자

	//! 생성자
	explicit CStaticMesh(const STParameters &parameters);

public:			// public 함수
	
	virtual void preDrawObject(void) override;

	//! 객체를 그린다
	virtual void doDrawObject(void) override;

	virtual void postDrawObject(void) override;

private:		// private 변수

	STStaticMesh _staticMesh;
	LPD3DXEFFECT _effect = nullptr;
	LPDIRECT3DTEXTURE9 _texture = nullptr;
};