#pragma once

#include "../../Global/Utility/Base/CRenderObject.h"

// ¸Ê
class CTeraMap : public CRenderObject
{
public:
	virtual void init();

	virtual float getHeightMapY(const D3DXVECTOR3 & pos) = 0;
};