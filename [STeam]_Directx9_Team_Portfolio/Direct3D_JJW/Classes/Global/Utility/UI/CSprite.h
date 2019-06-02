#pragma once

#include "../../Define/KGlobalDefine.h"
#include "../Base/CUIObject.h"

//! 스프라이트
class CSprite : public CUIObject
{
public:			// public 함수

	virtual void update(void) override;

	//! UI를 그린다
	virtual void doDrawUI(void) override;

public:
	void setTexture(const std::string &textureFilepath);
	void setRectSize(int left, int right, int top, int bottom);
	void setTextureSize(int textureSizeX, int textureSizeY);
	void setSpriteScaleTemp(float sacleX, float sacleY, float posX = 1.0f, float posY = 1.0f){
		_scaleX = sacleX; _scaleY = sacleY; _posX = posX; _posY = posY;
	}

	void setScaleSprite(D3DXVECTOR3 scale, D3DXVECTOR2 transPos);


	SIZE getTextureSize(void);
	SIZE getOriginSize(void);

public:			// 생성자, 소멸자

	//! 생성자
	explicit CSprite(const std::string &textureFilePath);

	void setAlphaControl(int _alpha) { AlphaControl = _alpha; }

private:			// private 변수

	SIZE _textureSize;
	LPDIRECT3DTEXTURE9 _texture = nullptr;
	SIZE _originSize;

	int AlphaControl = 255;
	RECT _textureRect;

	D3DXVECTOR2 _transPos;

	D3DXVECTOR3 _scale;

	float _scaleX = 1.0f;
	float _scaleY = 1.0f;
	float _posX = 0.0f;
	float _posY = 0.0f;
};