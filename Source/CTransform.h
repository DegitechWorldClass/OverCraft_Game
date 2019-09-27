#pragma once
#include "CComponent.h"
class CTransform :
	public CComponent
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
	CTransform();
	~CTransform();

private:
	Vector3 m_vPosition;
	Vector3 m_vScale;
	Vector3	m_vRotation;

public:
	Vector3 GetPosition()
	{
		return m_vPosition;
	}
	void	SetPosition(const Vector3& _vPos)
	{
		m_vPosition = _vPos;
	}

	Vector3 GetScale()
	{
		return m_vScale;
	}
	void	SetScale(const Vector3& _vScale)
	{
		m_vScale = _vScale;
	}

	Vector3	GetRotation()
	{
		return m_vRotation;
	}
	void	SetRotation(Vector3 _vRot)
	{
		m_vRotation = _vRot;
	}


public:
	void Translation(Vector2 _vPos);
	void Translation(float _fX, float _fY);
	void Translation(Vector3 _vPos);
	void Translation(float _fX, float _fY, float _fZ);
	void Rotate(Vector3 _vRot);
	void Rotate(float _fX, float _fY, float _fZ);

};

