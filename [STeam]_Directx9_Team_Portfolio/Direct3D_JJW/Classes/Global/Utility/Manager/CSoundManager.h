#pragma once

#include "../../Define/KGlobalDefine.h"

class CSound;

//! 사운드 관리자
class CSoundManager 
{
public:

	enum
	{
		MAX_NUM_DUPLICATE_EFFECT_SOUNDS = 5
	};

	//! 타입 재정의
	typedef std::array<CSound *, MAX_NUM_DUPLICATE_EFFECT_SOUNDS> TSoundList;

public:		// 소멸자

	//! 생성자
	explicit CSoundManager(void);

	//! 소멸자
	virtual ~CSoundManager(void);

public:		// public 함수

	//! 싱글턴
	DECLARE_SINGLETON(CSoundManager);

	//! 초기화
	void init(void);
	
	//! 효과음을 재생한다
	void PlayEffectSound(const std::string &soundFilePath, const bool isLoop = false);

	//! 배경음을 재생한다
	void PlayBGSound(const std::string &soundFilePath, const bool isLoop = true);

	//! 배경음을 일시 중지한다
	void PauseBGSound(void);

	//! 배경음을 정지한다
	void StopBGSound(void);

public:		// getter

	//! 다이렉트 사운드를 반환한다
	LPDIRECTSOUND getDirectSound(void);

	//! 효과음 볼륨을 변경한다
	void setEffectsVolume(float volume);

	//! 배경음 볼륨을 조절한다
	void setBGSoundVolume(float volume);

private:	// private 함수
	
	//! 재생 가능한 효과음을 탐색한다.
	CSound * FindPlayableEffectSound(const std::string &soundFilePath);

	//! 다이렉트 사운드를 생성한다
	LPDIRECTSOUND CreateDirectSound(void);

	//! 주 버퍼를 생성한다.
	LPDIRECTSOUNDBUFFER CreatePrimarySoundBuffer(void);

private:	// private 변수

	float _effectsVolume = 0.0f;
	float _BGVolume = 0.0f;

	LPDIRECTSOUND _directSound = nullptr;
	LPDIRECTSOUNDBUFFER _primarySoundBuffer = nullptr;

	CSound * _backGroundSound = nullptr;
	std::unordered_map<std::string, TSoundList> _effectSoundList;
};