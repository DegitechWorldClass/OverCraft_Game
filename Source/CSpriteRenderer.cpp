#include "DXUT.h"
#include "CSpriteRenderer.h"


CSpriteRenderer::CSpriteRenderer()
{
	OBJECT.RegisterRenderer2D(this);
}


CSpriteRenderer::~CSpriteRenderer()
{
	OBJECT.UnRegisterRenderer2D(this);
}

void CSpriteRenderer::Init()
{
	this->m_pTexture = nullptr;
	this->m_fWidth = 0.f;
	this->m_fHeight = 0.f;
	this->m_Color = D3DCOLOR_ARGB(255, 255, 255, 255);
	this->m_rRect = Rect(0, 0, 0, 0);
	this->m_bIsInterFace = TRUE;
}

void CSpriteRenderer::Update()
{
}

void CSpriteRenderer::Render()
{
	if (NULL == m_pTexture)
	{
		return;
	}
	Matrix matWorld;
	matWorld = IMAGE.GetWorldMatrix(this->m_pObject->Transform);
	auto handle = this->m_pObject;
	while (handle->m_pParent != nullptr)
	{
		handle = handle->m_pParent;
		matWorld *= IMAGE.GetWorldMatrix(handle->Transform);
	}

	IMAGE.Render(
		m_pTexture,
		matWorld,
		this->m_rRect,
		this->m_Color);
	//m_pTexture->Render(
	//	this->m_pObject->Transform->GetPosition(),
	//	this->m_pObject->Transform->GetScale(),
	//	this->m_pObject->Transform->GetRotation(),
	//	this->m_rRect,
	//	this->m_Color);
}

void CSpriteRenderer::Release()
{
}

void CSpriteRenderer::OnCollisionEnter(CObject * _pObject)
{
}

void CSpriteRenderer::OnCollisionStay(CObject * _pObject)
{
}

void CSpriteRenderer::OnCollisionExit(CObject * _pObject)
{
}
