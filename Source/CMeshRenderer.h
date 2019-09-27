#pragma once
#include "CRenderer3D.h"
class CMeshRenderer : public CRenderer3D
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
	CMeshRenderer();
	~CMeshRenderer();


private:
	CModel * m_pModel;

public:
	void SetModel(CModel * _pModel)
	{
		m_pModel = _pModel;
	}
	CModel * GetModel(CModel * _pModel)
	{
		return m_pModel;
	}



};

