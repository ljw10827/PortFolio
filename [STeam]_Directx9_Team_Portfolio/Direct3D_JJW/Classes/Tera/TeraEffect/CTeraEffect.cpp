#include "CTeraEffect.h"
#include "../../Global/Utility/Manager/CResourceManager.h"
#include "../../Global/Utility/Object/CCamera.h"
#include "../../Global/Utility/Base/CDirect3DApplication.h"
#include "../../Global/Utility/Manager/CDeviceManager.h"
#include "../../Global/Utility/Manager/CInputManager.h"

CTeraEffect::CTeraEffect(const std::wstring &filepath, EffectType effectType)
	:
	_effectType(effectType)
{
	_effekseer = GET_EFFEKSEER(filepath);
	_filepath = filepath;
	_position.x = 0;
	_position.y = 0;
	_position.z = 0;
}

CTeraEffect::~CTeraEffect()
{
}



void CTeraEffect::update()
{
	CRenderObject::update();
	effeckUpdate(_deltaTime);

	if (this->EffekExist())
	{
		if (_filepath == L"Resources/Effekseers/FireBallTest2.efk")
		{
			_count++;
			if (_count >= 210)
			{
				this->stopEffekseer();
				
			}
			//printf("%f \n", _count);
		}
	}
	else if(!this->EffekExist())
	{
		_count = 0;
	}
}




void CTeraEffect::doDrawObject(void)
{
	CRenderObject::doDrawObject();
	//ÇØ¾ßµÊ
	_effekseer._renderer->BeginRendering();

	_effekseer._manager->Draw();

	_effekseer._renderer->EndRendering();
}

void CTeraEffect::AddLocation(const D3DXVECTOR3 & addVector)
{
	_effekseer._manager->AddLocation(_effekseer._handle, ::Effekseer::Vector3D(addVector.x, addVector.y, addVector.z));
}


void CTeraEffect::effeckUpdate(float deltaTime)
{

	auto stProjectionMatrix = GET_CAMERA()->getProjectionMatrix();
	auto stViewMatrix = GET_CAMERA()->getViewMatrix();
	::Effekseer::Matrix44 stEffekProjectionMatrix;
	stEffekProjectionMatrix.Indentity();
	::Effekseer::Matrix44 stEffekViewMatrix;
	stEffekViewMatrix.Indentity();



	stEffekProjectionMatrix.Values[0][0] = stProjectionMatrix._11;
	stEffekProjectionMatrix.Values[0][1] = stProjectionMatrix._12;
	stEffekProjectionMatrix.Values[0][2] = stProjectionMatrix._13;
	stEffekProjectionMatrix.Values[0][3] = stProjectionMatrix._14;

	stEffekProjectionMatrix.Values[1][0] = stProjectionMatrix._21;
	stEffekProjectionMatrix.Values[1][1] = stProjectionMatrix._22;
	stEffekProjectionMatrix.Values[1][2] = stProjectionMatrix._23;
	stEffekProjectionMatrix.Values[1][3] = stProjectionMatrix._24;

	stEffekProjectionMatrix.Values[2][0] = stProjectionMatrix._31;
	stEffekProjectionMatrix.Values[2][1] = stProjectionMatrix._32;
	stEffekProjectionMatrix.Values[2][2] = stProjectionMatrix._33;
	stEffekProjectionMatrix.Values[2][3] = stProjectionMatrix._34;

	stEffekProjectionMatrix.Values[3][0] = stProjectionMatrix._41;
	stEffekProjectionMatrix.Values[3][1] = stProjectionMatrix._42;
	stEffekProjectionMatrix.Values[3][2] = stProjectionMatrix._43;
	stEffekProjectionMatrix.Values[3][3] = stProjectionMatrix._44;

	//-----------------------------------------------------------
	stEffekViewMatrix.Values[0][0] = stViewMatrix._11;
	stEffekViewMatrix.Values[0][1] = stViewMatrix._12;
	stEffekViewMatrix.Values[0][2] = stViewMatrix._13;
	stEffekViewMatrix.Values[0][3] = stViewMatrix._14;

	stEffekViewMatrix.Values[1][0] = stViewMatrix._21;
	stEffekViewMatrix.Values[1][1] = stViewMatrix._22;
	stEffekViewMatrix.Values[1][2] = stViewMatrix._23;
	stEffekViewMatrix.Values[1][3] = stViewMatrix._24;

	stEffekViewMatrix.Values[2][0] = stViewMatrix._31;
	stEffekViewMatrix.Values[2][1] = stViewMatrix._32;
	stEffekViewMatrix.Values[2][2] = stViewMatrix._33;
	stEffekViewMatrix.Values[2][3] = stViewMatrix._34;

	stEffekViewMatrix.Values[3][0] = stViewMatrix._41;
	stEffekViewMatrix.Values[3][1] = stViewMatrix._42;
	stEffekViewMatrix.Values[3][2] = stViewMatrix._43;
	stEffekViewMatrix.Values[3][3] = stViewMatrix._44;



	_effekseer._renderer->SetCameraMatrix(stEffekViewMatrix);
	_effekseer._renderer->SetProjectionMatrix(stEffekProjectionMatrix);

	//===============================================================================

	_effekseer._manager->Update(deltaTime);
}


