#include "DXUT.h"
#include "COBJLoader.h"


void COBJLoader::CreateMesh(LPD3DXMESH * _pMesh)
{
	if (FAILED(D3DXCreateMeshFVF(m_vecIndex.size() / 3, m_vecVertex.size(), D3DXMESH_MANAGED | D3DXMESH_32BIT, VERTEXFVF, g_Device, _pMesh)))
	{
		DEBUG_LOG("Failed D3DXCreateMeshFVF");
		return;
	}

	Vertex * pVertices = nullptr;
	if (FAILED((*_pMesh)->LockVertexBuffer(0, (void**)&pVertices)))
	{
		DEBUG_LOG("Failed LockVertexBuffer");
		return;
	}

	memcpy(pVertices, &m_vecVertex[0], sizeof(Vertex) * m_vecVertex.size());
	(*_pMesh)->UnlockVertexBuffer();
	m_vecVertex.clear();

	DWORD * pIndices = nullptr;
	if (FAILED((*_pMesh)->LockIndexBuffer(0, (void**)&pIndices)))
	{
		DEBUG_LOG("Failed LockIndexBuffer");
		return;
	}

	memcpy(pIndices, &m_vecIndex[0], sizeof(DWORD) * m_vecIndex.size());
	(*_pMesh)->UnlockIndexBuffer();
	m_vecIndex.clear();

	DWORD * pAttribute = nullptr;
	if (FAILED((*_pMesh)->LockAttributeBuffer(0, &pAttribute)))
	{
		DEBUG_LOG("Failed LockAttributeBuffer");
		return;
	}

	memcpy(pAttribute, &m_vecAttribute[0], sizeof(DWORD) * m_vecAttribute.size());
	(*_pMesh)->UnlockAttributeBuffer();
	m_vecAttribute.clear();

	for (size_t i = 0; i < m_vecVertexCache.size(); ++i)
	{
		CacheEntry* pEntry = m_vecVertexCache[i];
		while (pEntry != NULL)
		{
			CacheEntry* pNext = pEntry->pNext;
			SAFE_DELETE(pEntry);
			pEntry = pNext;
		}
	}
	m_vecVertexCache.clear();

	m_vecPosition.clear();
	m_vecTexCoord.clear();
	m_vecNormal.clear();
}

