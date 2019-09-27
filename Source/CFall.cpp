#include "DXUT.h"
#include "CFall.h"
extern float Score;
CFall::CFall()
{
}


CFall::~CFall()
{
}

void CFall::Hit()
{
	m_fCurHp--;
	
	switch((INT)m_fCurHp)
	{
	case 3:
		this->GetComponent<CRenderer>()->SetTexture(IMAGE["FALL_2"]);
		break;
	case 2:
		this->GetComponent<CRenderer>()->SetTexture(IMAGE["FALL_3"]);
		break;
	case 1:
		this->GetComponent<CRenderer>()->SetTexture(IMAGE["FALL_4"]);
		break;
	}
	if (m_fCurHp <= 0.f)
	{
		m_pObject->Destroy();
	}
}

void CFall::Init()
{
	this->AddComponent<CRenderer>();
	
	//this->AddComponent<CRigidBody>();

	this->AddComponent<CBoxCollider>();

	this->GetComponent<CRenderer>()->SetTexture(IMAGE["FALL_1"]);

	this->GetComponent<CBoxCollider>()->SetSize(this->GetComponent<CRenderer>()->GetSize());

	this->m_pObject->Transform->SetPosition(Vector2(GetRandomNum(0.F, WinSize.x),-200));

	m_fSpeed = GetRandomNum(100 + Score * 5, 300 + Score * 10);

	m_fMaxHp = 4.f;
	m_fCurHp = 4.f;
}

void CFall::Update()
{
	if (this->m_pObject->Transform->GetPosition().y  > WinSize.y+200.f)
	{
		m_pObject->Destroy();
	}
	this->Transform->Translation(Vector2(0.f, m_fSpeed * DeltaTime));
}

void CFall::Render()
{
}

void CFall::Release()
{
}

void CFall::OnCollisionEnter(CObject * _pObject)
{

}

void CFall::OnCollisionStay(CObject * _pObject)
{
	if (_pObject->GetObjectTag() == ObjectTag::Floor)
	{
		this->m_pObject->Destroy();
	}
}

void CFall::OnCollisionExit(CObject * _pObject)
{
}
