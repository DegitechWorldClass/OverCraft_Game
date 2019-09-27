#pragma once
#include "CComponent.h"

enum class PLAYER_STATUS
{
	Run = 0,
	Jump,
	DoubleJump,
	Slide,
};
class CPlayer :
	public CComponent
{
	friend class CObjectManager;
	friend class CObject; 
private:
	virtual void Init()									override;
	virtual void Update()								override;
	virtual void Render()								override;
	virtual void Release()								override;
	virtual void OnCollisionEnter(CObject * _pObject)	override;
	virtual void OnCollisionStay(CObject * _pObject)	override;
	virtual void OnCollisionExit(CObject * _pObject)	override;


public:
	CPlayer();
	~CPlayer();

private:
	PLAYER_STATUS m_Status;

	float m_fMoveSpeed;
};

