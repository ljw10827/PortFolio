#include "CTerrain.h"
#include "../Manager/CResourceManager.h"
#include "../Manager/CDeviceManager.h"
#include "../Base/CDirect3DApplication.h"
#include "CCamera.h"
#include "CLight.h"

CTerrain::CTerrain(const STParameters & parameters)
{
	ZeroMemory(&_mapSize, sizeof(_mapSize));
	ZeroMemory(&_tileSize, sizeof(_tileSize));
	ZeroMemory(&_totalSize, sizeof(_totalSize));

	this->SetupTerrainInfo(parameters);
	this->SetupTerrainHeight(parameters);
	_mesh = this->CreateTerrainMesh(parameters);
	_textureList = this->CreateTerrainTextures(parameters, &_splatTexture);
	_effect = GET_EFFECT(parameters.effectFilepath);
}

CTerrain::~CTerrain(void)
{
}

void CTerrain::update(void)
{
	CRenderObject::update();
	//auto cameraPosition = GET_CAMERA()->getPosition();

	//cameraPosition.y = this->getTerrainHeightAtPosition(cameraPosition) + 20.0f;

	//GET_CAMERA()->setPosition(cameraPosition);
}

void CTerrain::doDrawObject(void)
{
	CRenderObject::doDrawObject();
	// 행렬을 설정한다
	// {
	D3DXMATRIXA16 worldMatrix =  this->getFinalWorldMatrix();
	D3DXMATRIXA16 viewMatrix = GET_CAMERA()->getViewMatrix();
	D3DXMATRIXA16 projectionMatrix = GET_CAMERA()->getProjectionMatrix();

	_effect->SetMatrix("_worldMatrix", &worldMatrix);
	_effect->SetMatrix("_viewMatrix", &viewMatrix);
	_effect->SetMatrix("_projectionMatrix", &projectionMatrix);

	for (int i = 0; i < _textureList.size(); ++i) {
		char textureName[MAX_PATH] = "";
		sprintf(textureName, "_texture%02d", i+1);
		_effect->SetTexture(textureName, _textureList[i]);
	}

	_effect->SetTexture("_splatTexture", _splatTexture);
	_effect->SetVector("_viewPosition", &D3DXVECTOR4(GET_CAMERA()->getPosition(), 0.0f));
	_effect->SetVector("_lightDirection", &D3DXVECTOR4(GET_LIGHT()->getForwardDirection(), 1.0f));

	_effect->SetTechnique("MyTechnique");

	UINT numPasses = 0;

	_effect->Begin(&numPasses, 0);
	for (int i = 0; i < numPasses; ++i) {
		_effect->BeginPass(i);

		_mesh->DrawSubset(0);

		_effect->EndPass();
	}

	_effect->End();
}

void CTerrain::SetupTerrainInfo(const STParameters & parameters)
{
	auto heightMapTexture = GET_TEXTURE(parameters.heightFilepath);

	D3DSURFACE_DESC surfaceDesc;
	heightMapTexture->GetLevelDesc(0, &surfaceDesc);

	_mapSize.cx = surfaceDesc.Width;
	_mapSize.cy = surfaceDesc.Height;

	_tileSize.cx = parameters.tileSize.cx;
	_tileSize.cy = parameters.tileSize.cy;

	_totalSize.cx = _mapSize.cx * _tileSize.cx;
	_totalSize.cy = _mapSize.cy * _tileSize.cy;

	_heightScale = parameters.heightScale;
}

void CTerrain::SetupTerrainHeight(const STParameters & parameters)
{
	auto heightTexture = GET_TEXTURE(parameters.heightFilepath);

	D3DLOCKED_RECT lockedRect;

	if (SUCCEEDED(heightTexture->LockRect(0, &lockedRect, nullptr, 0))) {
		DWORD *bytes = (DWORD *)lockedRect.pBits;

		for (int i = 0; i < _mapSize.cy; ++i) {
			for (int j = 0; j < _mapSize.cx; ++j) {
				int index = (i * _mapSize.cx) + j;
				D3DCOLOR color = bytes[index];

				int redColor = (color >> 16) & 0xff;
				int greenColor = (color >> 8) & 0xff;
				int blueColor = (color >> 0) & 0xff;

				int height = redColor + greenColor + blueColor;
				_heightList.push_back(height * _heightScale);
			}
		}
		heightTexture->UnlockRect(0);
	}


	this->SmoothTerrainHeight(parameters);
}

