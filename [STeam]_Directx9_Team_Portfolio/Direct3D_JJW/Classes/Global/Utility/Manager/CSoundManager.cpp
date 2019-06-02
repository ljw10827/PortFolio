#include "CSoundManager.h"
#include "../Sound/CSound.h"
#include "../Base/CDirect3DApplication.h"
#include "../Manager/CWindowManager.h"

CSoundManager::CSoundManager(void)
	:
	_effectsVolume(1.0f),
	_BGVolume(1.0f)
{
}

CSoundManager::~CSoundManager(void)
{
	for (auto &valueType : _effectSoundList) {
		for (auto sound : valueType.second) {
			SAFE_DELETE(sound);
		}
	}

	SAFE_DELETE(_backGroundSound);
	SAFE_RELEASE(_primarySoundBuffer);
	SAFE_RELEASE(_directSound);
}
void CSoundManager::init(void)
{
	_directSound = this->CreateDirectSound();
	_primarySoundBuffer = this->CreatePrimarySoundBuffer();
}

void CSoundManager::PlayEffectSound(const std::string & soundFilePath, const bool isLoop)
{
	auto sound = this->FindPlayableEffectSound(soundFilePath);

	if (sound != nullptr) {
		sound->StopSound();
		sound->playSound(isLoop);
	}

	this->setEffectsVolume(_effectsVolume);
}

void CSoundManager::PlayBGSound(const std::string & soundFilePath, const bool isLoop)
{
	if (_backGroundSound != nullptr) {
		std::string playingSoundFilePath = _backGroundSound->getSoundFilePath();

		if (!_backGroundSound->isPlaying() ||
			soundFilePath != playingSoundFilePath)
		{
			if (soundFilePath != playingSoundFilePath) {
				_backGroundSound->StopSound();
				_backGroundSound->ResetSound(soundFilePath);
			}
			_backGroundSound->playSound(isLoop);
		}
	}
	else {
		CSound::STParameters parameters = {
			true,
			soundFilePath
		};

		_backGroundSound = new CSound(parameters);
		_backGroundSound->playSound(isLoop);
	}

	this->setBGSoundVolume(_BGVolume);
}

void CSoundManager::PauseBGSound(void)
{
	if (_backGroundSound != nullptr) {
		_backGroundSound->PauseSound();
	}
}

void CSoundManager::StopBGSound(void)
{
	if (_backGroundSound != nullptr) {
		_backGroundSound->StopSound();
	}
}

LPDIRECTSOUND CSoundManager::getDirectSound(void)
{
	return _directSound;
}

void CSoundManager::setEffectsVolume(float volume)
{
	_effectsVolume = volume;

	for (auto &valueType : _effectSoundList) {
		for (auto sound : valueType.second) {
			if (sound != nullptr) {
				sound->setSoundVolume(volume);
			}
		}
	}
}

void CSoundManager::setBGSoundVolume(float volume)
{
	_BGVolume = volume;

	if (_backGroundSound != nullptr) {
		_backGroundSound->setSoundVolume(volume);
	}
}

CSound * CSoundManager::FindPlayableEffectSound(const std::string & soundFilePath)
{

	// 생성 된 효과음가 리스트에 없을경우
	if (_effectSoundList.find(soundFilePath) ==
		_effectSoundList.end()) {
		
		TSoundList soundList{
			nullptr
		};

		_effectSoundList.insert(decltype(_effectSoundList)::value_type(soundFilePath, soundList));
	}
	// auto soundList = _effectSoundList[soundFilePath];
	auto iterator = _effectSoundList.find(soundFilePath);

	// 사운드 리스트를 탐색한다. 
	auto soundIterator = std::find_if(iterator->second.begin(),
		iterator->second.end(),
		[=](CSound *sound) -> bool
	{
		return sound == nullptr || !sound->isPlaying();
	});

	// 재생 가능한 사운드가 없을 경우
	if (soundIterator == iterator->second.end()) {
		return nullptr;
	}

	// 아직 생성되지 않은 사운드일 경우 
	if (*soundIterator == nullptr) {
		CSound::STParameters parameters{
			false,
			soundFilePath
		};

		auto sound = new CSound(parameters);
		
		// 이터레이터를 통해서 직접적으로 값을 추가하는 방법
		//*soundIterator = sound;

		//// 인덱스 기반
		int index = soundIterator - iterator->second.begin();
		iterator->second[index] = sound;

		return sound;
	}

	(*soundIterator)->ResetSound(soundFilePath);
	return *soundIterator;
}

LPDIRECTSOUND CSoundManager::CreateDirectSound(void)
{
	LPDIRECTSOUND directSound = nullptr;
	DirectSoundCreate(nullptr, &directSound, nullptr);

	directSound->SetCooperativeLevel(GET_WINDOW_HANDLE(), DSSCL_PRIORITY);
	return directSound;
}

LPDIRECTSOUNDBUFFER CSoundManager::CreatePrimarySoundBuffer(void)
{
	DSBUFFERDESC bufferDesc;
	ZeroMemory(&bufferDesc, sizeof(bufferDesc));

	bufferDesc.dwSize = sizeof(bufferDesc);
	bufferDesc.dwFlags = DSBCAPS_PRIMARYBUFFER;

	// 사운드 버퍼를 생성한다
	LPDIRECTSOUNDBUFFER soundBuffer = nullptr;
	_directSound->CreateSoundBuffer(&bufferDesc,
		&soundBuffer,
		nullptr);
	
	WAVEFORMATEX waveFormat;
	ZeroMemory(&waveFormat, sizeof(waveFormat));

	waveFormat.cbSize = sizeof(waveFormat);
	waveFormat.wFormatTag = WAVE_FORMAT_PCM;
	waveFormat.nChannels = 2;
	waveFormat.wBitsPerSample = 16;
	waveFormat.nSamplesPerSec = 22050;
	waveFormat.nBlockAlign = (waveFormat.wBitsPerSample / 8) * waveFormat.nChannels;
	waveFormat.nAvgBytesPerSec = waveFormat.nBlockAlign * waveFormat.nSamplesPerSec;

	soundBuffer->SetFormat(&waveFormat);
	return soundBuffer;
}
