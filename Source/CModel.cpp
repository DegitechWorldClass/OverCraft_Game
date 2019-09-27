#include "DXUT.h"
#include "CModel.h"


CModel::CModel()
{
}


CModel::~CModel()
{
	for (auto iter : m_vecMaterial)
		SAFE_DELETE(iter);

	m_vecMaterial.clear();

	SAFE_RELEASE(m_pMesh);
}
