#include "DXUT.h"
#include "CFixelCollider.h"


void CFixelCollider::Init()
{
	this->m_reCollisionBox = Rect(0.f, 0.f, 0.f, 0.f);
}

void CFixelCollider::Update()
{
}

void CFixelCollider::Render()
{

}

void CFixelCollider::Release()
{
	m_listCollision.clear();
}

CFixelCollider::CFixelCollider(CObject * _pObject)
	: CComponent(_pObject)
{
}


CFixelCollider::~CFixelCollider()
{
}

bool CFixelCollider::CheckCollision(CTexture * _pTexture, D3DXCOLOR _Color)
{	


}
