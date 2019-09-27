#include "DXUT.h"
#include "CRect.h"

using namespace Math;
CRect::CRect()
{
}


CRect::~CRect()
{
}

CRect::CRect(FLOAT _fLeft, FLOAT _fTop, FLOAT _fRight, FLOAT _fBottom)
	: Left(_fLeft), Top(_fTop), Right(_fRight), Bottom(_fBottom)
{
}

CRect::CRect(Vector2 _vPos, FLOAT _fWidth, FLOAT _fHeight)
	: Left(_vPos.x), Top(_vPos.y), Right(_vPos.x + _fWidth), Bottom(_vPos.y + _fHeight)
{
}

CRect::CRect(RECT _reRect)
	: CRect((FLOAT)_reRect.left,
	(FLOAT)_reRect.top,
		(FLOAT)_reRect.right,
		(FLOAT)_reRect.bottom)
{
}

CRect::CRect(Vector2 _vVertex[4])
{
	Left = _vVertex[0].x;
	Top = _vVertex[0].y;
	Right = _vVertex[2].x;
	Bottom = _vVertex[2].y;
}

INT GetRandomNum(INT _Min, INT _Max)
{
	//시드 설정
	random_device RndDevice;
	mt19937_64 rnd(RndDevice());

	//분포 설정
	uniform_int_distribution<int> range(_Min, _Max);

	//값 추출
	return range(rnd);
}

FLOAT GetRandomNum(FLOAT _Min, FLOAT _Max)
{
	INT min = (INT)(_Min * 1000);
	INT max = (INT)(_Max * 1000);
	//시드 설정
	random_device RndDevice;
	mt19937_64 rnd(RndDevice());

	//분포 설정
	uniform_int_distribution<int> range(min, max);

	//값 추출
	return (FLOAT)(range(rnd) / 1000.f);
}

FLOAT GetLength(Vector2 v1, Vector2 v2)
{
	float y = fabsf(v2.y - v1.y);
	float x = fabsf(v2.x - v1.x);

	return x + y;
}

