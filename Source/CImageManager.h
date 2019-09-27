#pragma once
#include "CSingleton.h"
struct Font
{
	LPD3DXFONT a;
	float size;
};

class CTexture;
class CImageManager :
	public CSingleton<CImageManager>
{
public:
	CImageManager();
	~CImageManager();

private:
	LPD3DXSPRITE m_pSprite = NULL;
	map<string, CTexture*> m_mapTexture;
	map<string, LPD3DXFONT> m_mapFont;

public:
	void Begin(bool isInterface);
	void End();
	void ReBegin(bool isInterface);
	void OnLostDevice();
	void OnResetDevice();
	LPD3DXFONT m_Font = NULL;
	LPD3DXLINE m_Line = NULL;


public:
	CTexture * AddTexture(CRString _Key, CRString _Path);
	CTexture * FindTexture(CRString _Key);
	void	AddFont(CRString _Key, CRString _Font);
	vector<CTexture*> MakeVecTex(CRString _Key);
	void PrintText(CRWString _wsStr, CRVector2 _vPos, int _iSize, float _fDegree, bool _bCenter, D3DCOLOR _Color);

	CTexture * operator [](const string& _Key)
	{
		return FindTexture(_Key);
	}

	void RenderLine(CRVector2 _vStart, CRVector2 _vEnd, float _fWidth, D3DCOLOR _Color, float _fRot = 0.f, CRVector2 _vCenter = Vector2(0, 0));

    //S * R * T Up to Parent
	Matrix GetWorldMatrix(CTransform * _pTransform);
public:
	void Render(
		CTexture * _pTexture,
		CRVector2 _vPos,
		CRVector2 _vScale,
		FLOAT _fDegree,
		CRRect _reRect,
		Color _Color);

	void Render(
		CTexture * _pTexture,
		CRMatrix _WorldMat,
		CRRect _reRect,
		Color _Color);

};

#define IMAGE (*CImageManager::GetInstance())
