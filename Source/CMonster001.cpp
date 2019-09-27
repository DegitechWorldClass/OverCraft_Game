#include "DXUT.h"
#include "CMonster001.h"


CMonster001::CMonster001()
{
}


CMonster001::~CMonster001()
{
}

void CMonster001::Init()
{
	this->AddComponent<CMeshRenderer>();
	this->AddComponent<CAnimation3D>();
	
}

void CMonster001::Update()
{
}

void CMonster001::Render()
{
}

void CMonster001::Release()
{
}

void CMonster001::OnCollisionEnter(CObject * _pObject)
{
}

void CMonster001::OnCollisionStay(CObject * _pObject)
{
}

void CMonster001::OnCollisionExit(CObject * _pObject)
{
}
