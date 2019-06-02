#pragma once

#include "../../Define/KGlobalDefine.h"

//! ����
class CSound
{
public:

	//! �Ű�����
	struct STParameters
	{
		bool isLoop;
		std::string soundFilePath;
	};
	
public:			// ������ �Ҹ���

	//! ������
	explicit CSound(const STParameters & parameters);

	//! �Ҹ���
	virtual ~CSound(void);

public:			// public �Լ�

	//! �÷��� ���θ� ��ȯ�Ѵ�
	bool isPlaying(void);

	// ���带 �����Ѵ�
	void ResetSound(const std::string &soundFilePath);

	//! ���带 ����Ѵ�
	void playSound(const bool isLoop);

	//! ���带 �Ͻ������Ѵ�
	void PauseSound(void);

	//! ���带 �����Ѵ�
	void StopSound(void);

public:		// getter

	//! ���� ��θ� ��ȯ�Ѵ�
	std::string getSoundFilePath(void);

	//! ���� ������ �����Ѵ�
	void setSoundVolume(float volume);

private:		// private �Լ�

	//! ���� ���۸� �����Ѵ�
	LPDIRECTSOUNDBUFFER CreateSoundBuffer(void);

private:		// private ����


	DWORD _soundPosition = 1;
	std::string _soundFilePath = "";

	STWaveSound _waveSound;
	STParameters _parameters;
	LPDIRECTSOUNDBUFFER _soundBuffer = nullptr;
};