void CTeraEffect::setDeltaTime(float deltaTime)
{
	_deltaTime = deltaTime;
}

void CTeraEffect::playEffeckseer(const D3DXVECTOR3 &position, const int startFrame)
{
	Effekseer::Matrix43 baseTempMatrix;
	baseTempMatrix = _effekseer._manager->GetBaseMatrix(_effekseer._handle);
	baseTempMatrix.Indentity();

	_effekseer._handle = _effekseer._manager->Play(_effekseer._effect, Effekseer::Vector3D(position.x, position.y, position.z), startFrame);
	_effekseer._manager->SetBaseMatrix(_effekseer._handle, baseTempMatrix);
	_effekseer._manager->GetBaseMatrix(_effekseer._handle);

	Effekseer::Matrix43 temp;
	Effekseer::Matrix43 offsetMat;

	offsetMat.Indentity();
	temp.Indentity();

	temp = _effekseer._manager->GetMatrix(_effekseer._handle);
	Effekseer::Matrix43::Multiple(offsetMat, temp, _effekseer._manager->GetBaseMatrix(_effekseer._handle));

	_effekseer._manager->SetBaseMatrix(_effekseer._handle, offsetMat);

	_count = 0;

}

void CTeraEffect::stopEffekseer()
{
	_effekseer._manager->StopEffect(_effekseer._handle);
}

void CTeraEffect::setRotationEffekseer(const float angleX, const float angleY, const float angleZ)
{
	_effekseer._manager->SetRotation(_effekseer._handle, angleX, angleY, angleZ);
}

void CTeraEffect::setScaleEffekseer(const float scaleX, const float scaleY, const float scaleZ)
{
	_effekseer._manager->SetScale(_effekseer._handle, scaleX, scaleY, scaleZ);
}

bool CTeraEffect::EffekExist()
{
	if (_effekseer._manager->Exists(_effekseer._handle))
	{
		return true;
	}

	else if(!_effekseer._manager->Exists(_effekseer._handle))
	{
		return false;
	}
}

void CTeraEffect::fireBallExplosion(const D3DXVECTOR3 & position)
{
	if (_filepath == L"Resources/Effekseers/FireBallTest2.efk")
	{
			this->stopEffekseer();
			this->playEffeckseer(position, 150);
	}
}

D3DXVECTOR3 CTeraEffect::getEffectPosition()
{
	_position.x = _effekseer._manager->GetLocation(_effekseer._handle).X;
	_position.y = _effekseer._manager->GetLocation(_effekseer._handle).Y;
	_position.z = _effekseer._manager->GetLocation(_effekseer._handle).Z;

	return _position;
}




