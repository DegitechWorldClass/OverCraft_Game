#include "DXUT.h"
#include "CLineRenerer.h"


CLineRenerer::CLineRenerer()
{
	OBJECT.RegisterRenderer2D(this);

}


CLineRenerer::~CLineRenerer()
{
	OBJECT.UnRegisterRenderer2D(this);

}

void CLineRenerer::Init()
{
}

void CLineRenerer::Update()
{
}

void CLineRenerer::Render()
{
}

void CLineRenerer::Release()
{
}

void CLineRenerer::OnCollisionEnter(CObject * _pObject)
{
}

void CLineRenerer::OnCollisionStay(CObject * _pObject)
{
}

void CLineRenerer::OnCollisionExit(CObject * _pObject)
{
}