void COBJLoader::MtlLoad(CRString & _mtlName, CModel * _pModel, CRString & _mapPath)
{
	ifstream mtlLoader;

	mtlLoader.open(m_mtlPath);

	if (mtlLoader.fail())
	{
		DEBUG_LOG("Mtl 파일 로드 실패! %s %s", _mtlName , m_mtlPath);
		return;
	}

	Material * pMtl = nullptr;
	D3DMATERIAL9 * pd3dMtl = nullptr;

	bool findMtl = false;

	while (!mtlLoader.eof())
	{
		std::string tag;
		mtlLoader >> tag;

		if (!findMtl)
		{
			if (tag == "newmtl")
			{
				mtlLoader >> tag;
				if (tag == _mtlName)
				{
					pMtl = new Material;

					pMtl->mtlName = _mtlName;
					_pModel->m_vecMaterial.push_back(pMtl);

					pd3dMtl = &pMtl->material;

					findMtl = true;
				}
			}
		}
		else
		{
			if (tag == "Ka")
			{
				float r, g, b;
				r = g = b = 0.f;

				mtlLoader >> tag;
				r = (float)atof(tag.c_str());

				mtlLoader >> tag;
				g = (float)atof(tag.c_str());

				mtlLoader >> tag;
				b = (float)atof(tag.c_str());

				pd3dMtl->Ambient = { r, g, b, 1.f };
			}
			if (tag == "Kd")
			{
				float r, g, b;
				r = g = b = 0.f;

				mtlLoader >> tag;
				r = (float)atof(tag.c_str());

				mtlLoader >> tag;
				g = (float)atof(tag.c_str());

				mtlLoader >> tag;
				b = (float)atof(tag.c_str());

				pd3dMtl->Diffuse = { r, g, b, 1.f };
			}

			if (tag == "Ks")
			{
				float r, g, b;
				r = g = b = 0.f;

				mtlLoader >> tag;
				r = (float)atof(tag.c_str());

				mtlLoader >> tag;
				g = (float)atof(tag.c_str());

				mtlLoader >> tag;
				b = (float)atof(tag.c_str());

				pd3dMtl->Specular = { r, g, b, 1.f };
			}

			if (tag == "Ke")
			{
				float r, g, b;
				r = g = b = 0.f;

				mtlLoader >> tag;
				r = (float)atof(tag.c_str());
				mtlLoader >> tag;
				g = (float)atof(tag.c_str());
				mtlLoader >> tag;
				b = (float)atof(tag.c_str());

				pd3dMtl->Emissive = { r,g,b, 1.f };
			}

			if (tag == "illum")
			{
				float l;

				mtlLoader >> tag;
				l = (float)atof(tag.c_str());

				pMtl->fIllum = l;
			}

			if (tag == "Ns")
			{
				float n;

				mtlLoader >> tag;
				n = (float)atof(tag.c_str());

				pMtl->fNs = n;
			}

			if (tag == "Tr" || tag == "d")
			{
				float a;

				mtlLoader >> tag;

				if (tag == "Tr")
					a = 1.f - (float)atof(tag.c_str());
				else
					a = (float)atof(tag.c_str());

				pMtl->fAlpha = a;
			}

			if (tag == "map_Kd")
			{
				mtlLoader >> tag;

				std::string ImagePath;

				if (_mapPath == "None")
				{
					int pathIndex = OBJPath.rfind("/"); // 마지막으로 사용된 해당 문자의 인덱스를 가져옴
					ImagePath = OBJPath.substr(0, pathIndex + 1) + tag; // 첫번쨰 인자부터 두번째 인자의 수만큼 글자를 가져옴
				}
				else
					ImagePath = _mapPath + tag;

				pMtl->DiffuseMap = IMAGE.AddTexture(ImagePath, ImagePath);
			}
			if (tag == "map_Ks")
			{
				mtlLoader >> tag;

				std::string ImagePath;

				if (_mapPath == "None")
				{
					int pathIndex = OBJPath.rfind("/"); // 마지막으로 사용된 해당 문자의 인덱스를 가져옴
					ImagePath = OBJPath.substr(0, pathIndex + 1) + tag; // 첫번쨰 인자부터 두번째 인자의 수만큼 글자를 가져옴
				}
				else
					ImagePath = _mapPath + tag;

				pMtl->specularMap = IMAGE.AddTexture(ImagePath, ImagePath);
			}


			if (tag == "newmtl")
				break;
		}
	}

	mtlLoader.close();
}

DWORD COBJLoader::AddVertex(UINT _iHash, Vertex * _pVertex)
{
	//DirectX Sample - MeshFromObj 사용함.

		// If this vertex doesn't already exist in the Vertices list, create a new entry.
			// Add the index of the vertex to the Indices list.
	bool bFoundInList = false;
	DWORD index = 0;

	// Since it's very slow to check every element in the vertex list, a hashtable stores
	// vertex indices according to the vertex position's index as reported by the OBJ file
	if ((UINT)m_vecVertexCache.size() > _iHash)
	{
		CacheEntry* pEntry = m_vecVertexCache[_iHash];
		while (pEntry != NULL)
		{
			Vertex* pCacheVertex = &m_vecVertex[pEntry->index];

			// If this vertex is identical to the vertex already in the list, simply
			// point the index buffer to the existing vertex
			if (0 == memcmp(_pVertex, pCacheVertex, sizeof(Vertex)))
			{
				bFoundInList = true;
				index = pEntry->index;
				break;
			}

			pEntry = pEntry->pNext;
		}
	}

	// Vertex was not found in the list. Create a new entry, both within the Vertices list
	// and also within the hashtable cache
	if (!bFoundInList)
	{
		// Add to the Vertices list
		index = m_vecVertex.size();
		m_vecVertex.push_back(*_pVertex);

		// Add this to the hashtable
		CacheEntry* pNewEntry = new CacheEntry;
		if (pNewEntry == NULL)
			return (DWORD)-1;

		pNewEntry->index = index;
		pNewEntry->pNext = NULL;

		// Grow the cache if needed
		while ((UINT)m_vecVertexCache.size() <= _iHash)
		{
			m_vecVertexCache.push_back(NULL);
		}

		// Add to the end of the linked list
		CacheEntry* pCurEntry = m_vecVertexCache[_iHash];
		if (pCurEntry == NULL)
		{
			// This is the head element
			//m_VertexCache.SetAt(hash, pNewEntry);
			m_vecVertexCache[_iHash] = pNewEntry;
		}
		else
		{
			// Find the tail
			while (pCurEntry->pNext != NULL)
			{
				pCurEntry = pCurEntry->pNext;
			}

			pCurEntry->pNext = pNewEntry;
		}
	}

	return index;
}

