#include "CResourceManager.h"
#include "../Manager/CDeviceManager.h"
#include "../Object/CCamera.h"
#include "../Base/CDirect3DApplication.h"
#include "../Base/CWindowApplication.h"

CResourceManager::~CResourceManager(void)
{
	for (auto &valueType : _waveSoundList) {
		SAFE_DELETE(valueType.second.bytes);
	}

	for (auto &valueType : _staticMeshList) {
		SAFE_RELEASE(valueType.second.mesh);
	}

	for (auto &valueType : _textureList) {
		SAFE_RELEASE(valueType.second);
	}

	for (auto &valueType : _effectList) {
		SAFE_RELEASE(valueType.second);
	}
}

LPD3DXMESH CResourceManager::getMeshForKey(const std::string & meshKey)
{
	auto iterator = _meshList.find(meshKey);
	return (iterator == _meshList.end()) ? nullptr : iterator->second;
}

STWaveSound CResourceManager::getWaveSoundForKey(const std::string & waveSoundKey, const bool isAutoCreate)
{
	STWaveSound waveSound;
	auto iterator = _waveSoundList.find(waveSoundKey);

	if (iterator != _waveSoundList.end()) {
		return iterator->second;
	}

	if (isAutoCreate) {
		waveSound = this->CreateWaveSound(waveSoundKey);
		this->AddWaveSoundForKey(waveSoundKey, waveSound);
	}

	return waveSound;
}

STStaticMesh CResourceManager::getStaticMeshForKey(const std::string & staticMeshKey, const bool isAutoCreate)
{
	STStaticMesh staticMesh;
	auto iterator = _staticMeshList.find(staticMeshKey);

	if (iterator != _staticMeshList.end()) {
		return iterator->second;
	}

	if (isAutoCreate) {
		staticMesh = this->CreateStaticMesh(staticMeshKey);
		this->AddStaticMeshForKey(staticMeshKey, staticMesh);
	}

	return staticMesh;

}

LPDIRECT3DTEXTURE9 CResourceManager::getTextureForKey(const std::string & textureKey, const bool isAutoCreate)
{
	LPDIRECT3DTEXTURE9 texture = nullptr;
	auto iterator = _textureList.find(textureKey);

	if (iterator != _textureList.end()) {
		return iterator->second;
	}

	if (isAutoCreate) {
		texture = this->createTexture(textureKey);
		this->addTextureForKey(textureKey, texture);
	}

	return texture;
}

LPDIRECT3DCUBETEXTURE9 CResourceManager::getCubeTextureForKey(const std::string & textureKey, const bool isAutoCreate)
{
	LPDIRECT3DCUBETEXTURE9 cubeTexture = nullptr;
	auto iterator = _cubeTextureList.find(textureKey);

	if (iterator != _cubeTextureList.end()) {
		return iterator->second;
	}

	if (isAutoCreate) {
		cubeTexture = this->CreateCubeTexture(textureKey);
		this->addCubeTextureForKey(textureKey, cubeTexture);
	}
	return cubeTexture;
}

LPDIRECT3DTEXTURE9 CResourceManager::getSpriteTextureForKey(const std::string & textureKey, const bool isAutoCreate)
{
	LPDIRECT3DTEXTURE9 texture = nullptr;
	auto iterator = _textureList.find(textureKey);

	if (iterator != _textureList.end()) {
		return iterator->second;
	}

	if (isAutoCreate) {
		texture = this->createSpriteTexture(textureKey);
		this->addTextureForKey(textureKey, texture);
	}

	return texture;
}

LPD3DXEFFECT CResourceManager::getEffectForKey(const std::string & effectKey, const bool isAutoCreate)
{
	LPD3DXEFFECT effect = nullptr;
	auto iterator = _effectList.find(effectKey);

	if (iterator != _effectList.end()) {
		return iterator->second;
	}

	if (isAutoCreate) {
		effect = this->CreateEffect(effectKey);
		this->addEffectForKey(effectKey, effect);
	}

	return effect;
}

STEffekseer CResourceManager::getEffekseerForKey(const std::wstring & effeckseerKey, const bool isAutoCreate)
{
	auto oIterator = _effekseerList.find(effeckseerKey);
	STEffekseer effekseer;

	if (oIterator != _effekseerList.end())
	{
		return oIterator->second;
	}

	if (isAutoCreate)
	{
		effekseer = this->CreateEffekSeer(effeckseerKey);
		this->AddEffekseerForKey(effeckseerKey, effekseer);
	}

	return effekseer;
}

void CResourceManager::AddMeshForKey(const std::string & meshKey, LPD3DXMESH mesh)
{
	_meshList.insert(decltype(_meshList)::value_type(meshKey, mesh));
}

void CResourceManager::AddWaveSoundForKey(const std::string & waveSoundKey, STWaveSound waveSound)
{
	_waveSoundList.insert(decltype(_waveSoundList)::value_type(waveSoundKey, waveSound));
}

