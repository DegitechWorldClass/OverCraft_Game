#include "DXUT.h"
#include "CText.h"


CText::CText()
{
	OBJECT.RegisterRenderer2D(this);

}


CText::~CText()
{
	OBJECT.UnRegisterRenderer2D(this);

}

void CText::Init()
{
}

void CText::Update()
{
}

void CText::Render()
{
}

void CText::Release()
{
}

void CText::OnCollisionEnter(CObject * _pObject)
{
}

void CText::OnCollisionStay(CObject * _pObject)
{
}

void CText::OnCollisionExit(CObject * _pObject)
{
}
