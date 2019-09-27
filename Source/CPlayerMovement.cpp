#include "DXUT.h"
#include "CPlayerMovement.h"


CPlayerMovement::CPlayerMovement()
{
	this->m_fDistanceFromCamera = 10.f;
	this->m_fSensitivity = 15.f;
	this->m_fMoveSpeed = 5.f;

	m_Status = PlayerStatus::IDLE;
}


CPlayerMovement::~CPlayerMovement()
{
}

void CPlayerMovement::SetAnime(PlayerStatus _Staus)
{
	if (this->m_Status != _Staus)
	{
		m_Status = _Staus;
		switch (_Staus)
		{
		case PlayerStatus::IDLE:
			this->GetComponent<CAnimation3D>()->SetHandleAnimator("IDLE");
			break;
		case PlayerStatus::RUN:
			this->GetComponent<CAnimation3D>()->SetHandleAnimator("RUN");
			break;
		case PlayerStatus::SWINGA:
			this->GetComponent<CAnimation3D>()->SetHandleAnimator("SWINGA");
			break;
		case PlayerStatus::SWINGB:
			this->GetComponent<CAnimation3D>()->SetHandleAnimator("SWINGB");
			break;
		case PlayerStatus::SWINGC:
			this->GetComponent<CAnimation3D>()->SetHandleAnimator("SWINGC");
			break;
		case PlayerStatus::DASH:
			this->GetComponent<CAnimation3D>()->SetHandleAnimator("DASH");
			break;
		}
	}
}

void CPlayerMovement::Init()
{
	this->GetComponent<CRigidBody3D>()->SetGravityScale(0.f);
	this->Transform->SetScale(Vector3(1, 1, -1));
	m_fMoveSpeed = 5.f;
	
	this->Transform->SetPosition(Vector3(0, 50, 0));

	CAMERA.SetRotation(Vector3(-15, 0, 0));

	m_vAxis[Axis::Foward]	= Vector3(0, 0, 1);
	m_vAxis[Axis::Backward] = Vector3(0, 0, -1);
	m_vAxis[Axis::Right]	= Vector3(1, 0, 0);
	m_vAxis[Axis::Left]		= Vector3(-1, 0, 0);
	m_vAxis[Axis::Up]		= Vector3(0, 1, 0);
	m_vAxis[Axis::Down]		= Vector3(0, -1, 0);


	m_vCamDir = Vector3(Transform->GetPosition().x, Transform->GetPosition().y + 4.f, Transform->GetPosition().z -6.f) - this->Transform->GetPosition();
	D3DXVec3Normalize(&m_vCamDir, &m_vCamDir);
	CAMERA.SetPos(m_vCamDir * m_fDistanceFromCamera);

}