void CResourceManager::AddStaticMeshForKey(const std::string & staticMeshKey, STStaticMesh staticMesh)
{
	_staticMeshList.insert(decltype(_staticMeshList)::value_type(staticMeshKey, staticMesh));
}

void CResourceManager::addTextureForKey(const std::string & textureKey, LPDIRECT3DTEXTURE9 texture)
{
	_textureList.insert(decltype(_textureList)::value_type(textureKey, texture));
}

void CResourceManager::addCubeTextureForKey(const std::string & textureKey, LPDIRECT3DCUBETEXTURE9 cubeTexture)
{
	_cubeTextureList.insert(decltype(_cubeTextureList)::value_type(textureKey, cubeTexture));
}

void CResourceManager::addEffectForKey(const std::string & effectKey, LPD3DXEFFECT effect)
{
	_effectList.insert(decltype(_effectList)::value_type(effectKey, effect));
}

void CResourceManager::AddEffekseerForKey(const std::wstring & effeckseerKey, STEffekseer effekseer)
{
	_effekseerList.insert(decltype(_effekseerList)::value_type(effeckseerKey, effekseer));
}

STWaveSound CResourceManager::CreateWaveSound(const std::string & waveSoundFilePath)
{
	STWaveSound waveSound;
	ZeroMemory(&waveSound, sizeof(waveSound));

	HMMIO waveHandle = mmioOpenA((char *)waveSoundFilePath.c_str(), nullptr, MMIO_READ);

	if (waveHandle != nullptr) {
		MMCKINFO chunk;
		ZeroMemory(&chunk, sizeof(chunk));

		chunk.fccType = mmioFOURCC('W', 'A', 'V', 'E');
		mmioDescend(waveHandle, &chunk, nullptr, 0);

		MMCKINFO subChunk;
		ZeroMemory(&subChunk, sizeof(subChunk));

		subChunk.ckid = mmioFOURCC('f', 'm', 't', ' ');
		mmioDescend(waveHandle, &subChunk, &chunk, 0);

		mmioRead(waveHandle, (char*)(&waveSound.waveFormat), subChunk.cksize);
		mmioAscend(waveHandle, &subChunk, 0);

		subChunk.ckid = mmioFOURCC('d', 'a', 't', 'a');
		mmioDescend(waveHandle, &subChunk, &chunk, 0);

		waveSound.numBytes = subChunk.cksize;
		waveSound.bytes = (BYTE *)malloc(sizeof(BYTE) * subChunk.cksize);

		mmioRead(waveHandle, (char *)waveSound.bytes, subChunk.cksize);
		mmioClose(waveHandle, MMIOM_CLOSE);
	}

	return waveSound;
}

STStaticMesh CResourceManager::CreateStaticMesh(const std::string & staticMeshFilePath)
{
	STStaticMesh staticMesh;

	LPD3DXBUFFER adjacencyBuffer = nullptr;
	LPD3DXBUFFER xMaterialsBuffer = nullptr;

	// 정적 메시를 생성한다
	D3DXLoadMeshFromXA(staticMeshFilePath.c_str(),
		D3DXMESH_MANAGED,
		GET_DEVICE(),
		&adjacencyBuffer,
		&xMaterialsBuffer,
		nullptr,
		&staticMesh.numMaterials,
		&staticMesh.mesh);

	// 정점정보를 설정한다
	//{
	D3DVERTEXELEMENT9 elements[] = {
		0, 0, D3DDECLTYPE_FLOAT3, D3DDECLMETHOD_DEFAULT, D3DDECLUSAGE_POSITION, 0,
		0, 12, D3DDECLTYPE_FLOAT3, D3DDECLMETHOD_DEFAULT, D3DDECLUSAGE_NORMAL, 0,
		0, 24, D3DDECLTYPE_FLOAT2, D3DDECLMETHOD_DEFAULT, D3DDECLUSAGE_TEXCOORD, 0,
		D3DDECL_END()
	};

	auto originMesh = staticMesh.mesh;

	// 메시를 복사한다
	originMesh->CloneMesh(originMesh->GetOptions(), 
		elements,
		GET_DEVICE(),
		&staticMesh.mesh);

	SAFE_RELEASE(originMesh);

	//}


	// 재질정보를 설정한다
	// {
	for (int i = 0; i < staticMesh.numMaterials; ++i) {
		LPD3DXMATERIAL xMaterials = (LPD3DXMATERIAL)(xMaterialsBuffer->GetBufferPointer());
		LPDIRECT3DTEXTURE9 texture = nullptr;

		if(xMaterials[i].pTextureFilename != nullptr){
			std::string basePath = "";

			// 경로가 있을 경우
			if (staticMeshFilePath.rfind('/') != std::string::npos) {
				std::size_t index = staticMeshFilePath.rfind('/');
				basePath = staticMeshFilePath.substr(0, index + 1);
			}

			char textureFilePath[MAX_PATH] = "";
			sprintf(textureFilePath, "%s%s", basePath.c_str(), xMaterials[i].pTextureFilename);

			texture = GET_TEXTURE(textureFilePath);

		}

		staticMesh.materialList.insert(std::make_pair(i, xMaterials[i].MatD3D));
		staticMesh.textureList.insert(std::make_pair(i, texture));
	}
	// }

	D3DXComputeNormals(staticMesh.mesh, (DWORD *)(adjacencyBuffer->GetBufferPointer()));

	return staticMesh;
}

