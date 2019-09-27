#include "DXUT.h"
#include "CPhysic.h"

using namespace Math;
CPhysic::CPhysic()
{
}


CPhysic::~CPhysic()
{
}

bool CPhysic::GetPixelCollision(CTexture * _pTexture, CRRect _Box, D3DXCOLOR _Color)
{
	D3DLOCKED_RECT LockRect;

	_pTexture->m_pTexture->LockRect(0, &LockRect, 0, D3DLOCK_DISCARD);

	DWORD* pColor = (DWORD*)LockRect.pBits; // 잠금후 픽셀 값 받아오기

	for (int i = _Box.Top; i < _Box.Bottom; i++)
	{
		for (int j = _Box.Left; j < _Box.Right; i++)
		{
			D3DXCOLOR col = pColor[_pTexture->m_Info.Width * i + j];

			if (col == _Color)
			{
				_pTexture->m_pTexture->UnlockRect(0); //  잠금 해제
				return true;
			}
		}
	}
	_pTexture->m_pTexture->UnlockRect(0); //  잠금 해제
	return false;
}

bool CPhysic::GetPixelCollision(CTexture * _pTexture, CRVector2 _Pos, D3DXCOLOR _Color)
{
	D3DLOCKED_RECT LockRect;

	_pTexture->m_pTexture->LockRect(0, &LockRect, 0, D3DLOCK_DISCARD);

	DWORD* pColor = (DWORD*)LockRect.pBits; // 잠금후 픽셀 값 받아오기

	D3DXCOLOR col = pColor[_pTexture->m_Info.Width * (INT)_Pos.y + (INT)_Pos.x];

	bool Collision = false;
	if (col == _Color)
		Collision = true;

	_pTexture->m_pTexture->UnlockRect(0); //  잠금 해제
	return Collision;
}

bool CPhysic::CheckCollision(const Rect & _reRect, const Vector2 & _vPos)
{
	return (_reRect.Left < _vPos.x &&
		_reRect.Top < _vPos.y &&
		_reRect.Right > _vPos.x &&
		_reRect.Bottom > _vPos.y);
}

bool CPhysic::CheckCollision(const Vector2 & _vPos, const Rect & _reRect)
{
	return CheckCollision(_reRect, _vPos);
}

bool CPhysic::CheckCollision(const Rect & _reRect01, const Rect & _reRect02)
{
	return (_reRect01.Left < _reRect02.Right &&
		_reRect01.Top <  _reRect02.Bottom &&
		_reRect01.Right > _reRect02.Left &&
		_reRect01.Bottom > _reRect02.Bottom);
}

bool CPhysic::CheckCollision(const Rect & _reRect01, float _fRot01, const Rect & _reRect02, float _fRot02)
{
	Vector2 dist = GetDistanceVector(_reRect01, _reRect02);
	Vector2 vec[4] = { GetHeightVector(_reRect01,_fRot01), GetHeightVector(_reRect02,_fRot02), GetWidthVector(_reRect01,_fRot01), GetWidthVector(_reRect02,_fRot02) };

	Vector2 unit;
	for (int i = 0; i < 4; i++) {
		double sum = 0;
		unit = GetUnitVector(vec[i]);
		for (int j = 0; j < 4; j++) {
			sum += absDotVector(vec[j], unit);
		}
		if (absDotVector(dist, unit) > sum) {
			return false;
		}
	}
	return true;
}

