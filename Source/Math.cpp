#include "DXUT.h"
#include "Math.h"

using namespace Math;


double Math::absDotVector(Vector2 a, Vector2 b)
{
	return abs(a.x * b.x + a.y * b.y);
}

double Math::DegToRad(double deg)
{
	return deg / 180 * 3.141592;
}

double Math::RadToDeg(double rad)
{
	return rad * 180 / 3.141592;
}

Vector2 Math::GetDistanceVector(Rect a, Rect b)
{
	Vector2 ret;
	ret.x = (a.Left + (a.Right - a.Left) / 2) - (b.Left + (b.Right - b.Left) / 2);
	ret.y = (a.Top + (a.Bottom - a.Top) / 2) - (b.Top + (b.Bottom - b.Top) / 2);
	return ret;
}

Vector2 Math::GetHeightVector(Rect a, float _fRot)
{
	Vector2 ret;
	ret.x = (a.Bottom - a.Top) * cos(DegToRad(_fRot - 90)) / 2;
	ret.y = (a.Bottom - a.Top) * sin(DegToRad(_fRot - 90)) / 2;
	return ret;
}

Vector2 Math::GetWidthVector(Rect a, float _fRot)
{
	Vector2 ret;
	ret.x = (a.Right - a.Left) * cos(DegToRad(_fRot)) / 2;
	ret.y = (a.Right - a.Left) * sin(DegToRad(_fRot)) / 2;
	return ret;
}

Vector2 Math::GetUnitVector(Vector2 a)
{
	Vector2 ret;
	double size;
	size = sqrtf(pow(a.x, 2) + pow(a.y, 2));
	ret.x = a.x / size;
	ret.y = a.y / size;
	return ret;
}

Vector2 Math::RotateVector(Vector2 _vCenter, Vector2 _vPoint, float _fDegree)
{
	float rad = Math::DegToRad(_fDegree);
	float rx = (_vPoint.x - _vCenter.x)*cosf(rad) - (_vPoint.y - _vCenter.y)*sinf(rad) + _vCenter.x;
	float ry = (_vPoint.x - _vCenter.x)*sinf(rad) + (_vPoint.y - _vCenter.y)*cosf(rad) + _vCenter.y;
	return { rx , ry };
}

