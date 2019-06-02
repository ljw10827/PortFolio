#pragma once

#include <iostream>
#include <vector>
#include <unordered_map>
#include <functional>
#include <random>
#include <array>
#include <chrono>
#include <numeric>
#include <thread>
#include <cassert>
#include <Windows.h>
#include <windowsx.h>
#include <stdio.h>
#include <tchar.h>
#include <d3dx9.h>
#include <dinput.h>
#include <string>
#include <mutex>
#include <dsound.h>
#include <Effekseer.h>
#include <EffekseerRendererDX9.h>
#include <dshow.h>

//! 타입 재정의
typedef std::function<void(float)> TScheduler;

#define MAX_NUM_DIRECTIONS		(3)
#define X_DIRECTION				(0)
#define Y_DIRECTION				(1)
#define Z_DIRECTION				(2)

#define CREATE_MAX_DOOBEAN			(5)
#define CREATE_MAX_PLANT			(7)
#define CREATE_MAX_GHILLIEDHU		(4)
#define CREATE_MAX_ARGASS			(3)
#define CREATE_MAX_CRAFTYSPIDER		(5)
#define CREATE_MAX_BASILISK			(1)
#define CREATE_MAX_POLLUTEDWOLF		(3)
#define CREATE_MAX_VERGOS			(1)

// 축
#define WORLD_RIGHT_DIRECTION				(D3DXVECTOR3(1.0f, 0.0f, 0.0f))
#define WORLD_UP_DIRECTION					(D3DXVECTOR3(0.0f, 1.0f, 0.0f))
#define WORLD_FORWARD_DIRECTION				(D3DXVECTOR3(0.0f, 0.0f, 1.0f))

#define SAFE_FREE(TARGER)					if((TARGET) != nullptr) { free((TARGET)); (TARGET) = nullptr; }
#define SAFE_RELEASE(TARGET)				if((TARGET) != nullptr) { (TARGET)->Release(); (TARGET) = nullptr; }
#define SAFE_DELETE(TARGET)					if((TARGET) != nullptr) { delete (TARGET); (TARGET) = nullptr; }
#define SAFE_DELETE_ARRAY(TARGET)			if((TARGET) != nullptr) { delete[] (TARGET); (TARGET) = nullptr; }
#define SAFE_UNACQUIRE(TARGET)				if((TARGET) != nullptr) { (TARGET)->Unacquire(); SAFE_RELEASE((TARGET)); }

#define IS_KEY_DOWN(KEY_CODE)				(GET_INPUT_MANAGER()->isKeyDown((KEY_CODE)))
#define IS_KEY_PRESSED(KEY_CODE)			(GET_INPUT_MANAGER()->isKeyPressed((KEY_CODE)))
#define IS_KEY_RELEASED(KEY_CODE)			(GET_INPUT_MANAGER()->isKeyReleased((KEY_CODE)))

#define IS_MOUSE_DOWN(BUTTON_INDEX)			(GET_INPUT_MANAGER()->isMouseDown((BUTTON_INDEX)))
#define IS_MOUSE_PRESSED(BUTTON_INDEX)		(GET_INPUT_MANAGER()->isMousePressed((BUTTON_INDEX)))
#define IS_MOUSE_RELEASED(BUTTON_INDEX)		(GET_INPUT_MANAGER()->isMouseRelease((BUTTON_INDEX)))

#define PLAY_EFFECT_SOUND(FILEPATH)			(GET_SOUND_MANAGER()->PlayEffectSound((FILEPATH)))
#define PLAY_BACKGROUND_SOUND(FILEPATH)		(GET_SOUND_MANAGER()->PlayBGSound((FILEPATH)))

// 게터 (접근자)
//{

#define GET_MESH(FILEPATH)					(GET_RESOURCE_MANAGER()->getMeshForKey((FILEPATH)))
#define GET_EFFECT(FILEPATH)				(GET_RESOURCE_MANAGER()->getEffectForKey((FILEPATH)))
#define GET_TEXTURE(FILEPATH)				(GET_RESOURCE_MANAGER()->getTextureForKey((FILEPATH)))
#define GET_CUBE_TEXTURE(FILEPATH)			(GET_RESOURCE_MANAGER()->getCubeTextureForKey((FILEPATH)))
#define GET_SPRITE_TEXTURE(FILEPATH)		(GET_RESOURCE_MANAGER()->getSpriteTextureForKey((FILEPATH)))
#define GET_STATIC_MESH(FILEPATH)			(GET_RESOURCE_MANAGER()->getStaticMeshForKey((FILEPATH)))
#define GET_WAVE_SOUND(FILEPATH)			(GET_RESOURCE_MANAGER()->getWaveSoundForKey((FILEPATH)))

#define GET_LIGHT()							(GET_DIRECT3D_APPLICATION()->getLight())
#define GET_CAMERA()						(GET_DIRECT3D_APPLICATION()->getCamera())
#define GET_SPRITE()						(GET_DIRECT3D_APPLICATION()->getSprite())

#define GET_WINDOW_APPLICATION()			(CWindowApplication::getInstance())
#define GET_DIRECT3D_APPLICATION()			((CDirect3DApplication *)GET_WINDOW_APPLICATION())

