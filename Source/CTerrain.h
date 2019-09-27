#pragma once
#include "CRenderer3D.h"
class CTerrain : public CRenderer3D
{
	friend class CObjectManager;
	friend class CObject;
private:
	virtual void Init() override;
	virtual void Update() override;
	virtual void Render() override;
	virtual void Release() override;
	virtual void OnCollisionEnter(CObject * _pObject)	override;
	virtual void OnCollisionStay(CObject * _pObject)	override;
	virtual void OnCollisionExit(CObject * _pObject)	override;

public:
	CTerrain();
	~CTerrain();

	void CreateHeightMap(CRString _Path, int _NumVertsPerRow, int _NumVertsPerCol, int _CellSpacing, float _HeightScale);

	int GetHeightMapEntry(int _Row, int _Col);
	void SetHeightMapEntry(int _Row, int _Col, int _Value);

	float GetHeight(float _fX, float _fZ);
	
	void LoadTexture(CRString _Path);
	void genTextrue(Vector3 DirectionToLight);


private:
	LPDIRECT3DINDEXBUFFER9 m_pIndexBuffer;
	LPDIRECT3DVERTEXBUFFER9 m_pVertexBuffer;
	LPDIRECT3DTEXTURE9	m_pTexture;

	int m_iNumVertsPerRow;
	int m_INumVertsPerCol;

	int m_iCellSpacing; // 셀 간의 간격

	int m_iNumCellsPerRow;
	int m_iNumCellsPerCol;
	int m_iWidth;
	int m_iDepth;
	int m_iNumVertices;
	int m_iNumTriangles;


	float m_fHeightScale; // 높이 배율을 조정하는 값

	vector<int> m_vecHeightmap;
	struct TerrainVertex
	{
		TerrainVertex() {}
		TerrainVertex(float x, float y, float z, float u, float v)
		{
			_x = x; _y = y; _z = z; _u = u; _v = v;
		}
		float _x, _y, _z;
		float _u, _v;

		static const DWORD FVF;
	};
public:
	void  LoadRawFile(CRString _Path);
	void  ComputeVertices();
	void  ComputeIndices();
	void  LightTerrain(Vector3 _directionToLight);
	float ComputeShade(int _CellRow, int _CellCol, Vector3 _DirectionToLight);

};

