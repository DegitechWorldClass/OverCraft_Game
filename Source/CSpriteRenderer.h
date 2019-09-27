#pragma once
#include "CRenderer2D.h"

class CSpriteRenderer
	: public CRenderer2D  
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
	CSpriteRenderer();
	~CSpriteRenderer();

private:


	//렌더링 되는 영역을 담는 사각형 변수
	CTexture * m_pTexture = nullptr;
	FLOAT m_fWidth;
	FLOAT m_fHeight;
	Color m_Color;
	Rect  m_rRect;


public:



	CTexture *	GetTexture()
	{
		return m_pTexture;
	}
	void		SetTexture(CTexture * _pTexture)
	{
		m_pTexture = _pTexture;
		m_fWidth = (FLOAT)m_pTexture->GetSize().x;
		m_fHeight = (FLOAT)m_pTexture->GetSize().y;
		m_rRect = Rect(0.f, 0.f, m_fWidth, m_fHeight);
	}
	Vector2		GetSize()
	{
		return m_pTexture->GetSize();
	}
	FLOAT		GetWidth()
	{
		return m_fWidth;
	}
	FLOAT		GetHeight()
	{
		return m_fHeight;
	}

	Color		GetColor()
	{
		return m_Color;
	}
	void		SetColor(Color _Color)
	{
		m_Color = _Color;
	}

	Rect 		GetRect()
	{
		return m_rRect;
	}
	void		SetRect(const Rect& Rect)
	{
		m_rRect = Rect;
	}

	Rect		GetCenterRect()
	{
		return Rect(-m_fWidth / 2.f, -m_fHeight / 2.f, m_fWidth / 2.f, m_fHeight / 2.f);
	}
};