LPDIRECT3DTEXTURE9 CResourceManager::createTexture(const std::string & textureFilePath)
{
	LPDIRECT3DTEXTURE9 texture = nullptr;
	
	// 텍스처를 생성한다
	D3DXCreateTextureFromFileA(GET_DEVICE(),
		textureFilePath.c_str(),
		&texture);

	return texture;
}

LPDIRECT3DCUBETEXTURE9 CResourceManager::CreateCubeTexture(const std::string & textureFilePath)
{
	LPDIRECT3DCUBETEXTURE9 cubeTexture = nullptr;

	// 큐브 텍스처를 생성한다.
	D3DXCreateCubeTextureFromFileA(GET_DEVICE(),
		textureFilePath.c_str(),
		&cubeTexture);

	return cubeTexture;
}

LPDIRECT3DTEXTURE9 CResourceManager::createSpriteTexture(const std::string & textureFilePath)
{
	LPDIRECT3DTEXTURE9 texture = nullptr;

	// 텍스처를 생성한다
	D3DXCreateTextureFromFileExA(GET_DEVICE(),
		textureFilePath.c_str(),
		D3DX_DEFAULT_NONPOW2,
		D3DX_DEFAULT_NONPOW2,
		1,
		D3DUSAGE_DYNAMIC,
		D3DFMT_UNKNOWN,
		D3DPOOL_DEFAULT,
		D3DX_FILTER_NONE,
		0,
		D3DCOLOR_ARGB(0, 0, 0, 0),
		nullptr,
		nullptr,
		&texture);

	return texture;
}

LPD3DXEFFECT CResourceManager::CreateEffect(const std::string & effectFilePath)
{
	LPD3DXEFFECT effect = nullptr;
	LPD3DXBUFFER errorMsgBuffer = nullptr;

	// 이펙트를 생성한다
	D3DXCreateEffectFromFileA(GET_DEVICE(),
		effectFilePath.c_str(),
		nullptr,
		nullptr,
		0,
		nullptr,
		&effect,
		&errorMsgBuffer);

	if (errorMsgBuffer != nullptr) {
		char *errorMsg = (char*)errorMsgBuffer->GetBufferPointer();
		printf("%s.CreateEffect : %s", effectFilePath, errorMsg);
	}

	return effect;
}

STEffekseer CResourceManager::CreateEffekSeer(const std::wstring & effekseerFilepath)
{
	STEffekseer effekseer;
	ZeroMemory(&effekseer, sizeof(effekseer));
	effekseer._handle = -1;

	effekseer._renderer = ::EffekseerRendererDX9::Renderer::Create(GET_DEVICE(), 2000);

	effekseer._manager = ::Effekseer::Manager::Create(2000);

	effekseer._manager->SetSpriteRenderer(effekseer._renderer->CreateSpriteRenderer());
	effekseer._manager->SetRibbonRenderer(effekseer._renderer->CreateRibbonRenderer());
	effekseer._manager->SetRingRenderer(effekseer._renderer->CreateRingRenderer());
	effekseer._manager->SetTrackRenderer(effekseer._renderer->CreateTrackRenderer());
	effekseer._manager->SetModelRenderer(effekseer._renderer->CreateModelRenderer());

	effekseer._manager->SetTextureLoader(effekseer._renderer->CreateTextureLoader());
	effekseer._manager->SetModelLoader(effekseer._renderer->CreateModelLoader());
	effekseer._position = ::Effekseer::Vector3D(0.0f, 0.0f, 5.0f);

	auto stProjectionMatrix = GET_CAMERA()->getProjectionMatrix();
	auto stViewMatrix = GET_CAMERA()->getViewMatrix();
	::Effekseer::Matrix44 stEffekProjectionMatrix;
	stEffekProjectionMatrix.Indentity();
	::Effekseer::Matrix44 stEffekViewMatrix;
	stEffekViewMatrix.Indentity();

	effekseer._manager->SetCoordinateSystem(Effekseer::CoordinateSystem::LH);


	const wchar_t *filepath = effekseerFilepath.c_str();

	effekseer._effect = Effekseer::Effect::Create(effekseer._manager, (const EFK_CHAR*)filepath);

	return effekseer;
}
