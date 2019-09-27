#pragma once
#include "CSingleton.h"
#include "COBJLoader.h"

class CModelManager :
	public CSingleton<CModelManager>
{
public:
	CModelManager();
	~CModelManager();
private:
	map <string, CModel *> m_mapModel;
	map <string, Shader *> m_mapShader;
	COBJLoader * m_pLoader;
public:
	CModel* AddModel(CRString _Key, CRString _Path, CRString _MapPath = "None");
	CModel *FindModel(CRString _Key);
	Shader * AddShader(CRString _Key, CRString _Path);

	Shader * SelectShader(CRMatrix _matWorld,  CRString _Key);


	vector<CModel*> MakeVecModel(CRString _Key);
	CModel * operator [](const string& _Key)
	{
		return FindModel(_Key);
	}

	void Render(CModel * _pModel, Matrix _matWorld);
private:
};

#define MODEL (*CModelManager::GetInstance())