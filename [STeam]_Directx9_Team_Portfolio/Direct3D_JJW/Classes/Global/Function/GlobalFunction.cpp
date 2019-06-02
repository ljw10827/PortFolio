#include "GlobalFunction.h"
#include "../Utility/Manager/CDeviceManager.h"
#include "../Utility/Base/CDirect3DApplication.h"
#include "../Utility/Object/CCamera.h"

bool isIntersectBox(const STBoundingBox & leftBox, const STBoundingBox rightBox)
{
	// X 축 검사
	if (leftBox.minPosition.x > rightBox.maxPosition.x ||
		leftBox.maxPosition.x < rightBox.minPosition.x)
	{
		return false;
	}

	// Y 축 검사
	if (leftBox.minPosition.y > rightBox.maxPosition.y ||
		leftBox.maxPosition.y < rightBox.minPosition.y)
	{
		return false;
	}

	// Z 축 검사
	if (leftBox.minPosition.z > rightBox.maxPosition.z ||
		leftBox.maxPosition.z < rightBox.minPosition.z)
	{
		return false;
	}

	return true;
}

bool isIntersectSphere(const STBoundingSphere & leftSphere, const STBoundingSphere & rightSphere)
{
	auto delta = leftSphere.centerPosition - rightSphere.centerPosition;

	return D3DXVec3Length(&delta) <= (leftSphere.radius + rightSphere.radius);
}

float intersectSphereValue(const STBoundingSphere & leftSphere, const STBoundingSphere & rightSphere)
{
	auto delta = leftSphere.centerPosition - rightSphere.centerPosition;

	auto sum = (leftSphere.radius + rightSphere.radius);

	if (D3DXVec3Length(&delta) <= (leftSphere.radius + rightSphere.radius)) {
		return sum - D3DXVec3Length(&delta);
	}
}

bool isIntersectSphereTera(const D3DXVECTOR3 &leftPosition, float leftRadius, const D3DXVECTOR3 &rightPosition, float rightRadius)
{
	auto delta = leftPosition - rightPosition;

	return D3DXVec3Length(&delta) <= (leftRadius + rightRadius);
}

bool IsIntersectRayBox(const STRay & a_rstRay, const STBoundingBox & a_rstBoundingBox)
{
	float fMaxS = -FLT_MAX;
	float fMinT = FLT_MAX;

	// X 축 검사
	// {
	if (fabsf(a_rstRay.direction.x) <= FLT_EPSILON) {
		if (a_rstRay.origin.x < a_rstBoundingBox.minPosition.x ||
			a_rstRay.origin.x > a_rstBoundingBox.maxPosition.x)
		{
			return false;
		}
	}
	else {
		float fS = (a_rstBoundingBox.minPosition.x - a_rstRay.origin.x) / a_rstRay.direction.x;
		float fT = (a_rstBoundingBox.maxPosition.x - a_rstRay.origin.x) / a_rstRay.direction.x;

		if (fT < fS) {
			std::swap(fS, fT);
		}

		if (fS > fMaxS) {
			fMaxS = fS;
		}

		if (fT < fMinT) {
			fMinT = fT;
		}

		if (fMinT < 0.0f || fMaxS > fMinT) {
			return false;
		}
	}
	// }

	// Y 축 검사
	// {
	if (fabsf(a_rstRay.direction.y) <= FLT_EPSILON) {
		if (a_rstRay.origin.y < a_rstBoundingBox.minPosition.y ||
			a_rstRay.origin.y > a_rstBoundingBox.maxPosition.y)
		{
			return false;
		}
	}
	else {
		float fS = (a_rstBoundingBox.minPosition.y - a_rstRay.origin.y) / a_rstRay.direction.y;
		float fT = (a_rstBoundingBox.maxPosition.y - a_rstRay.origin.y) / a_rstRay.direction.y;

		if (fT < fS) {
			std::swap(fS, fT);
		}

		if (fS > fMaxS) {
			fMaxS = fS;
		}

		if (fT < fMinT) {
			fMinT = fT;
		}

		if (fMinT < 0.0f || fMaxS > fMinT) {
			return false;
		}
	}
	// }

	// Z 축 검사
	// {
	if (fabsf(a_rstRay.direction.z) <= FLT_EPSILON) {
		if (a_rstRay.origin.z < a_rstBoundingBox.minPosition.z ||
			a_rstRay.origin.z > a_rstBoundingBox.maxPosition.z)
		{
			return false;
		}
	}
	else {
		float fS = (a_rstBoundingBox.minPosition.z - a_rstRay.origin.z) / a_rstRay.direction.z;
		float fT = (a_rstBoundingBox.maxPosition.z - a_rstRay.origin.z) / a_rstRay.direction.z;

		if (fT < fS) {
			std::swap(fS, fT);
		}

		if (fS > fMaxS) {
			fMaxS = fS;
		}

		if (fT < fMinT) {
			fMinT = fT;
		}

		if (fMinT < 0.0f || fMaxS > fMinT) {
			return false;
		}
	}
	// }

	return true;
}

