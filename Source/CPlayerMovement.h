#pragma once

enum PlayerStatus
{
	IDLE,
	RUN,
	SWINGA,
	SWINGB,
	SWINGC,
	DASH
};
enum Axis
{
	Foward,
	Backward,
	Left,
	Right,
	Up,
	Down,
	Last
};

class CPlayerMovement : public CComponent
{
	friend class CObjectManager;
	friend class CObject;
public:
	Vector3 m_vAxis[Axis::Last];
	PlayerStatus m_Status;
private:
	virtual void Init() override;
	virtual void Update() override;
	virtual void Render() override;
	virtual void Release() override;
	virtual void OnCollisionEnter(CObject * _pObject)	override;
	virtual void OnCollisionStay(CObject * _pObject)	override;
	virtual void OnCollisionExit(CObject * _pObject)	override;
public:
	CPlayerMovement();
	~CPlayerMovement();

private:
	float m_fCamrotX = 0.f;
	float m_fMoveSpeed;
	Vector3 m_vCamDir;
	Quaternion m_OldQt;
	float m_bAttacked = false;
	
	void SetAnime(PlayerStatus _Staus);

	float m_fSensitivity;		 // 마우스 감도
	float m_fDistanceFromCamera; // 카메라와의 거리
};

