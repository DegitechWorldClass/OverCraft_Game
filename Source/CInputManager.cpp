#include "DXUT.h"
#include "CInputManager.h"


CInputManager::CInputManager()
{
	m_vCurCursor = Vector2(0.f, 0.f);
	m_vDeltaCursor = Vector2(0.f, 0.f);
	RECT re;
	GetWindowRect(DXUTGetHWND(), &re);
	SetCursorPos(re.left + WinSize.x / 2, re.top + WinSize.y / 2.f);

}


CInputManager::~CInputManager()
{
}

void CInputManager::Update()
{
	POINT pt;
	GetCursorPos(&pt);
	//ScreenToClient(DXUTGetHWND(), &pt);

	RECT re;
	GetWindowRect(DXUTGetHWND(), &re);
	//m_vCurCursor = GetMousePos();
	//this->m_vDeltaCursor = Vector2(m_vCurCursor.x - WinSize.x / 2.f, m_vCurCursor.y - WinSize.y / 2.f);
	//m_vDeltaCursor += Vector2(8, 31);


	//SetCursorPos(re.left + WinSize.x / 2, re.top + WinSize.y / 2.f);
		memcpy(m_bLastInput, m_bCurInput, sizeof(m_bCurInput));
		for (int i = 0; i < 256; i++)
		{
			m_bCurInput[i] = false;
			if (GetAsyncKeyState(i) )
			{
				m_bCurInput[i] = true;
			}
		}
}

bool CInputManager::KeyDown(BYTE Key)
{
	return m_bCurInput[Key] && !m_bLastInput[Key];
}

bool CInputManager::KeyUp(BYTE Key)
{
	return !m_bCurInput[Key] && m_bLastInput[Key];
}

bool CInputManager::KeyPress(BYTE Key)
{
	return m_bCurInput[Key] && m_bLastInput[Key];
}

Vector2 CInputManager::GetMousePos()
{
	POINT pt;
	GetCursorPos(&pt);
	ScreenToClient(DXUTGetHWND(), &pt);
	return Vector2(pt.x, pt.y);
}

Vector2 CInputManager::DeltaCursorPos()
{
	return Vector2();
}
