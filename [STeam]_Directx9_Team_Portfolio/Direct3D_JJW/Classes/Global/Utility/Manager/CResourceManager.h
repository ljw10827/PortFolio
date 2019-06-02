#pragma once

#include "../../Define/KGlobalDefine.h"

//! ���ҽ� ������
class CResourceManager
{
public:			// getter

	//! �޽ø� ��ȯ�Ѵ�
	LPD3DXMESH getMeshForKey(const std::string &meshKey);

	//! ���̺� ���带 ��ȯ�Ѵ�
	STWaveSound getWaveSoundForKey(const std::string &waveSoundKey, const bool isAutoCreate = true);

	//! ���� �޽ø� ��ȯ�Ѵ�
	STStaticMesh getStaticMeshForKey(const std::string &staticMeshKey, const bool isAutoCreate = true);

	//! �ؽ�ó�� ��ȯ�Ѵ�
	LPDIRECT3DTEXTURE9 getTextureForKey(const std::string &textureKey, const bool isAutoCreate = true);

	//! ť���ؽ�ó�� ��ȯ�Ѵ�
	LPDIRECT3DCUBETEXTURE9 getCubeTextureForKey(const std::string &textureKey, const bool isAutoCreate = true);

	//! ��������Ʈ �ؽ�ó�� ��ȯ�Ѵ�
	LPDIRECT3DTEXTURE9 getSpriteTextureForKey(const std::string &textureKey, const bool isAutoCreate = true);

	//! ����Ʈ�� ��ȯ�Ѵ�
	LPD3DXEFFECT getEffectForKey(const std::string &effectKey, const bool isAutoCreate = true);

	//! �׶� ����Ʈ
	STEffekseer getEffekseerForKey(const std::wstring &effeckseerKey, const bool isAutoCreate = true);

public:			// public �Լ�

	//! �̱���
	DECLARE_SINGLETON(CResourceManager);

	//! �޽ø� �߰��Ѵ�
	void AddMeshForKey(const std::string &meshKey, LPD3DXMESH mesh);

	//! ���̺� ���带 �߰��Ѵ�
	void AddWaveSoundForKey(const std::string &waveSoundKey, STWaveSound waveSound);

	//! ���� �޽ø� �߰��Ѵ�
	void AddStaticMeshForKey(const std::string &staticMeshKey, STStaticMesh staticMesh);

	//! �ؽ�ó�� �߰��Ѵ�
	void addTextureForKey(const std::string &textureKey, LPDIRECT3DTEXTURE9 texture);

	//! ť�� �ؽ�ó�� �߰��Ѵ�
	void addCubeTextureForKey(const std::string &textureKey, LPDIRECT3DCUBETEXTURE9 cubeTexture);

	//! ����Ʈ�� �߰��Ѵ�
	void addEffectForKey(const std::string &effectKey, LPD3DXEFFECT effect);

	//! �׶� ����Ʈ
	void AddEffekseerForKey(const std::wstring &effeckseerKey, STEffekseer effekseer);

private:		// private �Լ�

	//! ���̺� ���带 �����Ѵ�
	STWaveSound CreateWaveSound(const std::string &waveSoundFilePath);

	//! �����޽ø� �����Ѵ�
	STStaticMesh CreateStaticMesh(const std::string &staticMeshFilePath);

	//! �ؽ�ó�� �����Ѵ�
	LPDIRECT3DTEXTURE9 createTexture(const std::string &textureFilePath);

	//! ť�� �ؽ�ó�� �����Ѵ�
	LPDIRECT3DCUBETEXTURE9 CreateCubeTexture(const std::string &textureFilePath);

	//! ��������Ʈ �ؽ�ó�� �����Ѵ�
	LPDIRECT3DTEXTURE9 createSpriteTexture(const std::string &textureFilePath);

	//! ����Ʈ�� �����Ѵ�
	LPD3DXEFFECT CreateEffect(const std::string &effectFilePath);

	//! �׶� ����Ʈ
	STEffekseer CreateEffekSeer(const std::wstring &effekseerFilepath);

private:			// �Ҹ���
	
	//! �Ҹ���
	virtual ~CResourceManager(void);

private:			// private ����

	std::unordered_map<std::string, STWaveSound> _waveSoundList;
	std::unordered_map<std::string, LPDIRECT3DTEXTURE9> _textureList;
	std::unordered_map<std::string, LPD3DXEFFECT> _effectList;
	std::unordered_map<std::string, STStaticMesh> _staticMeshList;
	std::unordered_map<std::string, LPDIRECT3DCUBETEXTURE9> _cubeTextureList;
	std::unordered_map<std::string, LPD3DXMESH> _meshList;

	//�׶� ����Ʈ
	std::unordered_map<std::wstring, STEffekseer> _effekseerList;

};