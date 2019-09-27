#pragma once
#include "DXUT.h"
#include "Enum.h"
namespace Property
{
	static bool		UseVSync = TRUE; // 수직 동기화
	static WINMODE	WinMode  = WINMODE::WINDOWED;
	static Vector2	WinSize  = Vector2(1280.f, 720.f);
	static wstring	WinTitle = L"EmptyProject";
}

using namespace Property;