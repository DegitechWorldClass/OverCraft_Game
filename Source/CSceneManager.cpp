#include "DXUT.h"
#include "CSceneManager.h"
#include "CScene.h"

CSceneManager::CSceneManager()
{
}


CSceneManager::~CSceneManager()
{
	if (m_pCurScene)
		m_pCurScene->Release();

	if (m_pNextScene)
		m_pNextScene->Release();

	for (auto iter : m_mapScene)
	{
		SAFE_DELETE(iter.second);
	}
	m_mapScene.clear();
}

CScene * CSceneManager::AddScene(CRString _Key, CScene * _pScene)
{
	auto find = m_mapScene.find(_Key);

	if (find == m_mapScene.end())
	{
		m_mapScene[_Key] = _pScene;
		return _pScene;
	}
	else
	{
		SAFE_DELETE(_pScene);
		return nullptr;
	}
}

CScene * CSceneManager::ChangeScene(CRString _Key)
{
	m_pNextScene = m_mapScene.find(_Key)->second;
	return m_pNextScene;
}

CRString CSceneManager::GetCurrentScene()
{
	if (m_pCurScene)
	{
		for (auto iter : m_mapScene)
		{
			if (iter.second == m_pCurScene)
			{
				return iter.first;
			}
		}
	}
	return "NULL";
}

void CSceneManager::Update()
{
	if (m_pCurScene)
		m_pCurScene->Update();

	if (m_pNextScene)
	{
		if (m_pCurScene)
			m_pCurScene->Release();

		OBJECT.ClearAllObjects();
		m_pCurScene = m_pNextScene;
		m_pNextScene = nullptr;
		m_pCurScene->Init();
	}
}

void CSceneManager::Render()
{
	if (m_pCurScene)
		m_pCurScene->Render();
}