bool CPhysic::CheckCollision( const Box& _Box01, float _fRot01, const Box& _Box02, float _fRot02)
{
	Box Box01 = _Box01;
	Box Box02 = _Box02;

	Vector3 D = _Box01.Center - _Box02.Center;

	Vector3 C[3];
	Vector3 absC[3];
	Vector3 AD;
	Vector3 Radius;
	float R0, R1, R;
	float R01;

	
	C[0].x = D3DXVec3Dot(&Box01.GetAxisX(), &Box02.GetAxisX());
	C[0].y = D3DXVec3Dot(&Box01.GetAxisX(), &Box02.GetAxisY());
	C[0].z = D3DXVec3Dot(&Box01.GetAxisX(), &Box02.GetAxisZ());
	AD.x = D3DXVec3Dot(&Box01.GetAxisX(), &D);
	absC[0].x = fabsf(C[0].x);
	absC[0].y = fabsf(C[0].y);
	absC[0].z = fabsf(C[0].z);

	R = fabs(AD.x);
	R1 = Box01.Radius.x * absC[0].x + Box01.Radius.y * absC[0].y + Box01.Radius.z * absC[0].z;
	R01 = Box01.Radius.x + R1;
	if (R > R01)return 0;

	//A1
	C[1].x = D3DXVec3Dot(&Box01.GetAxisY(), &Box02.GetAxisX());
	C[1].y = D3DXVec3Dot(&Box01.GetAxisY(), &Box02.GetAxisY());
	C[1].z = D3DXVec3Dot(&Box01.GetAxisY(), &Box02.GetAxisZ());
	AD.y = D3DXVec3Dot(&Box01.GetAxisY(), &D);
	absC[1].x = fabsf(C[1].x);
	absC[1].y = fabsf(C[1].y);
	absC[1].z = fabsf(C[1].z);
	R = fabsf(AD.y);
	R1 = Box01.Radius.x * absC[1].x + Box01.Radius.y * absC[1].y + Box01.Radius.z * absC[1].z;
	R01 = Box01.Radius.y + R1;
	if (R > R01)return 0;

	//A2
	C[2].x = D3DXVec3Dot(&Box01.GetAxisZ(), &Box02.GetAxisX());
	C[2].y = D3DXVec3Dot(&Box01.GetAxisZ(), &Box02.GetAxisY());
	C[2].z = D3DXVec3Dot(&Box01.GetAxisZ(), &Box02.GetAxisZ());
	AD.z = D3DXVec3Dot(&Box01.GetAxisZ(), &D);
	absC[2].x = fabsf(C[2].x);
	absC[2].y = fabsf(C[2].y);
	absC[2].z = fabsf(C[2].z);
	R = fabsf(AD.z);
	R1 = Box01.Radius.x * absC[2].x + Box01.Radius.y * absC[2].y + Box01.Radius.z * absC[2].z;
	R01 = Box01.Radius.z + R1;
	if (R > R01)return 0;

	//B0
	R = fabsf(D3DXVec3Dot(&Box01.GetAxisX(), &D));
	R0 = Box01.Radius.x * absC[0].x + Box01.Radius.y * absC[1].x + Box01.Radius.z * absC[2].x;
	R01 = R0 + Box01.Radius.x;
	if (R > R01)return 0;

	//B1
	R = fabsf(D3DXVec3Dot(&Box01.GetAxisY(), &D));
	R0 = Box01.Radius.x * absC[0].z + Box01.Radius.y * absC[1].y + Box01.Radius.z * absC[2].y;
	R01 = R0 + Box01.Radius.y;
	if (R > R01)return 0;

	//B2
	R = fabsf(D3DXVec3Dot(&Box01.GetAxisZ(), &D));
	R0 = Box01.Radius.x * absC[0].z + Box01.Radius.y * absC[1].z + Box01.Radius.z * absC[2].z;
	R01 = R0 + Box01.Radius.z;
	if (R > R01)return 0;

	//A0xB0
	R = fabsf(AD.z * C[1].x - AD.y * C[2].x);
	R0 = Box01.Radius.y * absC[2].x + Box01.Radius.z * absC[1].x;
	R1 = Box01.Radius.y * absC[0].z + Box01.Radius.z * absC[0].y;
	R01 = R0 + R1;
	if (R > R01)return 0;

	//A0xB1
	R = fabsf(AD.z * C[1].y - AD.y * C[2].y);
	R0 = Box01.Radius.y * absC[2].y + Box01.Radius.z * absC[1].y;
	R1 = Box01.Radius.x * absC[0].z + Box01.Radius.z * absC[0].x;
	R01 = R0 + R1;
	if (R > R01)return 0;

	//A0xB2
	R = fabs(AD.z * C[1].z - AD.y * C[2].z);
	R0 = Box01.Radius.y * absC[2].z + Box01.Radius.z * absC[1].y;
	R1 = Box01.Radius.x * absC[0].y + Box01.Radius.y * absC[0].x;
	R01 = R0 + R1;
	if (R > R01)return 0;

	//A1xB0
	R = fabs(AD.x * C[2].x - AD.x * C[0].x);
	R0 = Box01.Radius.x * absC[2].x + Box01.Radius.z * absC[0].x;
	R1 = Box01.Radius.y * absC[1].z + Box01.Radius.z * absC[1].y;
	R01 = R0 + R1;
	if (R > R01)return 0;

	//A1xB1
	R = fabs(AD.x * C[2].y - AD.z * C[0].y);
	R0 = Box01.Radius.x * absC[2].y + Box01.Radius.z * absC[0].y;
	R1 = Box01.Radius.x * absC[1].z + Box01.Radius.z * absC[1].x;
	R01 = R0 + R1;
	if (R > R01)return 0;

	//A1xB2
	R = fabsf(AD.x * C[2].z - AD.z * C[0].z);
	R0 = Box01.Radius.x * absC[2].z + Box01.Radius.z * absC[0].z;
	R1 = Box01.Radius.x * absC[1].y + Box01.Radius.y * absC[1].x;
	R01 = R0 + R1;
	if (R > R01)return 0;

	//A2xB0
	R =  fabsf(AD.y * C[0].x - AD.x * C[1].x);
	R0 = Box01.Radius.x * absC[1].x + Box01.Radius.y * absC[0].x;
	R1 = Box01.Radius.y * absC[2].z + Box01.Radius.z * absC[2].y;
	R01 = R0 + R1;
	if (R > R01)return 0;

	//A2xB1
	R = fabsf(AD.y * C[0].y - AD.x * C[1].y);
	R0 = Box01.Radius.x * absC[1].y + Box01.Radius.y * absC[0].y;
	R1 = Box01.Radius.x * absC[2].z + Box01.Radius.z * absC[2].x;
	R01 = R0 + R1;
	if (R > R01)return 0;

	//A2xB2
	R = fabsf(AD.y * C[0].z - AD.x * C[1].z);
	R0 = Box01.Radius.x * absC[1].z + Box01.Radius.y * absC[0].z;
	R1 = Box01.Radius.x * absC[2].y + Box01.Radius.y * absC[2].x;
	R01 = R0 + R1;
	if (R > R01)return 0;

	return 1;

}
