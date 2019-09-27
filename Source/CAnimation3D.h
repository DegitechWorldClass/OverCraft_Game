#pragma once
#include "CComponent.h"
#include "CAnimator3D.h"
class CTimer;
class CAnimation3D : public CComponent
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
	CAnimation3D();
	~CAnimation3D();

private:
	map<string, CAnimator3D *> m_Animators;
	CAnimator3D * m_pHandleAnimator = nullptr;

public:
	void AddAnimator(const string& _Key, const string& _resKey, float _fDelay, bool _bLoop);
	string GetHandleAnimatorKey() { return m_pHandleAnimator->GetKey(); }

	CAnimator3D * GetHandleAnimator() { return m_pHandleAnimator; }
	CAnimator3D * GetAnimator(CRString _Key);


	void	SetHandleAnimator(const string& _Key);
};

