#include "DXUT.h"
#include "CRigidBody3D.h"

#define GRAVITY 9.8f

CRigidBody3D::CRigidBody3D()
{
}


CRigidBody3D::~CRigidBody3D()
{
}

void CRigidBody3D::Init()
{
		this->m_vVelocity = Vector3(0.f, 0.f,0.f);
		this->m_bIsKinematic = false;
		this->m_fGravityScale = 1.f;
		this->m_fMass = 1.f;
}

void CRigidBody3D::Update()
{
	if (m_bMove == true)
	{
		if (m_bIsKinematic == FALSE)
		{
			m_vVelocity.y += 4800 * m_fMass * m_fGravityScale * DeltaTime;

			m_vVelocity.y *= 0.8f;
			m_vVelocity.x *= 0.8f;
			m_vVelocity.z *= 0.8f;
		}
		this->Transform->Translation(m_vVelocity * DeltaTime);
	}
}

void CRigidBody3D::Render()
{
}

void CRigidBody3D::Release()
{
}

void CRigidBody3D::OnCollisionEnter(CObject * _pObject)
{
}

void CRigidBody3D::OnCollisionStay(CObject * _pObject)
{
}

void CRigidBody3D::OnCollisionExit(CObject * _pObject)
{
}