COBJLoader::COBJLoader()
{
}


COBJLoader::~COBJLoader()
{
}

void COBJLoader::OBJLoad(CModel * _pModel, CRString & _Path, CRString & _mapPath)
{
	OBJPath = _Path;

	DWORD dwAttribute = 0;

	std::ifstream loader;

	loader.open(_Path.c_str());

	if (loader.fail())
	{
		DEBUG_LOG("파일을 여는데 실패 했습니다 : %s",_Path.c_str());
		return;
	}

	while (!loader.eof())
	{
		std::string tag;
		loader >> tag;

		if (tag == "v")
		{
			Vector3 position;
			loader >> position.x >> position.y >> position.z;
			m_vecPosition.push_back(position);
			continue;
		}
		else if (tag == "vt")
		{
			Vector2 texCoord;
			loader >> texCoord.x >> texCoord.y;
			m_vecTexCoord.push_back(Vector2(texCoord.x, 1.f - texCoord.y));
			continue;
		}
		else if (tag == "vn")
		{
			Vector3 normal;
			loader >> normal.x >> normal.y >> normal.z;
			m_vecNormal.push_back(normal);
			continue;
		}
		else if (tag == "f")
		{
			for (int i = 0; i < 3; ++i)
			{
				std::string str;
				loader >> str;

				UINT iPosition;
				UINT iTexCoord;
				UINT iNormal;

				sscanf(str.c_str(), "%u/%u/%u", &iPosition, &iTexCoord, &iNormal);

				Vertex vertex;
				vertex.m_vPos = m_vecPosition[iPosition - 1];
				vertex.m_vTex = m_vecTexCoord[iTexCoord - 1];
				vertex.m_vNormal = m_vecNormal[iNormal - 1];

				DWORD index = AddVertex(iPosition, &vertex);
				m_vecIndex.push_back(index);
			}

			m_vecAttribute.push_back(dwAttribute);
			continue;
		}
		else if (tag == "mtllib")
		{
			//loader >> m_mtlPath;

			//int pathIndex = _Path.rfind("/"); // 마지막으로 사용된 해당 문자의 인덱스를 가져옴
		//	m_mtlPath = _Path.substr(0, pathIndex + 1) + m_mtlPath; // 첫번쨰 인자부터 두번째 인자의 수만큼 글자를 가져옴

			m_mtlPath = _Path;

			m_mtlPath.pop_back();
			m_mtlPath.pop_back();
			m_mtlPath.pop_back();

			m_mtlPath += "mtl";
		}
		else if (tag == "usemtl")
		{
			loader >> tag;

			bool bFind = false;

			for (size_t iMtl = 0; iMtl < _pModel->m_vecMaterial.size(); ++iMtl)
			{
				if (_pModel->m_vecMaterial[iMtl]->mtlName == tag)
				{
					dwAttribute = iMtl;
					bFind = true;
				}
			}

			if (!bFind)
			{
				dwAttribute = _pModel->m_vecMaterial.size();
				MtlLoad(tag, _pModel, _mapPath);
			}

			continue;
		}
	}

	return CreateMesh(&_pModel->m_pMesh);
}
