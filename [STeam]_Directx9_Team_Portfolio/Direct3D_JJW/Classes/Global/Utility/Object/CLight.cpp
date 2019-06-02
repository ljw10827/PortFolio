#include "CLight.h"
#include "../Manager/CDeviceManager.h"

CLight::CLight(const int a_nIndex)
	:
	m_nIndex(a_nIndex),
	m_bIsLightEnable(true)
{
	ZeroMemory(&m_stLight, sizeof(m_stLight));

	m_stLight.Type = D3DLIGHT_DIRECTIONAL;
	m_stLight.Diffuse = D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f);
	m_stLight.Specular = D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f);
}

void CLight::stLightEnable(const bool a_bIsLightEnable)
{
	m_bIsLightEnable = a_bIsLightEnable;
}

void CLight::setDiffuseColor(const D3DXCOLOR & a_rstDiffuseColor)
{
	m_stLight.Diffuse = a_rstDiffuseColor;
}

void CLight::setSpecularColor(const D3DXCOLOR & a_rSpecularColor)
{
	m_stLight.Specular = a_rSpecularColor;
}

void CLight::update(void)
{
	CObject::update();

	m_stLight.Direction = m_stForwardDirection;
	
	GET_DEVICE()->LightEnable(m_nIndex, m_bIsLightEnable);
	GET_DEVICE()->SetLight(m_nIndex, &m_stLight);
}