bool IsIntersectRaySphere(const STRay & a_rstRay, const STBoundingSphere & a_rstBoundingSphere)
{
	D3DXVECTOR3 stW = a_rstBoundingSphere.centerPosition - a_rstRay.origin;
	D3DXVECTOR3 stDirection = a_rstRay.direction;

	// 방향 벡터를 정규화한다
	D3DXVec3Normalize(&stDirection, &stDirection);

	float fWsq = D3DXVec3Dot(&stW, &stW);
	float fRsq = pow(a_rstBoundingSphere.radius, 2);
	float fProj = D3DXVec3Dot(&stW, &stDirection);

	if (fProj < 0.0f && fWsq > fRsq) {
		return false;
	}

	float fVsq = D3DXVec3Dot(&stDirection, &stDirection);
	return (fVsq * fWsq) - (fProj * fProj) <= fVsq * fRsq;
}

STBoundingSphere CreateBoundingSphereTREE(LPD3DXMESH _Sphere, STSphereSRT _STSphereSRT)
{
	STBoundingSphere stBoundingSphere;
	ZeroMemory(&stBoundingSphere, sizeof(stBoundingSphere));

	// 바운드 스피어를 설정한다.
	BYTE * pnVertices = nullptr;
	if (SUCCEEDED(_Sphere->LockVertexBuffer(0, (void**)&pnVertices)))
	{
		D3DXComputeBoundingSphere((D3DXVECTOR3*)pnVertices,
			_Sphere->GetNumVertices(),
			_Sphere->GetNumBytesPerVertex(),
			&stBoundingSphere.centerPosition,
			&stBoundingSphere.radius
		);
		_Sphere->UnlockVertexBuffer();
	}

	stBoundingSphere.radius *= _STSphereSRT.Radius;
	stBoundingSphere.centerPosition += _STSphereSRT.position;

	return stBoundingSphere;
}

STBoundingBox ConvertObjectBoxToBox(const STObjectBox & objectBox)
{
	STBoundingBox boundingBox;
	ZeroMemory(&boundingBox, sizeof(boundingBox));

	// 새로운 정점을 설정한다
	// {
	D3DXVECTOR3 centerPosition = objectBox.centerPosition;
	D3DXVECTOR3 XAxis = objectBox.axis[X_DIRECTION] * objectBox.halfLengths[X_DIRECTION];
	D3DXVECTOR3 YAxis = objectBox.axis[Y_DIRECTION] * objectBox.halfLengths[Y_DIRECTION];
	D3DXVECTOR3 ZAxis = objectBox.axis[Z_DIRECTION] * objectBox.halfLengths[Z_DIRECTION];

	D3DXVECTOR3 vertices[8] = {
		centerPosition + XAxis + YAxis + ZAxis,
		centerPosition - XAxis + YAxis + ZAxis,
		centerPosition + XAxis - YAxis + ZAxis,
		centerPosition - XAxis - YAxis + ZAxis,

		centerPosition + XAxis + YAxis - ZAxis,
		centerPosition - XAxis + YAxis - ZAxis,
		centerPosition + XAxis - YAxis - ZAxis,
		centerPosition - XAxis - YAxis - ZAxis
	};
	// }

	// 최소, 최고 점을 설정한다
	// {
	boundingBox.minPosition = objectBox.centerPosition;
	boundingBox.maxPosition = objectBox.centerPosition;

	for (int i = 0; i < sizeof(vertices) / sizeof(vertices[0]); ++i) {
		D3DXVECTOR3 vertex = vertices[i];

		// X 위치 비교
		if (vertex.x <= boundingBox.minPosition.x) {
			boundingBox.minPosition.x = vertex.x;
		}
		if(vertex.x >= boundingBox.maxPosition.x){
			boundingBox.maxPosition.x = vertex.x;
		}

		// Y 위치 비교
		if (vertex.y <= boundingBox.minPosition.y) {
			boundingBox.minPosition.y = vertex.y;
		}
		if (vertex.y >= boundingBox.maxPosition.y) {
			boundingBox.maxPosition.y = vertex.y;
		}

		// Z 위치 비교
		if (vertex.z <= boundingBox.minPosition.z) {
			boundingBox.minPosition.z = vertex.z;
		}
		if (vertex.z >= boundingBox.maxPosition.z) {
			boundingBox.maxPosition.z = vertex.z;
		}
	}
	// }

	return boundingBox;
}

