#include "DXUT.h"
#include "CPlayer.h"
float Score;

CPlayer::CPlayer()
{

}


CPlayer::~CPlayer()
{
	 
}

void CPlayer::Init()
{
	Score = 0;
	this->AddComponent<CRenderer>();

	this->GetComponent<CRenderer>()->SetTexture(IMAGE["PLAYER"]);

	this->AddComponent<CRigidBody>();

	this->GetComponent<CRigidBody>()->SetIsKinematic(FALSE);

	this->AddComponent<CBoxCollider>();

	this->GetComponent<CBoxCollider>()->SetSize(Vector2(90,90));

	this->GetComponent<CBoxCollider>()->SetOffSet(Vector2(0.f, 10.f));

	this->Transform->SetPosition(Vector2(WinSize.x / 2.f, 100));

	this->m_fMoveSpeed = 700.f;
}
void CPlayer::Update()
{
	Score += DeltaTime;
	if (INPUT.KeyPress('A'))
	{
		m_pObject->Transform->Translation(-m_fMoveSpeed *  DeltaTime, 0);
	}
	if (INPUT.KeyPress('D'))
	{
		m_pObject->Transform->Translation(m_fMoveSpeed * DeltaTime, 0);
	}
	if (INPUT.KeyDown('W') || INPUT.KeyDown(VK_SPACE))
	{
		this->GetComponent<CRigidBody>()->SetVelocitiy(Vector2(0, -1800));
		this->GetComponent<CRigidBody>()->SetIsKinematic(FALSE);
	}

	//this->GetComponent<CBoxCollider>()->SetCollisionBox(this->GetComponent<CRenderer>()->GetRect());
}

void CPlayer::Render()
{

}

void CPlayer::OnCollisionEnter(CObject * _pObject)
{
	if (_pObject->GetObjectTag() == ObjectTag::Floor)
	{
		this->GetComponent<CRigidBody>()->SetIsKinematic(TRUE);
		this->GetComponent<CRigidBody>()->SetVelocitiy(Vector2(0.f, 0.f));
	}
	if (_pObject->GetObjectTag() == Tag::Fall)
	{
		SCENE.ChangeScene("S_ENDING");
	}
}

void CPlayer::OnCollisionStay(CObject * _pObject)
{
		if (_pObject->GetObjectTag() == ObjectTag::Floor)
		{
			//this->GetComponent<CRigidBody>()->SetIsKinematic(TRUE);
		//	this->GetComponent<CRigidBody>()->SetVelocitiy(Vector2(0.f, 0.f));
		}

}

void CPlayer::OnCollisionExit(CObject * _pObject)
{

	if (_pObject->GetObjectTag() == ObjectTag::Floor)
	{
		//this->GetComponent<CRigidBody>()->SetIsKinematic(FALSE);
	}
}


void CPlayer::Release()
{
}

