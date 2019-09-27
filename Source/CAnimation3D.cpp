#include "DXUT.h"
#include "CAnimation3D.h"
CAnimation3D::CAnimation3D()
{
}

CAnimation3D::~CAnimation3D()
{
}

CAnimator3D * CAnimation3D::GetAnimator(CRString _Key)
{
	auto find = this->m_Animators.find(_Key);
	
	if (find == m_Animators.end())return nullptr;
	
	return find->second;
}

void CAnimation3D::SetHandleAnimator(const string & _Key)
{
	auto find = m_Animators.find(_Key);

	if (find != m_Animators.end())
	{
		if (m_pHandleAnimator)
		{
			if (m_pHandleAnimator != find->second)
			{
				m_pHandleAnimator->m_iCurFrame = 0;
				m_pHandleAnimator->m_iPlayCount = 0;
			}
		}
		m_pHandleAnimator = find->second;
		m_pHandleAnimator->m_bEnable = true;


		m_pHandleAnimator = m_Animators[_Key];
	}
}


void CAnimation3D::AddAnimator(const string & _Key, const string & _resKey, float _fDelay, bool _bLoop)
{
	auto find = m_Animators.find(_Key);

	if (find == m_Animators.end())
	{
		CAnimator3D * pAnimator = new CAnimator3D();
		pAnimator->Init(_resKey, _fDelay, _bLoop);
		pAnimator->m_Key = _Key;

		m_Animators.insert(make_pair(_Key, pAnimator));


	}

}

void CAnimation3D::Init()
{
}

void CAnimation3D::Update()
{
	if (m_pHandleAnimator)
	{
		m_pHandleAnimator->Update();
		auto Renderer = m_pObject->GetComponent<CMeshRenderer>();
		if (Renderer)
			Renderer->SetModel(m_pHandleAnimator->GetFrameModel());
	}
}

void CAnimation3D::Render()
{
	if (m_pHandleAnimator)
	{
		m_pHandleAnimator->Render();
	}
}

void CAnimation3D::Release()
{
	for (auto& iter : m_Animators)
	{
		iter.second->Release();
		SAFE_DELETE(iter.second);
	}
	m_Animators.clear();
}

void CAnimation3D::OnCollisionEnter(CObject * _pObject)
{
}

void CAnimation3D::OnCollisionStay(CObject * _pObject)
{
}

void CAnimation3D::OnCollisionExit(CObject * _pObject)
{
}