void CTerrain::SmoothTerrainHeight(const STParameters & parameters)
{
	for(int k = 0; k < parameters.smoothLevel; ++k)
	{
		std::vector<float> smoothHeightList;
		std::vector<float> adjacencyHeightList;

		for (int i = 0; i < _mapSize.cy; ++i) {
			for (int j = 0; j < _mapSize.cx; ++j) {
				int index = (i * _mapSize.cx) + j;
				adjacencyHeightList.clear();

				// 왼쪽 정점 
				if (j >= 1) {
					float height = _heightList[index - 1];
					adjacencyHeightList.push_back(height);
				}

				// 오른쪽 
				if (j < _mapSize.cx - 1) {
					float height = _heightList[index + 1];
					adjacencyHeightList.push_back(height);
				}

				// 위쪽
				if (i >= 1) {
					float height = _heightList[index - _mapSize.cx];
					adjacencyHeightList.push_back(height);

					// 왼쪽 위 
					if (j >= 1) {
						float height = _heightList[index - _mapSize.cx - 1];
						adjacencyHeightList.push_back(height);
					}

					// 오른쪽 위
					if (j < _mapSize.cx - 1) {
						float height = _heightList[index - _mapSize.cx + 1];
						adjacencyHeightList.push_back(height);
					}

				}

				// 아래쪽
				if (i < _mapSize.cy - 1) {
					float height = _heightList[index + _mapSize.cx];
					adjacencyHeightList.push_back(height);

					// 아래 왼쪽 정점 
					if (j >= 1) {
						float height = _heightList[index + _mapSize.cx - 1];
						adjacencyHeightList.push_back(height);
					}

					// 아래 오른쪽 
					if (j < _mapSize.cx - 1) {
						float height = _heightList[index + _mapSize.cx + 1];
						adjacencyHeightList.push_back(height);
					}
				}

				float height = _heightList[index];

				// accumulate 함수는 합계를 계산해주는 표준 함수이다.
				float totalHeight =
					height +
					std::accumulate(adjacencyHeightList.begin(), adjacencyHeightList.end(), 0.0f);

				smoothHeightList.push_back(totalHeight / (float)(adjacencyHeightList.size() + 1));
			}
		}
		// assign 함수는 기존의 값을 덮어쓰는 함수이다.
		_heightList.assign(smoothHeightList.begin(), smoothHeightList.end());

	}
}

