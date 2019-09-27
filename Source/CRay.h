#pragma once
class CRay
{
	friend class CCameraManager;
public:
	CRay();
	~CRay();

private:
	Vector3 m_vPos;
	Vector3 m_vDir;

	void TransformRay();
};





