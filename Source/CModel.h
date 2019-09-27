#pragma once


struct Vertex
{
	Vector3 m_vPos;
	Vector3 m_vNormal;
	Vector2 m_vTex;

	Vertex(Vector3 _vPos, Vector2 _vTex, Vector3 _vNormal)
		:m_vPos(_vPos), m_vNormal(_vTex), m_vTex(_vNormal)
	{}
	Vertex() {}
};
struct Material
{
	std::string mtlName;

	D3DMATERIAL9 material;
	CTexture * DiffuseMap = nullptr;
	CTexture * specularMap = nullptr;

	float fAlpha;
	float fIllum;
	float fNs;

	Material()
		:fAlpha(1.f), fIllum(0.f), fNs(0.f)
	{
		material.Power = 1;
	}
};
class CModel
{
	friend class CModelManager;
public:
	CModel();
	~CModel();
	friend class COBJLoader;
private:
	LPD3DXMESH m_pMesh;
	std::vector<Material*> m_vecMaterial;

public:
	LPD3DXMESH GetD3DXMesh() { return m_pMesh; }
	Material * GetMaterial(int index)
	{
		return m_vecMaterial[index];
	}
	CTexture  * GetDiffuseMap(int index)
	{
		return m_vecMaterial[index]->DiffuseMap;
	}
	CTexture * GetSpecularMap(int index)
	{
		return m_vecMaterial[index]->specularMap;
	}
	

};


//x작고  y 작고 z 작음
//
//x크고  y 작고   z  작음
//
//x작고 y작고 z 큼
//
//x크고 y작고 z 큼





