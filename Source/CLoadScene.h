#pragma once
#include "CScene.h"
struct SoundLoadData
{
public:
	SoundLoadData(CRString _Key, CRString _Path) : m_Key(_Key), m_Path(_Path) { }
	~SoundLoadData() {}
public:
	string m_Key;
	string m_Path;
};

struct MeshLoadData
{
public:
	MeshLoadData(CRString _Key, CRString _Path ,CRString _MapPath) : m_Key(_Key), m_Path(_Path), m_MapPath(_MapPath) { }
	~MeshLoadData() {}
public:
	string m_Key;
	string m_Path;
	string m_MapPath;
};

struct ImageLoadData
{
public:
	ImageLoadData(CRString _Key, CRString _Path) : m_Key(_Key), m_Path(_Path) { }
	~ImageLoadData() {}
public:
	string m_Key;
	string m_Path;
};


class CLoadScene : public CScene
{
public:
	CLoadScene();
	~CLoadScene();
public:
	virtual void Init() override;
	virtual void Update() override;
	virtual void Render() override;
	virtual void Release() override;

	void LoadSprite (CRString _Key, CRString _Path, int _iSize = 1);
	void LoadMesh	(CRString _Key, CRString _Path, CRString _MapPath, int _iSize = 1);
	void LoadSound	(CRString _Key, CRString _Path, int _iSize = 1);
	static void LoadMeshFirst(MeshLoadData& _Handle);
private:
	vector<MeshLoadData>  m_vecMeshLoad ;
	vector<SoundLoadData> m_vecSoundLoad;
	vector<ImageLoadData> m_vecImageLoad;

	thread m_MeshLoadThread[8];


	int m_LoadSize;
	int m_LoadMax;

};

