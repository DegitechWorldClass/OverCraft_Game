#pragma once
#include "CCollider3D.h"
class CBoxCollider3D :
	public CCollider3D
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
	CBoxCollider3D();
	~CBoxCollider3D();

private:
	Vector3 m_LocalMin;
	Vector3 m_LocalMax;
			
	Vector3 m_Center;

public:
	Vector3 GetLoaclMin() { return m_LocalMin; }
	Vector3 GetLoaclMax() { return m_LocalMax; }
	Vector3 GetMin() { return m_Center + m_LocalMin; }
	Vector3 GetMax() { return m_Center + m_LocalMax; }

};

