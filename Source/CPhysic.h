#pragma once
#include "CSingleton.h"
class CPhysic
	: public CSingleton<CPhysic>
{
public:
	CPhysic();
	~CPhysic();

public:
	bool GetPixelCollision(CTexture * _pTexture, CRRect _Box, D3DXCOLOR _Color = D3DXCOLOR(1.f,1.f,1.f,1.f));

	bool GetPixelCollision(CTexture * _pTexture, CRVector2 _Pos, D3DXCOLOR _Color = D3DXCOLOR(1.f, 1.f, 1.f, 1.f));

	bool CheckCollision(const Rect& _reRect, const Vector2& _vPos);

	bool CheckCollision(const Vector2& _vPos, const Rect& _reRect);

	bool CheckCollision(const Rect& _reRect01, const Rect& _reRect02);

	bool CheckCollision(const Rect& _reRect01, float _fRot01, const Rect& _reRect02, float _fRot02);

	bool CheckCollision(const Box& _Box01, float _fRot01, const Box& _Box02, float _fRot02);

	//bool CheckCollision(const Box& _Box, float _fRot01, const Box& _Box02, float _fRot02);

//	bool CheckCollision()
};

#define Physic (*CPhysic::GetInstance())
 