void CPlayerMovement::Update()
{
	Vector2 NormalDelta = INPUT.m_vDeltaCursor;
	this->Transform->Rotate(0, NormalDelta.x * FixedDeltaTime * this->m_fSensitivity/10.f, 0);
	this->m_fCamrotX += NormalDelta.y * FixedDeltaTime * this->m_fSensitivity / 10.f;

	Vector3 vPlayerPos = this->Transform->GetPosition();

	Matrix CamRotX;
	Matrix CamRotY;

	D3DXMatrixRotationY(&CamRotY, D3DXToRadian(this->Transform->GetRotation().y));
	D3DXMatrixRotationX(&CamRotX, D3DXToRadian(this->m_fCamrotX));
	Matrix CamRot = CamRotX * CamRotY;

	D3DXVec3TransformNormal(&m_vAxis[Axis::Foward],		&Vector3(0, 0, 1), &CamRot);
	D3DXVec3TransformNormal(&m_vAxis[Axis::Backward],	&Vector3(0, 0,- 1), &CamRot);
	D3DXVec3TransformNormal(&m_vAxis[Axis::Right],		&Vector3(1, 0, 0), &CamRot);
	D3DXVec3TransformNormal(&m_vAxis[Axis::Left],		&Vector3(-1, 0, 0), &CamRot);
	D3DXVec3TransformNormal(&m_vAxis[Axis::Up],			&Vector3(0, 1, 0), &CamRot);
	D3DXVec3TransformNormal(&m_vAxis[Axis::Down],		&Vector3(0, -1, 0), &CamRot);


	Quaternion CurQ;
	D3DXQuaternionRotationMatrix(&CurQ, &CamRot);

	D3DXQuaternionSlerp(&CurQ, &m_OldQt, &CurQ, FixedDeltaTime  * 12.f);

	m_OldQt = CurQ;

	D3DXMatrixRotationQuaternion(&CamRot, &CurQ);


	Vector3 vNowCamDir;
	D3DXVec3TransformCoord(&vNowCamDir, &m_vCamDir, &CamRot);
	D3DXVec3Normalize(&vNowCamDir, &vNowCamDir);


	auto Terrain = OBJECT.FindObjectWithName("Map")->GetComponent<CTerrain>();
	this->Transform->SetPosition(Vector3(
		this->Transform->GetPosition().x ,                                                                                                                                                                                     
		Terrain->GetHeight(this->Transform->GetPosition().x,this->Transform->GetPosition().z),
		this->Transform->GetPosition().z));

	CAMERA.SetPos(this->Transform->GetPosition() + (vNowCamDir * 10));
	CAMERA.SetLookAt(this->Transform->GetPosition());

	if (CAMERA.GetPos().y -1 < Terrain->GetHeight(CAMERA.GetPos().x, CAMERA.GetPos().z))
	{
		CAMERA.SetPos(Vector3(CAMERA.GetPos().x, Terrain->GetHeight(CAMERA.GetPos().x, CAMERA.GetPos().z)+1, CAMERA.GetPos().z));
		CurQ = m_OldQt;
 	}
	
	bool bMove = false;
	bool bAttack = false;

	if (this->m_Status != PlayerStatus::SWINGA &&
		this->m_Status != PlayerStatus::SWINGB &&
		this->m_Status != PlayerStatus::SWINGC &&
		this->m_Status != PlayerStatus::DASH)
	{
		if (INPUT.KeyPress('A'))
		{
			this->Transform->Translation(this->m_vAxis[Axis::Left] * FixedDeltaTime * m_fMoveSpeed);
			this->Transform->SetScale(Vector3(1, 1, -1));
			bMove = true;
		}

		if (INPUT.KeyPress('D'))
		{
			this->Transform->Translation(this->m_vAxis[Axis::Right] * FixedDeltaTime * m_fMoveSpeed);
			this->Transform->SetScale(Vector3(1, 1, -1));

			bMove = true;
		}

		if (INPUT.KeyPress('W'))
		{
			this->Transform->Translation(m_vAxis[Axis::Foward] * m_fMoveSpeed * FixedDeltaTime);
			this->Transform->SetScale(Vector3(1, 1, -1));

			bMove = true;
		}

		if (INPUT.KeyPress('S'))
		{
			this->Transform->Translation(m_vAxis[Axis::Backward] * m_fMoveSpeed * FixedDeltaTime);
			this->Transform->SetScale(Vector3(1, 1, 1));

			bMove = true;
		}
	}


	if (bMove) {
		if (INPUT.KeyDown(VK_SPACE))
		{
			SetAnime(PlayerStatus::DASH);
			this->GetComponent<CRigidBody3D>()->AddForce(this->m_vAxis[Axis::Foward] *80);
		}
		else SetAnime(PlayerStatus::RUN);
	}
	else
	{
		if (m_Status == PlayerStatus::DASH)
		{
			if (this->GetComponent<CAnimation3D>()->GetHandleAnimator()->GetPlayCount() == 1)
			{
				SetAnime(PlayerStatus::IDLE);
			}

		}
		else if (m_Status == PlayerStatus::IDLE)
		{
			if (INPUT.KeyDown(VK_SPACE))
			{
				SetAnime(PlayerStatus::DASH);
				this->GetComponent<CRigidBody3D>()->AddForce(this->m_vAxis[Axis::Foward] * 80);
			}

			if (INPUT.KeyDown(VK_LBUTTON))
			{
				SetAnime(PlayerStatus::SWINGA);
			}
		}
		else	if (m_Status == PlayerStatus::SWINGA)
		{
				if (INPUT.KeyDown(VK_LBUTTON))
				{
					m_bAttacked = true;
				}
			if (this->GetComponent<CAnimation3D>()->GetHandleAnimator()->GetPlayCount() == 1)
			{
				if (m_bAttacked == true)
				{
					m_bAttacked = false;
					SetAnime(PlayerStatus::SWINGB);
				}
				else SetAnime(PlayerStatus::IDLE);
			}
		}
		else	if (m_Status == PlayerStatus::SWINGB)
		{
				if (INPUT.KeyDown(VK_LBUTTON))
				{
					m_bAttacked = true;
				}
			if (this->GetComponent<CAnimation3D>()->GetHandleAnimator()->GetPlayCount() == 1)
			{
				if (m_bAttacked == true)
				{
					m_bAttacked = false;
					SetAnime(PlayerStatus::SWINGC);
				}
				else SetAnime(PlayerStatus::IDLE);
			}
		}
		else	if (m_Status == PlayerStatus::SWINGC)
		{
			if (this->GetComponent<CAnimation3D>()->GetHandleAnimator()->GetPlayCount() == 1)
			{
				m_bAttacked == false;
				SetAnime(PlayerStatus::IDLE);
			}
		}
		else
		{
				SetAnime(PlayerStatus::IDLE);
		}
	}
}

void CPlayerMovement::Render()
{
}

void CPlayerMovement::Release()
{
}

void CPlayerMovement::OnCollisionEnter(CObject * _pObject)
{
}

void CPlayerMovement::OnCollisionStay(CObject * _pObject)
{
}

void CPlayerMovement::OnCollisionExit(CObject * _pObject)
{
}
