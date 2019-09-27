#include "DXUT.h"
#include "CTerrain.h"
const DWORD CTerrain::TerrainVertex::FVF = D3DFVF_XYZ | D3DFVF_TEX1;


CTerrain::CTerrain()
{
	OBJECT.RegisterRenderer3D(this);
}


CTerrain::~CTerrain()
{
	OBJECT.UnRegisterRenderer3D(this);
}

void CTerrain::CreateHeightMap(CRString _Path, int _NumVertsPerRow, int _NumVertsPerCol, int _CellSpacing, float _HeightScale)
{
	m_iNumVertsPerRow = _NumVertsPerRow;
	m_INumVertsPerCol = _NumVertsPerCol;
	m_iCellSpacing = _CellSpacing;

	m_iNumCellsPerRow = m_iNumVertsPerRow - 1;
	m_iNumCellsPerCol = m_INumVertsPerCol - 1;

	m_iWidth = m_iNumCellsPerRow * m_iCellSpacing;
	m_iDepth = m_iNumCellsPerCol * m_iCellSpacing;

	m_iNumVertices = m_iNumVertsPerRow   * m_INumVertsPerCol ;
	m_iNumTriangles = m_iNumCellsPerRow  * m_iNumCellsPerCol  * 2;

	m_fHeightScale = _HeightScale;

	LoadRawFile(_Path);

	for (auto& iter : m_vecHeightmap)
	{
		iter *= m_fHeightScale;
	}
	
	ComputeVertices();

	ComputeIndices();
}

int CTerrain::GetHeightMapEntry(int _Row, int _Col)
{
	return m_vecHeightmap[_Row * m_iNumVertsPerRow + _Col];
}

void CTerrain::SetHeightMapEntry(int _Row, int _Col, int _Value)
{
	m_vecHeightmap[_Row * m_iNumVertsPerRow + _Col] = _Value;
}

float CTerrain::GetHeight(float _fX, float _fZ)
{
	_fX = ((float)m_iWidth / 2.f) + _fX;
	_fZ = ((float)m_iDepth / 2.f) - _fZ;

	_fX /= (float)m_iCellSpacing;
	_fZ /= (float)m_iCellSpacing;

	float col = floorf(_fX);
	float row = floorf(_fZ);

	float A = GetHeightMapEntry(row, col);
	float B = GetHeightMapEntry(row, col + 1);
	float C = GetHeightMapEntry(row + 1, col);
	float D = GetHeightMapEntry(row + 1, col + 1);


	float dx = _fX - col;
	float dz = _fZ - row;

	float height = 0.f;
	if (dz < 1.f - dx)
	{
		float uy = B - A;
		float vy = C - A;

		height = A + lerp(0.0f, uy, dx) + lerp(0.0f, vy, dz );
	}
	else
	{
		float uy = C - D;
		float vy = B - D;

		

		height = D + lerp(0.0f, uy, 1.f - dx ) +lerp(0.0f, vy, 1.f - dz);
	}

	return height;
}

void CTerrain::LoadTexture(CRString _Path)
{
	D3DXCreateTextureFromFileA(
		g_Device,
		_Path.c_str(),
		&m_pTexture
	);
}

