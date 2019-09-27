#include "DXUT.h"
#include "CModelManager.h"


CModelManager::CModelManager()
{
	m_pLoader = new COBJLoader();
}


CModelManager::~CModelManager()
{
	for (auto iter : m_mapModel)
	{
		SAFE_DELETE(iter.second);
	}

	m_mapModel.clear();

	for (auto iter : m_mapShader)
	{
		SAFE_RELEASE(iter.second);
	}
	m_mapShader.clear();
	SAFE_DELETE(m_pLoader);
}

CModel * CModelManager::AddModel(CRString _Key, CRString _Path, CRString _MapPath )
{
	auto find = m_mapModel.find(_Key);
	if (find != m_mapModel.end())
	{
		return find->second;
	}
	
	CModel * pModel = new CModel();

	m_pLoader->OBJLoad(pModel, _Path, _MapPath);

	m_mapModel.insert(make_pair(_Key, pModel));
	return pModel;
}

Shader * CModelManager::AddShader(CRString _Key, CRString _Path)
{
	LPD3DXEFFECT lpEffect = NULL;

	if (S_OK == D3DXCreateEffectFromFileA(
		g_Device,
		_Path.c_str(),
		NULL,
		NULL,
		NULL,
		NULL,
		&lpEffect,
		NULL))
	{
		this->m_mapShader.insert(make_pair(_Key, lpEffect));
		return lpEffect;
	}
	DEBUG_LOG("Failed LoadShader! Key : %s | Path : %s", _Key.c_str(), _Path.c_str());
	return NULL;


}
Shader * CModelManager::SelectShader(CRMatrix _matWorld, CRString _Key)
{
	// 광원의 위치
	D3DXVECTOR4 gWorldLightPosition = D3DXVECTOR4(500.0f, 500.0f, -500.0f, 1.0f);

	// 표면의 색상
	D3DXVECTOR4 gSurfaceColor = D3DXVECTOR4(0, 1, 0, 1);
	LPDIRECT3DVERTEXSHADER9 a;
	auto pShader = m_mapShader[_Key];
	// 월드/뷰/투영행렬을 미리 곱한다.
	D3DXMATRIXA16 matWorldView;
	D3DXMATRIXA16 matWorldViewProjection;
	//D3DXMatrixMultiply(&matWorldView, &matWorld, &matView);
	//D3DXMatrixMultiply(&matWorldViewProjection, &matWorldView, &matProjection);

	//	// 쉐이더 전역변수들을 설정
	//pShader->SetMatrix("gWorldViewProjectionMatrix",
	//		&matWorldViewProjection);
	//pShader->SetMatrix("gInvWorldMatrix", &matInvWorld);

	//pShader->SetVector("gWorldLightPosition", &gWorldLightPosition);
	//pShader->SetVector("gSurfaceColor", &gSurfaceColor);
}
CModel *CModelManager::FindModel(CRString _Key)
{
	auto find = m_mapModel.find(_Key);
	if (find != m_mapModel.end())
	{
		return find->second;
	}
	DEBUG_LOG("Find Model Not Found : %s", _Key.c_str());
	return nullptr;
}

vector<CModel*> CModelManager::MakeVecModel(CRString _Key)
{
	vector<CModel*> vecModel;

	for (int i = 1; ; i++)
	{
		char Key[100];
		sprintf(Key, "%s (%d)", _Key.c_str(), i);

		auto Find = FindModel(Key);
		if (Find == nullptr)
			break;

		vecModel.push_back(Find);
	}

	if (vecModel.empty() == true)
	{
		DEBUG_LOG("VECTMODEL IS EMPTY : %s", _Key.c_str());
	}

	return vecModel;
}
void CModelManager::Render(CModel * _pModel, Matrix _matWorld)
{
	g_Device->SetTransform(D3DTS_WORLD, &_matWorld);

	int i = 0;
	for (auto iter : _pModel->m_vecMaterial)
	{
		g_Device->SetMaterial(&(iter->material));

		if (iter->DiffuseMap)
			g_Device->SetTexture(0, iter->DiffuseMap->m_pTexture);

		_pModel->m_pMesh->DrawSubset(i++);
	}

}