int CreateIntRandomValue(int min, int max)
{
	std::random_device randomDevice;
	std::uniform_int_distribution<int> uniformRandom(min, max);

	return uniformRandom(randomDevice);
}

float CreateFloatRandomValue(float min, float max)
{
	std::random_device randomDevice;
	std::uniform_real_distribution<float> uniformRandom(min, max);

	return uniformRandom(randomDevice);
}

STRay CreateRay(const POINT & point)
{
	D3DVIEWPORT9 viewport;
	GET_DEVICE()->GetViewport(&viewport);

	//! 스크린 좌표 -> 정규좌표
	float normalizeX = ((point.x * 2.0f) / viewport.Width) - 1.0f;
	float normalizeY = ((point.y * -2.0f) / viewport.Height) + 1.0f;

	//! 정규좌표 -> 투영 -> 뷰
	auto viewMatrix = GET_CAMERA()->getViewMatrix();
	auto projectionMatrix = GET_CAMERA()->getProjectionMatrix();

	STRay ray = {
		D3DXVECTOR3(0.0f, 0.0f, 0.0f),
		D3DXVECTOR3(normalizeX / projectionMatrix(0,0),
		normalizeY / projectionMatrix(1, 1),
		1.0f)
	};

	//! 뷰 -> 월드
	D3DXMATRIXA16 inverseMatrix;
	D3DXMatrixInverse(&inverseMatrix, nullptr, &viewMatrix);

	D3DXVec3TransformCoord(&ray.origin, &ray.origin, &inverseMatrix);
	D3DXVec3TransformNormal(&ray.direction, &ray.direction, &inverseMatrix);

	D3DXVec3Normalize(&ray.direction, &ray.direction);

	return ray;
}

STBoundingBox CreateBoundingBox(LPD3DXMESH mesh)
{
	STBoundingBox boundingBox;
	ZeroMemory(&boundingBox, sizeof(STBoundingBox));

	// 바운딩 박스를 설정한다
	// {
	BYTE *vertices = nullptr;

	if (SUCCEEDED(mesh->LockVertexBuffer(0, (void **)&vertices))) {
		D3DXComputeBoundingBox((D3DXVECTOR3 *)vertices,
			mesh->GetNumVertices(),
			mesh->GetNumBytesPerVertex(),
			&boundingBox.minPosition,
			&boundingBox.maxPosition);
		
		mesh->UnlockVertexBuffer();
	}

	// }

	return boundingBox;
}

STBoundingSphere CreateBoundingSphere(LPD3DXMESH mesh)
{
	STBoundingSphere boundingSphere;
	ZeroMemory(&boundingSphere, sizeof(STBoundingSphere));

	// 바운딩 스피어를 설정한다
	//{
	BYTE *vertices = nullptr;

	if (SUCCEEDED(mesh->LockVertexBuffer(0, (void **)&vertices))) {
		D3DXComputeBoundingSphere((D3DXVECTOR3 *)vertices,
			mesh->GetNumVertices(),
			mesh->GetNumBytesPerVertex(),
			&boundingSphere.centerPosition,
			&boundingSphere.radius);

		mesh->UnlockVertexBuffer();
	}

	//}

	return boundingSphere;
}
