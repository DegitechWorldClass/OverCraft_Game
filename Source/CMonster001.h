#pragma once
#include "CComponent.h"
#include "CMonsterBase.h"
class CMonster001 : public CComponent, public CMonsterBase
{

public:
	CMonster001();
	~CMonster001();
private:
	virtual void Init() override;
	virtual void Update() override;
	virtual void Render() override;
	virtual void Release() override;
	virtual void OnCollisionEnter(CObject * _pObject)	override;
	virtual void OnCollisionStay(CObject * _pObject)	override;
	virtual void OnCollisionExit(CObject * _pObject)	override;

};

