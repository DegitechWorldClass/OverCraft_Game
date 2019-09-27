#include "DXUT.h"
#include "CAnimation2D.h"


CAnimation2D::CAnimation2D()
{
}


CAnimation2D::~CAnimation2D()
{
}

void CAnimation2D::SetHandleAnimator(const string & _Key)
{
	auto find = m_Animators.find(_Key);

	if (find != m_Animators.end())
	{
		m_pHandleAnimator = find->second;
		m_pHandleAnimator->m_iCurFrame = 0;
		m_pHandleAnimator = m_Animators[_Key];
	}
}

void CAnimation2D::AddAnimator(const string & _Key, const string & _resKey, float _fDelay, bool _bLoop)
{
	auto find = m_Animators.find(_Key);

	if (find == m_Animators.end())
	{
		CAnimator2D * pAnimator = new CAnimator2D();
		pAnimator->Init(_resKey, _fDelay, _bLoop);

		m_Animators.insert(make_pair(_Key, pAnimator));


	}

}

void CAnimation2D::Init()
{
}

void CAnimation2D::Update()
{
	if (m_pHandleAnimator)
	{
		m_pHandleAnimator->Update();
		auto Renderer = m_pObject->GetComponent<CSpriteRenderer>();
		if (Renderer)
			Renderer->SetTexture(m_pHandleAnimator->GetFrameTexture());
	}
}

void CAnimation2D::Render()
{
	if (m_pHandleAnimator)
	{
		m_pHandleAnimator->Render();
	}
}

void CAnimation2D::Release()
{
	for (auto& iter : m_Animators)
	{
		iter.second->Release();
		SAFE_DELETE(iter.second);
	}
	m_Animators.clear();
}

void CAnimation2D::OnCollisionEnter(CObject * _pObject)
{
}

void CAnimation2D::OnCollisionStay(CObject * _pObject)
{
}

void CAnimation2D::OnCollisionExit(CObject * _pObject)
{
}
