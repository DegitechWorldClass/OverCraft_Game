#pragma once
#pragma once
#include "stdafx.h"
namespace Math
{
	static float PI = 3.141592f;


	//vector inner
	double absDotVector(Vector2 a, Vector2 b);
	//deg -> rad
	__inline double DegToRad(double deg);

	//deg -> rad 
	__inline double RadToDeg(double rad);

	//distance vector
	Vector2 GetDistanceVector(Rect a, Rect b);

	//height vector
	Vector2 GetHeightVector(Rect a, float _fRot);

	//width vector
	Vector2 GetWidthVector(Rect a, float _fRot);

	//unit vector
	Vector2 GetUnitVector(Vector2 a);

	Vector2 RotateVector(Vector2 _vCenter,
		Vector2 _vPoint,
		float _fDegree);
}

INT GetRandomNum(INT _Min, INT _Max);
FLOAT GetRandomNum(FLOAT _Min, FLOAT _Max);
FLOAT GetLength(Vector2 v1, Vector2 v2);