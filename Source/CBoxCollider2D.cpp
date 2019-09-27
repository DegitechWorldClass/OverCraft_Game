#include "DXUT.h"
#include "CBoxCollider2D.h"


CBoxCollider2D::CBoxCollider2D()
{
}


CBoxCollider2D::~CBoxCollider2D()
{
}

void CBoxCollider2D::Init()
{
	this->m_reCollisionRect = Rect(0.f, 0.f, 0.f, 0.f);
	this->m_vOffSet = Vector2(0.f, 0.f);
	this->m_vSize = Vector2(0.f, 0.f);
}

void CBoxCollider2D::Update()
{

	auto Renderer = m_pObject->GetComponent<CRenderer2D>();
	
	this->m_reCollisionRect = Rect(
		this->m_pObject->Transform->GetPosition().x - m_vSize.x/2.f  + m_vOffSet.x,
		this->m_pObject->Transform->GetPosition().y - m_vSize.y/2.f + m_vOffSet.y,
		this->m_pObject->Transform->GetPosition().x + m_vSize.x/2.f + m_vOffSet.x,
		this->m_pObject->Transform->GetPosition().y + m_vSize.y/2.f + m_vOffSet.y);

	//this->m_reCollisionRect.Left *= 1.f + (Transform->GetScale().x - 1.f) / 2.f;
	//this->m_reCollisionRect.Top *= 1.f + (Transform->GetScale().y - 1.f) / 2.f;
	//this->m_reCollisionRect.Right *= 1.f + (Transform->GetScale().x - 1.f) / 2.f;
	//this->m_reCollisionRect.Bottom *= 1.f + (Transform->GetScale().y - 1.f) / 2.f;
}

void CBoxCollider2D::Render()
{
	Rect re = m_reCollisionRect;

	//IMAGE.RenderLine(re.GetLT(), re.GetRT(), 2, D3DCOLOR_ARGB(255, 255, 255, 2), m_pObject->Transform->GetRotation(), this->m_pObject->Transform->GetPosition());
	//IMAGE.RenderLine(re.GetRT(), re.GetRB(), 2, D3DCOLOR_ARGB(255, 255, 255, 2), m_pObject->Transform->GetRotation(), this->m_pObject->Transform->GetPosition());
	//IMAGE.RenderLine(re.GetLB(), re.GetLT(), 2, D3DCOLOR_ARGB(255, 255, 255, 2), m_pObject->Transform->GetRotation(), this->m_pObject->Transform->GetPosition());
	//IMAGE.RenderLine(re.GetRB(), re.GetLB(), 2, D3DCOLOR_ARGB(255, 255, 255, 2), m_pObject->Transform->GetRotation(), this->m_pObject->Transform->GetPosition());

}

void CBoxCollider2D::Release()
{
	m_listCollision.clear();
}

void CBoxCollider2D::OnCollisionEnter(CObject * _pObject)
{
}

void CBoxCollider2D::OnCollisionStay(CObject * _pObject)
{
}

void CBoxCollider2D::OnCollisionExit(CObject * _pObject)
{
}

