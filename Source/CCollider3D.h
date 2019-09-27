#pragma once
#include "CComponent.h"
class CCollider3D :
	public CComponent
{
	friend class CObjectManager;
	friend class CObject;
private:
	virtual void Init() PURE;
	virtual void Update() PURE;
	virtual void Render() PURE;
	virtual void Release() PURE;
	virtual void OnCollisionEnter(CObject * _pObject)	PURE;
	virtual void OnCollisionStay(CObject * _pObject)	PURE;
	virtual void OnCollisionExit(CObject * _pObject)	PURE;
public:
	CCollider3D();
	virtual ~CCollider3D();
};

