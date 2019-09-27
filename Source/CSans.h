#pragma once
#include "CComponent.h"
class CSans :
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
	CSans();
	~CSans();

	int m_iDir;
	int m_iMoveDir;
	float m_fTime = 0.f;

	float m_fSpeed;
};

