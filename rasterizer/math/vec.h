#ifndef __VEC_H__
#define __VEC_H__

#include <math.h>

struct Vec2 
{
	float px, py;
};

struct Vec3 
{
	float px, py, pz;
};

struct Vec4 
{
	float px, py, pz, pw;
};

__forceinline Vec4 Vec4Set(float x, float y, float z, float w)
{
	Vec4 v;
	v.px = x; v.py = y; v.pz = z; v.pw = w;
	return v;
}

//Vec4 XMVector3Dot
//(
// FXMVECTOR V1, 
// FXMVECTOR V2
// )
//{
//	FLOAT fValue = V1.vector4_f32[0] * V2.vector4_f32[0] + V1.vector4_f32[1] * V2.vector4_f32[1] + V1.vector4_f32[2] * V2.vector4_f32[2];
//	XMVECTOR vResult = {
//		fValue,
//		fValue,
//		fValue,
//		fValue
//	};            
//	return vResult;
//}

Vec4 Vec4Subtract
(
 Vec4 v1,
 Vec4 v2
 )
{

	Vec4 result;

	result.px = v1.px - v2.px;
	result.py = v1.py - v2.py;
	result.pz = v1.pz - v2.pz;
	result.pw = v1.pw - v2.pw;

	return result;
}

struct Matrix
{
	union
	{
		Vec4 r[4];
		struct
		{
			float _11, _12, _13, _14;
			float _21, _22, _23, _24;
			float _31, _32, _33, _34;
			float _41, _42, _43, _44;
		};
		float m[4][4];
	};
};

Matrix MatrixIdentity()
{
	Matrix m;

	m._11 = 1.f; m._12 = 0.f; m._13 = 0.f; m._14 = 0.f;
	m._21 = 0.f; m._22 = 1.f; m._23 = 0.f; m._24 = 0.f;
	m._31 = 0.f; m._32 = 0.f; m._33 = 1.f; m._34 = 0.f;
	m._41 = 0.f; m._42 = 0.f; m._43 = 0.f; m._44 = 1.f;

	return m;
}

Matrix MatrixTranslation(float x, float y, float z)
{
	Matrix m;

	m._11 = 1.f; m._12 = 0.f; m._13 = 0.f; m._14 = 0.f;
	m._21 = 0.f; m._22 = 1.f; m._23 = 0.f; m._24 = 0.f;
	m._31 = 0.f; m._32 = 0.f; m._33 = 1.f; m._34 = 0.f;
	m._41 = x;	 m._42 = y;   m._43 = z;   m._44 = 1.f;

	return m;
}

Matrix MatrixScaling
(
 float scaleX, 
 float scaleY, 
 float scaleZ
 )
{
	Matrix m;

	m._11 = scaleX; m._12 = 0.f;	m._13 = 0.f;	m._14 = 0.f;
	m._21 = 0.f;	m._22 = scaleY; m._23 = 0.f;	m._24 = 0.f;
	m._31 = 0.f;	m._32 = 0.f;	m._33 = scaleZ; m._34 = 0.f;
	m._41 = 0.f;	m._42 = 0.f;	m._43 = 0.f;	m._44 = 1.f;

	return m;
}

Matrix MatrixRotationX
(
 float Angle
 )
{
	Matrix m;

	float fSinAngle = sinf(Angle);
	float fCosAngle = cosf(Angle);

	m._11 = 1.0f; m._12 = 0.0f;		 m._13 = 0.0f;		m._14 = 0.0f;
	m._21 = 0.0f; m._22 = fCosAngle; m._23 = fSinAngle;	m._24 = 0.0f;
	m._31 = 0.0f; m._32 = -fSinAngle;m._33 = fCosAngle; m._34 = 0.0f;
	m._41 = 0.0f; m._42 = 0.0f;		 m._43 = 0.0f;		m._44 = 1.0f;

	return m;
}

Matrix MatrixRotationY
(
 FLOAT Angle
 )
{
	Matrix m;

	FLOAT fSinAngle = sinf(Angle);
	FLOAT fCosAngle = cosf(Angle);

	m._11 = fCosAngle;	m._12 = 0.0f; m._13 = -fSinAngle;	m._14 = 0.0f;
	m._21 = 0.0f;		m._22 = 1.0f; m._23 = 0.0f;			m._24 = 0.0f;
	m._31 = fSinAngle;	m._32 = 0.0f; m._33 = fCosAngle;	m._34 = 0.0f;
	m._41 = 0.0f;		m._42 = 0.0f; m._43 = 0.0f;			m._44 = 1.0f;

	return m;
}

Matrix MatrixRotationZ
(
 FLOAT Angle
 )
{
	Matrix m;

	FLOAT fSinAngle = sinf(Angle);
	FLOAT fCosAngle = cosf(Angle);

	m._11 = fCosAngle;	m._12 = fSinAngle;	m._13 = 0.0f; m._14 = 0.0f;
	m._21 = -fSinAngle; m._22 = fCosAngle;	m._23 = 0.0f; m._24 = 0.0f;
	m._31 = 0.0f;		m._32 = 0.0f;		m._33 = 1.0f; m._34 = 0.0f;
	m._41 = 0.0f;		m._42 = 0.0f;		m._43 = 0.0f; m._44 = 1.0f;

	return m;
}

Matrix MatrixLookAtLH
(
 Vec4 eyePosition, 
 Vec4 lookAt, 
 Vec4 upDirection
 )
{
	Vec4 eyeDirection;
	Matrix m;

	eyeDirection = Vec4Subtract(lookAt, eyePosition);
	//m = XMMatrixLookToLH(eyePosition, eyeDirection, upDirection);

	return m;
}

Matrix MatrixLookToLH(Vec4 eyePosition, Vec4 eyeDirection, Vec4 upDirection)
{
	Vec4 negEyePosition;
	Vec4 d0, d1, d2;
	Vec4 r0, r1, r2;
	Matrix m;

	//XMASSERT(!XMVector3Equal(EyeDirection, XMVectorZero()));
	//XMASSERT(!XMVector3IsInfinite(EyeDirection));
	//XMASSERT(!XMVector3Equal(UpDirection, XMVectorZero()));
	//XMASSERT(!XMVector3IsInfinite(UpDirection));

	//R2 = XMVector3Normalize(EyeDirection);

	//R0 = XMVector3Cross(UpDirection, R2);
	//R0 = XMVector3Normalize(R0);

	//R1 = XMVector3Cross(R2, R0);

	//NegEyePosition = XMVectorNegate(EyePosition);

	//D0 = XMVector3Dot(R0, NegEyePosition);
	//D1 = XMVector3Dot(R1, NegEyePosition);
	//D2 = XMVector3Dot(R2, NegEyePosition);

	//M.r[0] = XMVectorSelect(D0, R0, g_XMSelect1110.v);
	//M.r[1] = XMVectorSelect(D1, R1, g_XMSelect1110.v);
	//M.r[2] = XMVectorSelect(D2, R2, g_XMSelect1110.v);
	//M.r[3] = g_XMIdentityR3.v;

	//M = XMMatrixTranspose(M);

	return m;
}
#endif