void CTerrain::genTextrue(Vector3 DirectionToLight)
{
	int texWidth  = m_iNumCellsPerRow;
	int texHeight = m_iNumCellsPerCol;

	D3DXCreateTexture(
		g_Device,
		texWidth, texHeight,
		0,
		0,
		D3DFMT_X8R8G8B8,
		D3DPOOL_MANAGED,
		&m_pTexture);

	D3DSURFACE_DESC textureDesc;
	m_pTexture->GetLevelDesc(NULL, &textureDesc);

	D3DLOCKED_RECT LockRect;
	m_pTexture->LockRect(NULL, &LockRect, NULL, NULL);

	DWORD * PixelData = (DWORD*)LockRect.pBits;
	for (int i = 0; i < texHeight; i++)
	{
		for (int j = 0; j < texWidth; j++)
		{
			D3DXCOLOR c;

			float height = (float)GetHeightMapEntry(i, j) / m_fHeightScale;

			if ((height) < 42.5f) 		 c = BEACH_SAND;
			else if ((height) < 85.0f)	 c = LIGHT_YELLOW_GREEN;
			else if ((height) < 127.5f)  c =  PUREGREEN;
			else if ((height) < 170.0f)  c =  DARK_YELLOW_GREEN;
			else if ((height) < 212.5f)  c =  DARKBROWN;
			else	                     c = WHITE;

			PixelData[i * LockRect.Pitch / 4 + j] = (D3DCOLOR)c;
		}
	}
	m_pTexture->UnlockRect(0);

	LightTerrain(DirectionToLight);

	D3DXFilterTexture(
		m_pTexture,
		NULL,
		NULL,
		D3DX_DEFAULT);
}



void CTerrain::LoadRawFile(CRString _Path)
{
	std::vector<BYTE> in(m_iNumVertices);

	std::ifstream inFile(_Path.c_str(), std::ios_base::binary);

	inFile.read(
		(char*)&in[0], // buffer
		in.size());// number of bytes to read into buffer

	inFile.close();

	// copy BYTE vector to int vector
	m_vecHeightmap.resize(m_iNumVertices);

	for (int i = 0; i < in.size(); i++)
		m_vecHeightmap[i] = in[i];
}

void CTerrain::ComputeVertices()
{
	g_Device->CreateVertexBuffer(
		m_iNumVertices * sizeof(TerrainVertex),
		D3DUSAGE_WRITEONLY,
		TerrainVertex::FVF,
		D3DPOOL_MANAGED,
		&m_pVertexBuffer,
		NULL);

	int StartX = -m_iWidth / 2;
	int StartZ = m_iDepth / 2;


	int EndX = m_iWidth / 2;
	int EndZ = -m_iDepth / 2;

	float uCoordIncrementSize = 1.0f / (float)m_iNumCellsPerRow;
	float vCoordIncrementSize = 1.0f / (float)m_iNumCellsPerCol;

	TerrainVertex * Vertex = NULL;

	m_pVertexBuffer->Lock(0, 0, (void**)&Vertex, NULL);

	int i = 0;
	for (int z = StartZ; z >= EndZ; z -= m_iCellSpacing)
	{
		int j = 0;
		for (int x = StartX; x <= EndX; x += m_iCellSpacing)
		{
			int Index = i * m_iNumVertsPerRow + j;

			Vertex[Index] = TerrainVertex(
				(float)x,
				(float)m_vecHeightmap[Index],
				(float)z,
				(float)j * uCoordIncrementSize,
				(float)i * vCoordIncrementSize);

			j++;
		}
		i++;
	}
	m_pVertexBuffer->Unlock();

}

void CTerrain::ComputeIndices()
{
	g_Device->CreateIndexBuffer(
		m_iNumTriangles * 3 * sizeof(WORD),
		D3DUSAGE_WRITEONLY,
		D3DFMT_INDEX16,
		D3DPOOL_MANAGED,
		&m_pIndexBuffer,
		NULL);
	WORD * indices = NULL;
	m_pIndexBuffer->Lock(0, 0, (void**)&indices, 0);

	int baseIndex = 0;

	for (int i = 0; i < m_iNumCellsPerCol; i++)
	{
		for (int j = 0; j < m_iNumCellsPerRow; j++)
		{
			indices[baseIndex]		=	i		* m_iNumVertsPerRow + j;
			indices[baseIndex + 1]	=	i		* m_iNumVertsPerRow + j + 1;
			indices[baseIndex + 2]	= (i + 1)	* m_iNumVertsPerRow + j;

			indices[baseIndex + 3]	= (i + 1)	* m_iNumVertsPerRow + j;
			indices[baseIndex + 4]	=	 i		* m_iNumVertsPerRow + j + 1;
			indices[baseIndex + 5]	= (i + 1)	* m_iNumVertsPerRow + j + 1;

			baseIndex += 6;
		}
	}

	m_pIndexBuffer->Unlock();
}

