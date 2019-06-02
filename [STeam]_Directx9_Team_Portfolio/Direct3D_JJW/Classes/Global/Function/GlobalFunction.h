#pragma once

#include "../Define/KGlobalDefine.h"

//! 바운딩 박스의 충돌 여부를 검사한다
bool isIntersectBox(const STBoundingBox &leftBox, const STBoundingBox rightBox);

//! 바운딩 스피어의 충돌 여부를 검사한다
bool isIntersectSphere(const STBoundingSphere &leftSphere, const STBoundingSphere &rightSphere);

float intersectSphereValue(const STBoundingSphere & leftSphere, const STBoundingSphere & rightSphere);

bool isIntersectSphereTera(const D3DXVECTOR3 & leftPosition, float leftRadius, const D3DXVECTOR3 & rightPosition, float rightRadius);

//! 광선과 구의 충돌 여부를 검사한다
bool IsIntersectRaySphere(const STRay &ray, const STBoundingSphere &boundingSphere);

// 나무용 바운딩 스피어를 생성한다.
STBoundingSphere CreateBoundingSphereTREE(LPD3DXMESH _Sphere, STSphereSRT _STSphereSRT);

//! 광선과 박스의 충돌 여부를 검사한다
bool IsIntersectRayBox(const STRay &ray, const STBoundingBox &boundingBox);

//! 객체 박스 -> 바운딩 박스 변환
STBoundingBox ConvertObjectBoxToBox(const STObjectBox &objectBox);

//! 정수 랜덤 값을 생성한다
int CreateIntRandomValue(int min, int max);

//! 실수 랜덤 값을 생성한다
float CreateFloatRandomValue(float min, float max);

//! 광선을 생성한다
STRay CreateRay(const POINT &point);

//! 바운딩 박스를 생성한다
STBoundingBox CreateBoundingBox(LPD3DXMESH mesh);

//! 바운딩 스피어를 생성한다
STBoundingSphere CreateBoundingSphere(LPD3DXMESH mesh);


// 스케줄러


// 스케줄러의 시간의 완료를 계산하는 함수
