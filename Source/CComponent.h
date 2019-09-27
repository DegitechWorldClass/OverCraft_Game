#pragma once
#include "CObject.h"

class CTransform;
class CObject;
class CComponent abstract
{
	friend class CObject;
	friend class CObjectManager;

public:
	CComponent();
	virtual ~CComponent();

private:
	virtual void Init()		PURE;
	virtual void Update()	PURE;
	virtual void Render()	PURE;
	virtual void Release()	PURE;
	virtual void OnCollisionEnter(CObject * _pObject)	PURE;
	virtual void OnCollisionStay(CObject * _pObject)	PURE;
	virtual void OnCollisionExit(CObject * _pObject)	PURE;



private:
	bool m_bIsEnable;

public:
	bool GetIsEnable()
	{
		return m_bIsEnable;
	}
	void SetIsEnable(bool _bIsEnable)
	{
		m_bIsEnable = _bIsEnable;
	}
	//list<CComponent *>& GetComponents() 
	//{ 
	//	return this->m_pObject->GetComponents(); 
	//}

	template <typename T>
	T*  GetComponent()
	{
		return this->m_pObject->GetComponent<T>();
	}

	template <typename T>
	T* AddComponent()
	{
		return this->m_pObject->AddComponent<T>();
	}

	template <typename T>
	T* GetComponentInParent()
	{
		return m_pObject->GetComponentInParent<T>();
	}

	template <typename T>
	T* GetComponentInChild()
	{
		return m_pObject->GetComponentInChild<T>();
	}

	template <typename T>
	list<T*> GetComponentsInChild()
	{
		return m_pObject->GetComponentsInChild();
	}
public:
	CObject * m_pObject;
	CTransform * Transform = NULL;

};

