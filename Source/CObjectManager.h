#pragma once
#include "CSingleton.h"




class CObjectManager :
	public CSingleton<CObjectManager>
{
	friend class CMainGame;
public:
	CObjectManager();
	~CObjectManager();
private:
	list<CObject *> m_Objects;
	list<CRenderer3D *> m_listRender3D;
	map<SortingLayer, list<CRenderer2D * >> m_SortedRenderer2DList;

	map<ObjectTag, set<ObjectTag>> m_mapCollisionDetectlist;



public:
	void RegisterRenderer2D(CRenderer2D * _pRenderer2D);
	void UnRegisterRenderer2D(CRenderer2D * _pRenderer2D);

	void RegisterRenderer3D(CRenderer3D * _pRenderer3D);

	void UnRegisterRenderer3D(CRenderer3D * _pRenderer3D);
	void ClearAllObjects();
	void DeleteCollisionDetect(ObjectTag Tag1, ObjectTag Tag2);
	CObject * FindObjectWithName(CRString _Name);
	list<CObject *> FindObjectsWithName(CRString _Name);
	CObject * FindObjectWithTag(ObjectTag _Tag);
	list<CObject *> FindObjectsWithTags(ObjectTag _Tag);

	CObject * AddObject(CRString _ObjectName = "GameObject",ObjectTag _ObjectTag = Untagged)  // 디폴트 파라미터
	{
		CObject * pObject = new CObject();

		pObject->Transform = pObject->AddComponent<CTransform>();
		pObject->m_Tag = _ObjectTag;
		pObject->m_iDepth = 0;
		pObject->m_Name = _ObjectName;
		pObject->Init();

		m_Objects.push_back(pObject);
		return pObject;
	}

	

	
private:
	void Update();
	void Render();

};

#define OBJECT (*CObjectManager::GetInstance())