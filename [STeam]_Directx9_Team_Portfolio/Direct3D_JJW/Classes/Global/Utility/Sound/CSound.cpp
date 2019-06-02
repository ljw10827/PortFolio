#include "CSound.h"
#include "../Manager/CSoundManager.h"
#include "../Manager/CResourceManager.h"

CSound::CSound(const STParameters & parameters)
	:
	_parameters(parameters)
{
	this->ResetSound(parameters.soundFilePath);
}

CSound::~CSound(void)
{
	SAFE_RELEASE(_soundBuffer);
}

bool CSound::isPlaying(void)
{
	DWORD status = 0;

	_soundBuffer->GetStatus(&status);

	return status & DSBSTATUS_PLAYING;
}

void CSound::ResetSound(const std::string & soundFilePath)
{
	_soundFilePath = soundFilePath;
	_waveSound = GET_WAVE_SOUND(soundFilePath);

	SAFE_RELEASE(_soundBuffer);
	_soundBuffer = this->CreateSoundBuffer();

	BYTE *bytesA = nullptr;
	BYTE *bytesB = nullptr;

	DWORD numBytesA = 0;
	DWORD numBytesB = 0;

	if (SUCCEEDED(_soundBuffer->Lock(0,
		_waveSound.numBytes,
		(void **)&bytesA,
		&numBytesA,
		(void **)&bytesB,
		&numBytesB,
		0)))
	{
		CopyMemory(bytesA, _waveSound.bytes, sizeof(BYTE) * _waveSound.numBytes);
		_soundBuffer->Unlock(nullptr, 0, nullptr, 0);
	}
}

void CSound::playSound(const bool isLoop)
{
	DWORD flags = isLoop ? DSBPLAY_LOOPING : 0;

	_soundBuffer->SetCurrentPosition(_soundPosition);
	_soundBuffer->Play(0, 0, flags);
}

void CSound::PauseSound(void)
{
	_soundBuffer->GetCurrentPosition(&_soundPosition, nullptr);
	_soundBuffer->Stop();
}

void CSound::StopSound(void)
{
	_soundPosition = 0;
	_soundBuffer->Stop();
}

std::string CSound::getSoundFilePath(void)
{
	return _soundFilePath;
}

void CSound::setSoundVolume(float volume)
{
	volume = max(0.0f, volume);
	volume = min(1.0f, volume);

	_soundBuffer->SetVolume((1.0f - volume) * DSBVOLUME_MIN);
}

LPDIRECTSOUNDBUFFER CSound::CreateSoundBuffer(void)
{
	DSBUFFERDESC bufferDesc;
	ZeroMemory(&bufferDesc, sizeof(bufferDesc));

	bufferDesc.dwSize = sizeof(bufferDesc);
	bufferDesc.guid3DAlgorithm = GUID_NULL;
	bufferDesc.lpwfxFormat = &_waveSound.waveFormat;
	bufferDesc.dwBufferBytes = _waveSound.numBytes;
	bufferDesc.dwFlags = DSBCAPS_STATIC | DSBCAPS_GLOBALFOCUS | DSBCAPS_CTRLVOLUME;

	LPDIRECTSOUNDBUFFER soundBuffer = nullptr;
	
	GET_DIRECT_SOUND()->CreateSoundBuffer(&bufferDesc, &soundBuffer, nullptr);

	return soundBuffer;
}
