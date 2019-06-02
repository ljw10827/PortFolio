#pragma once

#include "../../Define/KGlobalDefine.h"

class CSound;

//! ���� ������
class CSoundManager 
{
public:

	enum
	{
		MAX_NUM_DUPLICATE_EFFECT_SOUNDS = 5
	};

	//! Ÿ�� ������
	typedef std::array<CSound *, MAX_NUM_DUPLICATE_EFFECT_SOUNDS> TSoundList;

public:		// �Ҹ���

	//! ������
	explicit CSoundManager(void);

	//! �Ҹ���
	virtual ~CSoundManager(void);

public:		// public �Լ�

	//! �̱���
	DECLARE_SINGLETON(CSoundManager);

	//! �ʱ�ȭ
	void init(void);
	
	//! ȿ������ ����Ѵ�
	void PlayEffectSound(const std::string &soundFilePath, const bool isLoop = false);

	//! ������� ����Ѵ�
	void PlayBGSound(const std::string &soundFilePath, const bool isLoop = true);

	//! ������� �Ͻ� �����Ѵ�
	void PauseBGSound(void);

	//! ������� �����Ѵ�
	void StopBGSound(void);

public:		// getter

	//! ���̷�Ʈ ���带 ��ȯ�Ѵ�
	LPDIRECTSOUND getDirectSound(void);

	//! ȿ���� ������ �����Ѵ�
	void setEffectsVolume(float volume);

	//! ����� ������ �����Ѵ�
	void setBGSoundVolume(float volume);

private:	// private �Լ�
	
	//! ��� ������ ȿ������ Ž���Ѵ�.
	CSound * FindPlayableEffectSound(const std::string &soundFilePath);

	//! ���̷�Ʈ ���带 �����Ѵ�
	LPDIRECTSOUND CreateDirectSound(void);

	//! �� ���۸� �����Ѵ�.
	LPDIRECTSOUNDBUFFER CreatePrimarySoundBuffer(void);

private:	// private ����

	float _effectsVolume = 0.0f;
	float _BGVolume = 0.0f;

	LPDIRECTSOUND _directSound = nullptr;
	LPDIRECTSOUNDBUFFER _primarySoundBuffer = nullptr;

	CSound * _backGroundSound = nullptr;
	std::unordered_map<std::string, TSoundList> _effectSoundList;
};