void CTerrain::LightTerrain(Vector3 _directionToLight)
{
	D3DSURFACE_DESC textureDesc;
	m_pTexture->GetLevelDesc(0, &textureDesc);

	D3DLOCKED_RECT LockRect;
	m_pTexture->LockRect(
		NULL,
		&LockRect,
		NULL,
		NULL);

	DWORD * PixelData = (DWORD*)LockRect.pBits;
	for (int i = 0; i < textureDesc.Height; i++)
	{
		for (int j = 0; j < textureDesc.Width; j++)
		{
			int index = i * LockRect.Pitch / 4 + j;

			D3DXCOLOR c(PixelData[index]);

			c *= ComputeShade(i, j, _directionToLight);

			PixelData[index] = (D3DCOLOR)c;
		}
	}
	m_pTexture->UnlockRect(NULL);
}

float CTerrain::ComputeShade(int _CellRow, int _CellCol, Vector3 _DirectionToLight)
{

	// get heights of three vertices on the quad
	float heightA = GetHeightMapEntry(_CellRow, _CellCol);
	float heightB = GetHeightMapEntry(_CellRow, _CellCol + 1);
	float heightC = GetHeightMapEntry(_CellRow + 1, _CellCol);

	// build two vectors on the quad
	D3DXVECTOR3 u(m_iCellSpacing, heightB - heightA, 0.0f);
	D3DXVECTOR3 v(0.0f, heightC - heightA, -m_iCellSpacing);

	// find the normal by taking the cross product of two
	// vectors on the quad.
	D3DXVECTOR3 n;
	D3DXVec3Cross(&n, &u, &v);
	D3DXVec3Normalize(&n, &n);

	float cosine = D3DXVec3Dot(&n, &_DirectionToLight);

	if (cosine < 0.0f)
		cosine = 0.0f;

	return cosine;

}

void CTerrain::Init()
{
}

void CTerrain::Update()
{
}

void CTerrain::Render()
{
	Matrix matWorld;
	matWorld = IMAGE.GetWorldMatrix(this->Transform);
	auto handle = this->m_pObject;
	while (handle->m_pParent != nullptr)
	{
		handle = handle->m_pParent;
		matWorld *= IMAGE.GetWorldMatrix(handle->Transform);
	}

	g_Device->SetTransform(D3DTS_WORLD, &matWorld);

	g_Device->SetStreamSource(0, m_pVertexBuffer, 0, sizeof(TerrainVertex));
	g_Device->SetFVF(TerrainVertex::FVF);
	g_Device->SetIndices(m_pIndexBuffer);

	g_Device->SetTexture(NULL, m_pTexture);

	g_Device->SetRenderState(D3DRS_LIGHTING, FALSE);
	g_Device->DrawIndexedPrimitive(
		D3DPT_TRIANGLELIST,
		NULL,
		NULL,
		m_iNumVertices,
		NULL,
		m_iNumTriangles);
	g_Device->SetRenderState(D3DRS_LIGHTING, TRUE);


	//g_Device->SetRenderState(D3DRS_FILLMODE, D3DFILL_WIREFRAME);
	//g_Device->DrawIndexedPrimitive(
	//	D3DPT_TRIANGLELIST,
	//	NULL,
	//	NULL,
	//	m_iNumVertices,
	//	NULL,
	//	m_iNumTriangles);
	//
	//g_Device->SetRenderState(D3DRS_FILLMODE, D3DFILL_SOLID);
}	

void CTerrain::Release()
{
	m_pVertexBuffer->Release();
	m_pTexture->Release();
	m_pIndexBuffer->Release();
}

void CTerrain::OnCollisionEnter(CObject * _pObject)
{
}

void CTerrain::OnCollisionStay(CObject * _pObject)
{
}

void CTerrain::OnCollisionExit(CObject * _pObject)
{
}
