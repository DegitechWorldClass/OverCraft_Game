#pragma once

#include"CCollider2D.h"
enum CollisionStatus
{
	COLS_OnEnter,
	COLS_OnStay,
	COLS_OnExit
};
enum ObjectTag;
class CBoxCollider2D :
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

private:
	Vector2 m_vSize;
	Vector2 m_vOffSet;
public:
	CBoxCollider2D();
	~CBoxCollider2D();

private:
	set < CObject *> m_listCollision;

	//좌표가 포함된 사각형
	Rect m_reCollisionRect;

public:
	Vector2 GetSize()
	{
		return m_vSize;
	}

	void SetSize(Vector2 _vSize)
	{
		m_vSize = _vSize;
	}

	Rect GetCollisionRect()
	{
		return m_reCollisionRect;
	}
	
	Vector2 GetOffSet()
	{
		return m_vOffSet;
	}
	void SetOffSet(Vector2 _vOffSet)
	{
		m_vOffSet = _vOffSet;
	}

};

