#pragma once
#include "CComponent.h"
#include "CAnimator2D.h"
class CAnimation2D : public CComponent
{
public:
	CAnimation2D();
	~CAnimation2D();
	friend class CObjectManager;
	friend class CObject;
private:
private:
	virtual void Init() override;
	virtual void Update() override;
	virtual void Render() override;
	virtual void Release() override;
	virtual void OnCollisionEnter(CObject * _pObject)	override;
	virtual void OnCollisionStay(CObject * _pObject)	override;
	virtual void OnCollisionExit(CObject * _pObject)	override;

private:
	map<string, CAnimator2D *> m_Animators;
	CAnimator2D * m_pHandleAnimator = nullptr;

public:
	void AddAnimator(const string& _Key, const string& _resKey, float _fDelay, bool _bLoop);
	string GetHandleAnimatorKey() { return m_pHandleAnimator->GetKey(); }

	CAnimator2D * GetHandleAnimator() { return m_pHandleAnimator; }
	CAnimator2D * GetAnimator(CRString _Key);


	void	SetHandleAnimator(const string& _Key);
};

