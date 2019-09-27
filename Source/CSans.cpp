#include "DXUT.h"
#include "CSans.h"


CSans::CSans()
{
}


CSans::~CSans()
{
}

void CSans::Init()
{
	this->AddComponent<CRenderer>();
	this->AddComponent<CAnimation>();
	this->GetComponent<CAnimation>()->AddAnimator("SANS", "MAIN_SANS", 0.05f, true);
	this->m_pObject->m_iDepth = 5;
	this->GetComponent<CAnimation>()->SetHandleAnimator("SANS");

	m_iMoveDir = GetRandomNum(0, 100) < 50 ? -1 : 1;
	m_iDir = GetRandomNum(0, 100) < 50 ? -1 : 1;

	if (m_iMoveDir == -1) // Y이동일때
	{
		this->Transform->SetPosition(Vector2(GetRandomNum(100.f,WinSize.x/2.f), WinSize.y / 2.f + (WinSize.y / 2.f + 200) * (-m_iDir)));
	}
	else if (m_iMoveDir == 1)
	{
		this->Transform->SetPosition(Vector2(WinSize.x / 2.f + (WinSize.x / 2.f + 200) * (-m_iDir), GetRandomNum(100.f, WinSize.y / 2.f)));
	}
	m_fSpeed = GetRandomNum(1500, 3000);
}

void CSans::Update()
{
	if (m_iMoveDir == -1) // Y이동일때
	{
		this->Transform->Translation(Vector2(0.f,m_fSpeed * m_iDir* DeltaTime));
	}
	else if (m_iMoveDir == 1)
	{
		this->Transform->Translation(Vector2(m_fSpeed * m_iDir * DeltaTime,0.f));
	}

	if (m_fTime > 20.f)
	{
		this->m_pObject->Destroy();
	}
	else m_fTime += DeltaTime;
}

void CSans::Render()
{
}

void CSans::Release()
{
}

void CSans::OnCollisionEnter(CObject * _pObject)
{
}

void CSans::OnCollisionStay(CObject * _pObject)
{
}

void CSans::OnCollisionExit(CObject * _pObject)
{
}