LPD3DXMESH CTerrain::CreateTerrainMesh(const STParameters & parameters)
{
	// 메시를 생성한다
	D3DVERTEXELEMENT9 elements[] = {
		0,  0, D3DDECLTYPE_FLOAT3, D3DDECLMETHOD_DEFAULT, D3DDECLUSAGE_POSITION, 0,
		0, 12, D3DDECLTYPE_FLOAT3, D3DDECLMETHOD_DEFAULT, D3DDECLUSAGE_NORMAL,   0,
		0, 24, D3DDECLTYPE_FLOAT3, D3DDECLMETHOD_DEFAULT, D3DDECLUSAGE_TANGENT,  0,
		0, 36, D3DDECLTYPE_FLOAT3, D3DDECLMETHOD_DEFAULT, D3DDECLUSAGE_BINORMAL, 0,
		0, 48, D3DDECLTYPE_FLOAT2, D3DDECLMETHOD_DEFAULT, D3DDECLUSAGE_TEXCOORD, 0,
		D3DDECL_END(),
	};

	LPD3DXMESH mesh = nullptr;

	D3DXCreateMesh((_mapSize.cx * _mapSize.cy) * 2,
		_mapSize.cy * _mapSize.cy,
		D3DXMESH_MANAGED | D3DXMESH_32BIT,
		elements,
		GET_DEVICE(),
		&mesh);

	// 정점 정보를 설정한다
	// {
	STVertex *vertices = nullptr;

	if (SUCCEEDED(mesh->LockVertexBuffer(0, (void **)&vertices))) {
		D3DXVECTOR3 basePosition = {
			(_totalSize.cx / -2.0f) + (_tileSize.cx / 2.0f),
			0.0f,
			(_totalSize.cy / 2.0f) - (_tileSize.cy / 2.0f)
		};

		for (int i = 0; i < _mapSize.cy; ++i) {
			for (int j = 0; j < _mapSize.cx; ++j) {
				int index = (i * _mapSize.cx) + j;

				vertices[index].position =
					basePosition +
					D3DXVECTOR3(j * _tileSize.cx, _heightList[index], i * -_tileSize.cy);

				vertices[index].UV = D3DXVECTOR2(j / (_mapSize.cx - 1.0f), i / (_mapSize.cy - 1.0f));
			}
		}

		mesh->UnlockVertexBuffer();
	}
	// }


	// 인덱스 정보를 설정한다
	// {
	DWORD * indices = nullptr;

	if (SUCCEEDED(mesh->LockIndexBuffer(0, (void **)&indices))) {
		for (int i = 0; i < _mapSize.cy - 1; ++i) {
			for (int j = 0; j < _mapSize.cx - 1; ++j) {
				int vertexIndex = (i * _mapSize.cx) + j;
				int index = vertexIndex * 6;

				// 왼쪽 삼각형
				indices[index + 0] = vertexIndex;
				indices[index + 1] = vertexIndex + 1;
				indices[index + 2] = vertexIndex + _mapSize.cx;

				// 오른쪽 삼각형
				indices[index + 3] = vertexIndex + _mapSize.cx;
				indices[index + 4] = vertexIndex + 1;
				indices[index + 5] = vertexIndex + _mapSize.cx + 1;
			}
		}

		mesh->UnlockIndexBuffer();
	}
	// }


	// 법선 정보를 계산한다
	D3DXComputeNormals(mesh, nullptr);

	// 접선, 종법선 정보를 계산한다
	D3DXComputeTangent(mesh, 0, 0, 0, true, nullptr);

	return mesh;
}

std::vector<LPDIRECT3DTEXTURE9> CTerrain::CreateTerrainTextures(const STParameters & parameters, LPDIRECT3DTEXTURE9 * outSplatTexture)
{
	std::vector<LPDIRECT3DTEXTURE9> textureList;
	*outSplatTexture = GET_TEXTURE(parameters.splatFilepath);

	for (auto &textureFilepath : parameters.textureFilepathList) {
		auto texture = GET_TEXTURE(textureFilepath);
		textureList.push_back(texture);
	}

	return textureList;
}


float CTerrain::getTerrainHeightAtPosition(const D3DXVECTOR3 & position)
{
	float mapPositionX = ((_totalSize.cx / 2.0f) + position.x) / _tileSize.cx;
	float mapPositionZ = ((_totalSize.cy / 2.0f) - position.z) / _tileSize.cy;

	int mapIndexX = (int)mapPositionX;
	int mapIndexZ = (int)mapPositionZ;

	int index = (mapIndexZ * _mapSize.cx) + mapIndexX;

	float percentX = mapPositionX - mapIndexX;
	float percentZ = mapPositionZ - mapIndexZ;

	float heightLT = _heightList[index];
	float heightRT = _heightList[index + 1];
	float heightLB = _heightList[index + _mapSize.cx];
	float heightRB = _heightList[index + _mapSize.cx + 1];

	// 왼쪽 삼각형 위에 있을 경우
	if (1.0f - percentX > percentZ) {
		return heightLT +
			((heightRT - heightLT) * percentX) +
			((heightLB - heightLT) * percentZ);
	}

	// 오른쪽 삼각형 위에 있을 경우
	return heightRB +
		((heightLB - heightRB) * (1.0f - percentX)) +
		((heightRT - heightRB) * (1.0f - percentZ));
}
