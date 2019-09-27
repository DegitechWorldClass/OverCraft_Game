#pragma once
#include "CSingleton.h"
class CCameraManager :
	public CSingleton< CCameraManager>
{
public:
	CCameraManager();
	~CCameraManager();

public:
	void RayCast(CRVector3 _vPos, CRVector3 _vDir);

	void Update();
	void SetTransform();

	Matrix m_matView;
	Matrix m_matProj;
private:
	Vector3 m_vPos;
	Vector3 m_vRotation;
	Vector3 m_vLookAt;
	Vector3 m_vUp;

public:
	Vector3 GetPos() { return m_vPos; }
	void SetPos(Vector3 _vPos) { m_vPos = _vPos; }

	Vector3 GetLookAt() { return m_vLookAt; }
	void SetLookAt(Vector3 _vLookAt) { m_vLookAt = _vLookAt; }

	Vector3 GetUp() { return m_vUp;}
	void SetUp(Vector3 _vUp) { m_vUp = _vUp; }

	Vector3 GetRotation() { return m_vRotation; }
	void SetRotation(Vector3 _vRotation) { m_vRotation = _vRotation; }
};

#define CAMERA (*CCameraManager::GetInstance())

