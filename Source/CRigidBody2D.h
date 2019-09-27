#pragma once
#include "CComponent.h"

class CRigidBody2D
	: public CComponent
{
	friend class CObjectManager;
	friend class CObject;
private:
	virtual void Init() override;
	virtual void Update() override;
	virtual void Render() override;
	virtual void Release() override;
	virtual void OnCollisionEnter(CObject * _pObject)	override;
	virtual void OnCollisionStay(CObject * _pObject)	override;
	virtual void OnCollisionExit(CObject * _pObject)	override;

public:
	CRigidBody2D();
	~CRigidBody2D();

private:
	Vector2 m_vVelocity;
	bool	m_bIsKinematic;
	float	m_fGravityScale;
	float	m_fMass;
	bool	m_bMove = true;
public:
	Vector2 GetVelocity()
	{
		return m_vVelocity;
	}
	void	SetVelocitiy(const Vector2& _vVelocitiy)
	{
		m_vVelocity = _vVelocitiy;
	}

	bool	GetIsKinematic()
	{
		return m_bIsKinematic;
	}
	void	SetIsKinematic(bool _bIsKinematic)
	{
		m_bIsKinematic = _bIsKinematic;

	}

	float	GetGravityScale()
	{
		return m_fGravityScale;
	}
	void	SetGravityScale(float _bGravityScale)
	{
		m_fGravityScale = _bGravityScale;

	}

	void	AddForce(Vector2 _vVelocity)
	{
		m_vVelocity += _vVelocity;
	}

	void	AddForce(float _fX, float _fY)
	{
		m_vVelocity += Vector2(_fX, _fY);
	}

	void	SetMass(float _fMass)
	{
		m_fMass = _fMass;
	}

	float	GetMass()
	{
		return m_fMass;
	}


};