#define GET_MOUSE_WHEEL()					(GET_INPUT_MANAGER()->getMouseWheel())
#define GET_MOUSE_POSITION()				(GET_INPUT_MANAGER()->getMousePosition())

#define GET_DELTA_TIME()					(GET_TIME_MANAGER()->getDeltaTime())
#define GET_RUNNING_TIME()					(GET_TIME_MANAGER()->getRunningTime())

#define GET_WINDOW_SIZE()					(GET_WINDOW_MANAGER()->getWindowSize())
#define GET_WINDOW_HANDLE()					(GET_WINDOW_MANAGER()->getWindowHandle())
#define GET_INSTANCE_HANDLE()				(GET_WINDOW_MANAGER()->getInstanceHandle())

#define GET_DIRECT3D()						(GET_DEVICE_MANAGER()->getDirect3D())
#define GET_DEVICE()						(GET_DEVICE_MANAGER()->getDevice())
#define GET_DIRECT_SOUND()					(GET_SOUND_MANAGER()->getDirectSound())

#define GET_WINDOW_MANAGER()				(CWindowManager::getInstance())
#define GET_DEVICE_MANAGER()				(CDeviceManager::getInstance())
#define GET_TIME_MANAGER()					(CTimeManager::getInstance())
#define GET_INPUT_MANAGER()					(CInputManager::getInstance())
#define GET_RESOURCE_MANAGER()				(CResourceManager::getInstance())
#define GET_SOUND_MANAGER()					(CSoundManager::getInstance())

//씬 관리자
#define GET_SCENE_MANAGER()					(CSceneManager::getInstance())
#define GET_EFFEKSEER(FILEPATH)				(GET_RESOURCE_MANAGER()->getEffekseerForKey((FILEPATH)))
#define GET_MONSTER()						(CMonsterFactory::getInstance())

#define GET_MAP(MAPNAME)					(GET_MAP_MANAGER()->getTeraMap((MAPNAME)))
#define GET_MAP_MANAGER()					(CTeraMapManager::getInstance())

#define SET_SCHEDULE(TIME, CALLBAK)			(GET_SCHEDULER_MANAGER()->setScheduler((TIME), (CALLBAK)))
#define GET_SCHEDULER_MANAGER()				(CSchedulerManager::getInstance())

// 싱글턴
#define DECLARE_SINGLETON(CLASS_NAME)				\
public:												\
static CLASS_NAME * getInstance(void) {				\
	static std::mutex mutex;						\
	std::lock_guard<std::mutex> lockGuard(mutex);	\
	static CLASS_NAME oInstance;					\
	return &oInstance;								\
}


//! 마우스 입력
enum class EMouseInput
{
	LEFT_BUTTON,
	RIGHT_BUTTON,
	MIDDLE_BUTTON,
	NONE
};


//! 주시 타입
enum class EFollowType
{
	FIXED,
	ROTATION,
	FREE,
	NONE
};

//! 디버그 타입
enum class EDebugType
{
	BOX,
	SPHERE,
	NONE
};

enum class EffectType
{
	FireBall,
	laser,
	Slash,
	Hit,
	NONE
};

//! 광선
struct STRay
{
	D3DXVECTOR3 origin;
	D3DXVECTOR3 direction;
};

//! 정적 메시
struct STStaticMesh
{
	LPD3DXMESH mesh;
	DWORD numMaterials;

	std::unordered_map<int, D3DMATERIAL9> materialList;
	std::unordered_map<int, LPDIRECT3DTEXTURE9> textureList;
};

//! .wav 사운드
struct STWaveSound
{
	BYTE *bytes;
	DWORD numBytes;
	WAVEFORMATEX waveFormat;
};

//! 객체 박스
struct STObjectBox
{
	D3DXVECTOR3 centerPosition;

	float halfLengths[MAX_NUM_DIRECTIONS];
	D3DXVECTOR3 axis[MAX_NUM_DIRECTIONS];
};

//! 바운딩 박스
struct STBoundingBox
{
	D3DXVECTOR3 minPosition;
	D3DXVECTOR3 maxPosition;
};

//! 바운딩 스피어
struct STBoundingSphere
{
	float radius;
	D3DXVECTOR3 centerPosition;
};

struct STEffekseer
{
	::Effekseer::Manager*				_manager;
	::EffekseerRendererDX9::Renderer*	_renderer;
	::Effekseer::Effect*				_effect;
	::Effekseer::Handle					_handle;
	::Effekseer::Vector3D				_position;
};

struct STSphereSRT
{
	float Radius = 1;
	D3DXVECTOR3 position = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
};

enum class SkinnedType
{
	MDooBean,
	MPlantMini,
	MPollutedWolf,
	MGhillieDhu,
	MCraftySpider,
	MBasilisk,
	MArgass,
	MVergos,
	NCastanic,
	NGeneral,
	NHumanF,
	NRabbit,
	NDog,
	NSheep,
	NSheepNaked,
	NSoldier01,
	NSoldier02,
	Player,
	NBarricade,
	None
};