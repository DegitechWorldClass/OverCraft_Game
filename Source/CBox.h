#pragma once
class CBox : public CollisionData
{
public:
	CBox();
	~CBox();

public:
	Vector3 LocalMin;
	Vector3 LocalMax;

	Vector3 Center;
	Vector3 Rotation;
	Vector3 Radius;

	Vector3 GetMin() { return Center + LocalMin; }
	Vector3 GetMax() { return Center + LocalMax; }
public:
	Vector3 GetAxisX() { return Vector3(0,0,0); }

	Vector3 GetAxisY() { return Vector3(0,0,0); }
	Vector3 GetAxisZ() { return Vector3(0,0,0); }

};

