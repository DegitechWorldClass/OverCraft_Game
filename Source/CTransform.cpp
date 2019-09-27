#include "DXUT.h"
#include "CTransform.h"


CTransform::CTransform()
{
}


CTransform::~CTransform()
{
}

void CTransform::Translation(Vector2 _vPos)
{
	this->m_vPosition += Vector3(_vPos);
}

void CTransform::Translation(float _fX, float _fY)
{
	this->m_vPosition += Vector3(_fX, _fY,0.f);
}

void CTransform::Translation(Vector3 _vPos)
{
	this->m_vPosition += Vector3(_vPos);
}

void CTransform::Translation(float _fX, float _fY,float _fZ)
{
	this->m_vPosition += Vector3(_fX, _fY, _fZ);
}

void CTransform::Rotate(Vector3 _vRot)
{
	m_vRotation += _vRot;
}

void CTransform::Rotate(float _fX, float _fY, float _fZ)
{
	m_vRotation += Vector3(_fX, _fY, _fZ);
}




void CTransform::Init()
{
	this->m_vPosition = Vector3(0.f, 0.f, 0.f);
	this->m_vScale = Vector3(1.f, 1.f,1.f);
	this->m_vRotation = Vector3(0.f,0.f,0.f);
}

void CTransform::Update()
{
}

void CTransform::Render()
{
}

void CTransform::Release()
{
}

void CTransform::OnCollisionEnter(CObject * _pObject)
{
}

void CTransform::OnCollisionStay(CObject * _pObject)
{
}

void CTransform::OnCollisionExit(CObject * _pObject)
{
}
