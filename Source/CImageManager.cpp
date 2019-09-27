#include "DXUT.h"
#include "CImageManager.h"
#include "CTexture.h"

CImageManager::CImageManager()
{
	if(!m_pSprite)
	D3DXCreateSprite(g_Device, &m_pSprite);

	if (!m_Font)
		D3DXCreateFontW(DXUTGetD3D9Device(), 40, 0, 0, 1,
			FALSE, HANGUL_CHARSET, 0, 0, 0, L"¸¼Àº °íµñ Bold", &m_Font);

	if (!m_Line)
		D3DXCreateLine(g_Device, &m_Line);

}


CImageManager::~CImageManager()
{	
	for (auto& iter : m_mapTexture)
	{
		SAFE_DELETE(iter.second);
	}
	m_mapTexture.clear();
	SAFE_RELEASE(m_pSprite);
	SAFE_RELEASE(m_Font);
	SAFE_RELEASE(m_Line);

}

void CImageManager::Begin(bool isInterface)
{
	//m_Line->Begin();

	if (TRUE == isInterface)
	{
		m_pSprite->Begin(D3DXSPRITE_ALPHABLEND);
	}
	else m_pSprite->Begin(D3DXSPRITE_ALPHABLEND | D3DXSPRITE_OBJECTSPACE);

}

void CImageManager::End()
{
	m_pSprite->End();
	//m_Line->End();
}

void CImageManager::ReBegin(bool isInterface)
{
	//m_Line->End();
	m_pSprite->End();
	//m_Line->Begin();
	if (TRUE == isInterface)
	{
		m_pSprite->Begin(D3DXSPRITE_ALPHABLEND);
	}
	else m_pSprite->Begin(D3DXSPRITE_ALPHABLEND | D3DXSPRITE_OBJECTSPACE);

}

void CImageManager::OnLostDevice()
{
	m_pSprite->OnLostDevice();
	m_Font->OnLostDevice();
	m_Line->OnLostDevice();
}

void CImageManager::OnResetDevice()
{
	m_pSprite->OnResetDevice();
	m_Font->OnResetDevice();
	m_Line->OnResetDevice();
}

CTexture * CImageManager::AddTexture(CRString _Key, CRString _Path)
{
	auto find = m_mapTexture.find(_Key);

	if (find != m_mapTexture.end())
	{
		return find->second;
	}

	CTexture * pTexture = new CTexture;

	if (S_OK == D3DXCreateTextureFromFileExA(
		g_Device,
		_Path.c_str(),
		D3DX_DEFAULT_NONPOW2,
		D3DX_DEFAULT_NONPOW2,
		0,
		0,
		D3DFMT_UNKNOWN,
		D3DPOOL_MANAGED,
		D3DX_DEFAULT,
		D3DX_DEFAULT,
		0,
		&pTexture->m_Info,
		NULL,
		&pTexture->m_pTexture))
	{
		m_mapTexture[_Key] = pTexture;
		return pTexture;
	}
	DEBUG_LOG("FAILED LOAD TEXTURE %s", _Path.c_str());
	return nullptr;
}

CTexture * CImageManager::FindTexture(CRString _Key)
{
	auto find = m_mapTexture.find(_Key);

	if (find != m_mapTexture.end())
	{
		return find->second;
	}
	DEBUG_LOG("FAILED FIND TEXTURE : %s", _Key.c_str());
	return nullptr;
}

void CImageManager::AddFont(CRString _Key, CRString _Font)
{
	auto find = m_mapFont.find(_Key);

	if (find == m_mapFont.end())
	{
		D3DXCreateFontW(DXUTGetD3D9Device(), 10, 0, 0, 1,
			FALSE, HANGUL_CHARSET, 0, 0, 0, L"¸¼Àº °íµñ Bold", nullptr);
	}
}

vector<CTexture*> CImageManager::MakeVecTex(CRString _Key)
{
	vector<CTexture*> vecTexture;

	for (int i = 1; ; i++)
	{
		char Key[100];
		sprintf(Key, "%s (%d)", _Key.c_str(), i);

		auto Find = FindTexture(Key);
		if (Find == nullptr)
			break;

		vecTexture.push_back(Find);
	}

	if (vecTexture.empty() == true)
	{
		DEBUG_LOG("VECTEXTURE IS EMPTY : %s", _Key.c_str());
	}

	return vecTexture;
}

