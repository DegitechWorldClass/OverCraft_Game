#pragma once
#include "DXUT.h"
#include "Enum.h"
namespace Property
{
	static bool		UseVSync = TRUE; // ���� ����ȭ
	static WINMODE	WinMode  = WINMODE::WINDOWED;
	static Vector2	WinSize  = Vector2(1280.f, 720.f);
	static wstring	WinTitle = L"EmptyProject";
}

using namespace Property;