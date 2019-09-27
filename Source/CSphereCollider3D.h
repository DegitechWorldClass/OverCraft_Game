#pragma once
#include "CCollider3D.h"


class CSphereCollider3D :
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
	CSphereCollider3D();
	~CSphereCollider3D();
};

