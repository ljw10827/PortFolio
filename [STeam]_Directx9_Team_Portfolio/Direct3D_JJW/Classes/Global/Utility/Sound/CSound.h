#pragma once

#include "../../Define/KGlobalDefine.h"

//! 사운드
class CSound
{
public:

	//! 매개변수
	struct STParameters
	{
		bool isLoop;
		std::string soundFilePath;
	};
	
public:			// 생성자 소멸자

	//! 생성자
	explicit CSound(const STParameters & parameters);

	//! 소멸자
	virtual ~CSound(void);

public:			// public 함수

	//! 플레이 여부를 반환한다
	bool isPlaying(void);

	// 사운드를 리셋한다
	void ResetSound(const std::string &soundFilePath);

	//! 사운드를 재생한다
	void playSound(const bool isLoop);

	//! 사운드를 일시정지한다
	void PauseSound(void);

	//! 사운드를 중지한다
	void StopSound(void);

public:		// getter

	//! 사운드 경로를 반환한다
	std::string getSoundFilePath(void);

	//! 사운드 볼륨을 변경한다
	void setSoundVolume(float volume);

private:		// private 함수

	//! 사운드 버퍼를 생성한다
	LPDIRECTSOUNDBUFFER CreateSoundBuffer(void);

private:		// private 변수


	DWORD _soundPosition = 1;
	std::string _soundFilePath = "";

	STWaveSound _waveSound;
	STParameters _parameters;
	LPDIRECTSOUNDBUFFER _soundBuffer = nullptr;
};