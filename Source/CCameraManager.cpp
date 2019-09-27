#include "DXUT.h"
#include "CCameraManager.h"


CCameraManager::CCameraManager()
{
	m_vPos = Vector3(0, 0, -10);
	m_vLookAt= Vector3(0, 0, 0);
	m_vUp = Vector3(0, 1, 0);
	m_vRotation = Vector3(0, 0, 0);
	D3DXMatrixLookAtLH(&m_matView, &m_vPos, &m_vLookAt, &m_vUp);

	D3DXMatrixPerspectiveFovLH(&m_matProj, D3DX_PI / 4.f, 16.f / 9.f, 1.f, 50000.f);

}


CCameraManager::~CCameraManager()
{
}

void CCameraManager::RayCast(CRVector3 _vPos, CRVector3 _vDir)
{
	Vector2 vCursor = INPUT.GetMousePos();
	
	Vector3 _vTransPos;

	D3DVIEWPORT9 ViewPort;
	g_Device->GetViewport(&ViewPort);

	_vTransPos.x = (((2.0f * vCursor.x) / ViewPort.Width) - 1.0f) - m_matProj._31;
	_vTransPos.y = (((2.0f * vCursor.y) / ViewPort.Height) + 1.0f) - m_matProj._32;


	_vTransPos.x /= m_matProj._11;
	_vTransPos.y /= m_matProj._22;
	_vTransPos.z = 1.f;


	Matrix matViewInverse;
	D3DXMatrixInverse(&matViewInverse, NULL, &CAMERA.m_matView);

	//D3DXVec3TransformCoord(&m_vPos, &m_vPos, &matViewInverse);

	//D3DXVec3TransformNormal(&m_vDir, &m_vDir, &matViewInverse);

	//D3DXVec3Normalize(&m_vDir, &m_vDir);
	//CRay Ray;
	//Ray.m_vPos = Vector3(m, 0.f, 0.f);
	//Ray.m_vDir = Vector3(
	//	, 
	//	_vTransPos.y, 
	//	1.f);

	//D3DXIntersect(MODEL.FindModel("test")->GetD3DXMesh(),&Ray.m_vPos, &Ray.m_vDir,




}

void CCameraManager::Update()
{
	//DEBUG_LOG("Look: %.2f %.2f %.2f", m_vLookAt.x, m_vLookAt.y, m_vLookAt.z);
	//DEBUG_LOG("Pos : %.f %.f %.f", m_vPos.x, m_vPos.y, m_vPos.z);
	//DEBUG_LOG("Rot : %.f %.f %.f", m_vRotation.x, m_vRotation.y, m_vRotation.z);


	auto Terrain = OBJECT.FindObjectWithName("Map");
	//if(Terrain)
	//m_vPos.y = //Terrain->GetComponent<CTerrain>()->GetHeight(m_vPos.x, m_vPos.z) + 100;
	//DEBUG_LOG("%.f , %.f , %.f", m_vPos.x, m_vPos.y, m_vPos.z);
	Vector3 vViewX;
	Vector3 vViewY;
	Vector3 vView;
	Vector3 vCross;
	Matrix matRotX;
	Matrix matRotY;

	vViewX = m_vLookAt - m_vPos;
	vViewY = m_vLookAt - m_vPos;
	vView = m_vLookAt - m_vPos;

	D3DXVec3Cross(&vCross, &m_vUp, &vViewX);
	D3DXMatrixRotationAxis(&matRotX, &vCross, D3DXToRadian(m_vRotation.x));

	D3DXMatrixRotationAxis(&matRotY, &m_vUp, D3DXToRadian(m_vRotation.y));

	D3DXVec3TransformCoord(&vView, &vView, &(matRotX * matRotY));

	Vector3 RotateLookAt = m_vPos + vView;
	

	D3DXMatrixLookAtLH(&m_matView, &m_vPos, &RotateLookAt, &m_vUp);
	D3DXMatrixPerspectiveFovLH(&m_matProj, D3DX_PI / 4.f, 16.f / 9.f, 1.f, 500000.F);
}

void CCameraManager::SetTransform()
{
	g_Device->SetTransform(D3DTS_PROJECTION, &m_matProj);
	g_Device->SetTransform(D3DTS_VIEW, &m_matView);
}
