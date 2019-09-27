#include "DXUT.h"
#include "CAnimator3D.h"


CAnimator3D::CAnimator3D()
{
}


CAnimator3D::~CAnimator3D()
{
}


void CAnimator3D::Init(const string & _Key, float _fDelay, bool _bLoop)
{
	m_fDelay = _fDelay;
	m_bLoop = _bLoop;
	m_bEnable = true;
	m_Models = MODEL.MakeVecModel(_Key);
	m_iPlayCount = 0;
	m_iCurFrame = 0;
	m_iMaxFrame = m_Models.size() - 1;
	


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

void CAnimator3D::Update()
{
	m_pTimer->Update();
}

void CAnimator3D::Render()
{
}

void CAnimator3D::Release()
{
	SAFE_DELETE(m_pTimer);
}
