#pragma once


struct CacheEntry
{
	UINT index;
	CacheEntry* pNext;
};

class COBJLoader
{
private:
	string OBJPath;

	vector<Vector3> m_vecPosition;
	vector<Vector2> m_vecTexCoord;
	vector<Vector3> m_vecNormal;

	vector<Vertex>  m_vecVertex;
	vector<DWORD> m_vecIndex;
	vector<DWORD> m_vecAttribute;

	vector <CacheEntry*> m_vecVertexCache;

	string m_mtlPath;

	void CreateMesh(LPD3DXMESH * _pMesh);
	void MtlLoad(CRString & _mtlName, CModel * _pModel ,CRString & _mapPath = "None");
	DWORD AddVertex(UINT _iHash, Vertex * _pVertex);
public:
	COBJLoader();
	~COBJLoader();

	void OBJLoad(CModel * _pModel, CRString & _Path, CRString & _mapPath = "None");
};

