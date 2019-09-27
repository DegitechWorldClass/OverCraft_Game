#include "DXUT.h"
#include "CRay.h"


CRay::CRay()
{
}


CRay::~CRay()
{
}

void CRay::TransformRay()
{
	//카메라 -> 월드
	Matrix matViewInverse;
	D3DXMatrixInverse(&matViewInverse, NULL, &CAMERA.m_matView);

	D3DXVec3TransformCoord(&m_vPos, &m_vPos, &matViewInverse);

	D3DXVec3TransformNormal(&m_vDir, &m_vDir, &matViewInverse);

	D3DXVec3Normalize(&m_vDir, &m_vDir);
}
