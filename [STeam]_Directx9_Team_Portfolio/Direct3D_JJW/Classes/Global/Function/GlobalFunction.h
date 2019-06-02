#pragma once

#include "../Define/KGlobalDefine.h"

//! �ٿ�� �ڽ��� �浹 ���θ� �˻��Ѵ�
bool isIntersectBox(const STBoundingBox &leftBox, const STBoundingBox rightBox);

//! �ٿ�� ���Ǿ��� �浹 ���θ� �˻��Ѵ�
bool isIntersectSphere(const STBoundingSphere &leftSphere, const STBoundingSphere &rightSphere);

float intersectSphereValue(const STBoundingSphere & leftSphere, const STBoundingSphere & rightSphere);

bool isIntersectSphereTera(const D3DXVECTOR3 & leftPosition, float leftRadius, const D3DXVECTOR3 & rightPosition, float rightRadius);

//! ������ ���� �浹 ���θ� �˻��Ѵ�
bool IsIntersectRaySphere(const STRay &ray, const STBoundingSphere &boundingSphere);

// ������ �ٿ�� ���Ǿ �����Ѵ�.
STBoundingSphere CreateBoundingSphereTREE(LPD3DXMESH _Sphere, STSphereSRT _STSphereSRT);

//! ������ �ڽ��� �浹 ���θ� �˻��Ѵ�
bool IsIntersectRayBox(const STRay &ray, const STBoundingBox &boundingBox);

//! ��ü �ڽ� -> �ٿ�� �ڽ� ��ȯ
STBoundingBox ConvertObjectBoxToBox(const STObjectBox &objectBox);

//! ���� ���� ���� �����Ѵ�
int CreateIntRandomValue(int min, int max);

//! �Ǽ� ���� ���� �����Ѵ�
float CreateFloatRandomValue(float min, float max);

//! ������ �����Ѵ�
STRay CreateRay(const POINT &point);

//! �ٿ�� �ڽ��� �����Ѵ�
STBoundingBox CreateBoundingBox(LPD3DXMESH mesh);

//! �ٿ�� ���Ǿ �����Ѵ�
STBoundingSphere CreateBoundingSphere(LPD3DXMESH mesh);


// �����ٷ�


// �����ٷ��� �ð��� �ϷḦ ����ϴ� �Լ�
