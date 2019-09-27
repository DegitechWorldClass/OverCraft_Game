#pragma once
#include "CComponent.h"
class CFixelCollider :
	public CComponent
{
	friend class CObjectManager;
	friend class CObject;
private:
	virtual void Init() override;
	virtual void Update() override;
	virtual void Render() override;
	virtual void Release() override;
public:
	CFixelCollider(CObject * _pObject);
	~CFixelCollider();


private:
	set < CObject *> m_listCollision;

	//충돌처리에 사용되는 좌표가 절대적인 사각형
	Rect m_reCollisionBox;




	CTexture * m_pTexture = NULL;

public:
	CTexture * GetTexture()
	{ 
		return m_pTexture; 
	}
	void SetTexture(CTexture * _pTexture) 
	{ 
		m_pTexture = _pTexture; 
	}
	
	Rect GetCollisionBox()
	{
		return m_reCollisionBox;
	}
	void SetCollisionBox(const Rect& _reCollisionBox)
	{
		m_reCollisionBox = _reCollisionBox;
	}

	bool CheckCollision( CTexture * _pTexture,D3DXCOLOR _Color);
};

