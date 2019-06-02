#pragma once

#include "../../Define/KGlobalDefine.h"

//! 리소스 관리자
class CResourceManager
{
public:			// getter

	//! 메시를 반환한다
	LPD3DXMESH getMeshForKey(const std::string &meshKey);

	//! 웨이브 사운드를 반환한다
	STWaveSound getWaveSoundForKey(const std::string &waveSoundKey, const bool isAutoCreate = true);

	//! 정적 메시를 반환한다
	STStaticMesh getStaticMeshForKey(const std::string &staticMeshKey, const bool isAutoCreate = true);

	//! 텍스처를 반환한다
	LPDIRECT3DTEXTURE9 getTextureForKey(const std::string &textureKey, const bool isAutoCreate = true);

	//! 큐브텍스처를 반환한다
	LPDIRECT3DCUBETEXTURE9 getCubeTextureForKey(const std::string &textureKey, const bool isAutoCreate = true);

	//! 스프라이트 텍스처를 반환한다
	LPDIRECT3DTEXTURE9 getSpriteTextureForKey(const std::string &textureKey, const bool isAutoCreate = true);

	//! 이펙트를 반환한다
	LPD3DXEFFECT getEffectForKey(const std::string &effectKey, const bool isAutoCreate = true);

	//! 테라 이펙트
	STEffekseer getEffekseerForKey(const std::wstring &effeckseerKey, const bool isAutoCreate = true);

public:			// public 함수

	//! 싱글턴
	DECLARE_SINGLETON(CResourceManager);

	//! 메시를 추가한다
	void AddMeshForKey(const std::string &meshKey, LPD3DXMESH mesh);

	//! 웨이브 사운드를 추가한다
	void AddWaveSoundForKey(const std::string &waveSoundKey, STWaveSound waveSound);

	//! 정적 메시를 추가한다
	void AddStaticMeshForKey(const std::string &staticMeshKey, STStaticMesh staticMesh);

	//! 텍스처를 추가한다
	void addTextureForKey(const std::string &textureKey, LPDIRECT3DTEXTURE9 texture);

	//! 큐브 텍스처를 추가한다
	void addCubeTextureForKey(const std::string &textureKey, LPDIRECT3DCUBETEXTURE9 cubeTexture);

	//! 이펙트를 추가한다
	void addEffectForKey(const std::string &effectKey, LPD3DXEFFECT effect);

	//! 테라 이펙트
	void AddEffekseerForKey(const std::wstring &effeckseerKey, STEffekseer effekseer);

private:		// private 함수

	//! 웨이브 사운드를 생성한다
	STWaveSound CreateWaveSound(const std::string &waveSoundFilePath);

	//! 정적메시를 생성한다
	STStaticMesh CreateStaticMesh(const std::string &staticMeshFilePath);

	//! 텍스처를 생성한다
	LPDIRECT3DTEXTURE9 createTexture(const std::string &textureFilePath);

	//! 큐브 텍스처를 생성한다
	LPDIRECT3DCUBETEXTURE9 CreateCubeTexture(const std::string &textureFilePath);

	//! 스프라이트 텍스처를 생성한다
	LPDIRECT3DTEXTURE9 createSpriteTexture(const std::string &textureFilePath);

	//! 이펙트를 생성한다
	LPD3DXEFFECT CreateEffect(const std::string &effectFilePath);

	//! 테라 이펙트
	STEffekseer CreateEffekSeer(const std::wstring &effekseerFilepath);

private:			// 소멸자
	
	//! 소멸자
	virtual ~CResourceManager(void);

private:			// private 변수

	std::unordered_map<std::string, STWaveSound> _waveSoundList;
	std::unordered_map<std::string, LPDIRECT3DTEXTURE9> _textureList;
	std::unordered_map<std::string, LPD3DXEFFECT> _effectList;
	std::unordered_map<std::string, STStaticMesh> _staticMeshList;
	std::unordered_map<std::string, LPDIRECT3DCUBETEXTURE9> _cubeTextureList;
	std::unordered_map<std::string, LPD3DXMESH> _meshList;

	//테라 이펙트
	std::unordered_map<std::wstring, STEffekseer> _effekseerList;

};