void CImageManager::PrintText(CRWString _wsStr, CRVector2 _vPos, int _iSize, float _fDegree, bool _bCenter, D3DCOLOR _Color)
{
//	LPD3DXFONT pFont;
//	D3DXMATRIX matWorld, matTrans, matRot;
//
//	D3DXCreateFontW(DXUTGetD3D9Device(), _iSize, 0, 0, 1,
//		FALSE, HANGUL_CHARSET, 0, 0, 0, L"¸¼Àº °íµñ Bold", &pFont);
//
//	D3DXMatrixRotationZ(&matRot, D3DXToRadian(_fDegree));
//
//	if (!_bCenter)
//		D3DXMatrixTranslation(&matTrans, _vPos.x, _vPos.y, 0);
//	else
//		D3DXMatrixTranslation(&matTrans, _vPos.x - _iSize * (_wsStr.size() * 0.25), _vPos.y - _iSize / 2.f, 0);
//
//	matWorld = matRot * matTrans;
//	m_pSprite->SetTransform(&matWorld); 
//	pFont->DrawTextW(m_pSprite, _wsStr.c_str(), _wsStr.size(), NULL, DT_CENTER | DT_NOCLIP, _Color);
//	SAFE_RELEASE(pFont); 
	D3DXMATRIX matWorld, matTrans, matRot;
	D3DXMatrixRotationZ(&matRot, D3DXToRadian(_fDegree));

	if (!_bCenter)
		D3DXMatrixTranslation(&matTrans, _vPos.x, _vPos.y, 0);
	else
		D3DXMatrixTranslation(&matTrans, _vPos.x - _iSize * (_wsStr.size() * 0.25), _vPos.y - _iSize / 2.f, 0);

	matWorld = matRot * matTrans;
	m_pSprite->SetTransform(&matWorld);
	m_Font->DrawTextW(m_pSprite, _wsStr.c_str(), _wsStr.size(), NULL, DT_CENTER | DT_NOCLIP, _Color);
}




void CImageManager::RenderLine(CRVector2 _vStart, CRVector2 _vEnd, float _fWidth, D3DCOLOR _Color, float _fRot, CRVector2 _vCenter)
{
	Vector3 vPos[2] = { {_vEnd.x - _vCenter.x ,_vEnd.y - _vCenter.y,1.f},{_vStart.x - _vCenter.x,_vStart.y - _vCenter.y,1.f} };


	Matrix matWorld, matScale, matRotation, matTransformation;

	D3DXMatrixScaling(&matScale, 1.f, 1.f, 1.f);

	D3DXMatrixRotationZ(&matRotation, D3DXToRadian(_fRot));

	D3DXMatrixTranslation(&matTransformation, (-(WinSize.x / 2.f) + _vCenter.x), (-(WinSize.y / 2.F) + _vCenter.y), 0.f);

	matWorld = matScale * matRotation * matTransformation;


	m_Line->SetWidth(_fWidth);

	m_Line->SetAntialias(true);

	m_Line->DrawTransform(vPos, 2, &(matWorld * CAMERA.m_matProj), _Color);

}

Matrix CImageManager::GetWorldMatrix(CTransform * _pTransform)
{
	Matrix matWorld, matScale, matRotationX, matRotationY, matRotationZ, matTransformation;


	D3DXMatrixScaling(&matScale, _pTransform->GetScale().x, _pTransform->GetScale().y, _pTransform->GetScale().z);
	D3DXMatrixRotationX(&matRotationX, D3DXToRadian(_pTransform->GetRotation().x));
	
	D3DXMatrixRotationY(&matRotationY, D3DXToRadian(_pTransform->GetRotation().y));

	D3DXMatrixRotationZ(&matRotationZ, D3DXToRadian(_pTransform->GetRotation().z));

	D3DXMatrixTranslation(&matTransformation, _pTransform->GetPosition().x, _pTransform->GetPosition().y, _pTransform->GetPosition().z);

	matWorld = matScale * matRotationX * matRotationY * matRotationZ * matTransformation;

	return matWorld;
}

void CImageManager::Render(CTexture * _pTexture, CRVector2 _vPos, CRVector2 _vScale,FLOAT _fDegree, CRRect _reRect, Color _Color)
{
	Vector3 vCenter = Vector3(
		 _pTexture->m_Info.Width /2.f, 
		_pTexture->m_Info.Height /2.f,
		0.f);

	Matrix matWorld, matScale, matRotation, matTransformation;


	D3DXMatrixScaling(&matScale, _vScale.x, _vScale.y, 1.f);

	D3DXMatrixRotationZ(&matRotation, D3DXToRadian(_fDegree));

	D3DXMatrixTranslation(&matTransformation, _vPos.x, _vPos.y, 0.f);

	matWorld = matScale * matRotation * matTransformation;

	m_pSprite->SetTransform(&matWorld);

	m_pSprite->Draw(_pTexture->m_pTexture, &(RECT)_reRect, &vCenter, nullptr, _Color);

}

void CImageManager::Render(CTexture * _pTexture, CRMatrix _WorldMat, CRRect _reRect, Color _Color)
{
	Vector3 vCenter = Vector3(
		_pTexture->m_Info.Width / 2.f,
		_pTexture->m_Info.Height / 2.f,
		0.f);

	

	m_pSprite->SetTransform(&_WorldMat);

	m_pSprite->Draw(_pTexture->m_pTexture, &(RECT)_reRect, &vCenter, nullptr, _Color);

}

