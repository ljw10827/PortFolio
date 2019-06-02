#include "CSprite.h"
#include "../Manager/CResourceManager.h"
#include "../Base/CDirect3DApplication.h"
#include "../Manager/CWindowManager.h"
#include "../Manager/CDeviceManager.h"

CSprite::CSprite(const std::string & textureFilePath)
{
	_texture = GET_SPRITE_TEXTURE(textureFilePath);
	
	D3DSURFACE_DESC surfaceDesc;
	_texture->GetLevelDesc(0, &surfaceDesc);

	_textureSize.cx = surfaceDesc.Width;
	_textureSize.cy = surfaceDesc.Height;

	_textureRect = {
		0, 0, _textureSize.cx, _textureSize.cy
	};

	//원본 사이즈 저장
	_originSize = _textureSize;
	AlphaControl = 255.0f;

}

void CSprite::update(void)
{
	CObject::update();
	_textureRect = {
		0, 0, _textureSize.cx, _textureSize.cy
	};
	
}

void CSprite::doDrawUI(void)
{
	CUIObject::doDrawUI();
	D3DXMATRIXA16 scalingMatrix;
	D3DXMatrixTransformation2D(&scalingMatrix, &D3DXVECTOR2(_posX, _posY), 0.0f, &D3DXVECTOR2(_scaleX, _scaleY), NULL, NULL, NULL);

	GET_SPRITE()->Begin(D3DXSPRITE_ALPHABLEND | D3DXSPRITE_SORT_DEPTH_BACKTOFRONT);
	GET_DEVICE()->SetTransform(D3DTS_WORLD, &scalingMatrix);
	
	GET_SPRITE()->Draw(_texture,
		&_textureRect,
		&D3DXVECTOR3(_textureRect.left, _textureRect.top, 0.0f),
		&m_stPosition,
		/*_color*/
		D3DCOLOR_RGBA(255, 255, 255, AlphaControl));

	GET_SPRITE()->End();
}

//=============================함수 추가 =============================//

//텍스처 사이즈를 수정한다.
void CSprite::setTextureSize(int textureSizeX, int textureSizeY)
{
	_textureSize.cx = textureSizeX;
	_textureSize.cy = textureSizeY;
}


void CSprite::setTexture(const std::string & textureFilepath)
{
	_texture = GET_SPRITE_TEXTURE(textureFilepath);

	D3DSURFACE_DESC surfaceDesc;
	_texture->GetLevelDesc(0, &surfaceDesc);

	_textureSize.cx = surfaceDesc.Width;
	_textureSize.cy = surfaceDesc.Height;

}

void CSprite::setRectSize(int left, int right, int top, int bottom)
{
	_textureRect.left = left;
	_textureRect.right = right;
	_textureRect.top = top;
	_textureRect.bottom = bottom;
}

//텍스처 사이즈를 갖고온다.
SIZE CSprite::getTextureSize(void)
{
	return _textureSize;
}

// 원본 사이즈를 갖고온다.
SIZE CSprite::getOriginSize(void)
{
	return _originSize;
}

void CSprite::setScaleSprite(D3DXVECTOR3 scale, D3DXVECTOR2 transPos)
{
	_scaleX = scale.x;
	_scaleY = scale.y;

	_posX = transPos.x;
	_posY = transPos.y;
}
//=========================함수 추가 끝 ===================================//