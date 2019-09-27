#include "DXUT.h"
#include "CAnimator2D.h"


CAnimator2D::CAnimator2D()
{
}


CAnimator2D::~CAnimator2D()
{
}

void CAnimator2D::Init(const string & _Key, float _fDelay, bool _bLoop)
{
	_fDelay = _fDelay;
	m_bLoop = _bLoop;
	m_bEnable = true;
	m_Textures = IMAGE.MakeVecTex(_Key);
	m_iPlayCount = 0;
	m_iCurFrame = 0;
	m_iMaxFrame = m_Textures.size() - 1;



	m_pTimer = new CTimer(_fDelay, [&]()->void
	{
		m_iCurFrame++;
		if (m_iCurFrame > m_iMaxFrame)
		{
			m_iCurFrame = 0;
			m_iPlayCount++;
			if (!m_bLoop) m_bEnable = false;
		}
	});
}

void CAnimator2D::Update()
{
	m_pTimer->Update();
}

void CAnimator2D::Render()
{
}

void CAnimator2D::Release()
{
	SAFE_DELETE(m_pTimer);
}
