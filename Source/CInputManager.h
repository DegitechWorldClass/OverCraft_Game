#pragma once
#include "CSingleton.h"

class CInputManager :
	public CSingleton< CInputManager>
{
//	friend class CMainGame;
public:
	CInputManager();
	~CInputManager();

public:
	bool m_bCurInput[256];
	bool m_bLastInput[256];

	void Update();
public:
	bool KeyDown(BYTE Key);
	bool KeyUp(BYTE Key);
	bool KeyPress(BYTE Key);

	Vector2 GetMousePos();
	Vector2 DeltaCursorPos();

	Vector2 m_vLastCurosr;
	Vector2 m_vCurCursor;

	Vector2 m_vDeltaCursor;
};

#define INPUT (*CInputManager::GetInstance())
