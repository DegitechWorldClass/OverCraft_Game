#pragma once
class CSphere : public CollisionData
{
public:
	CSphere();
	~CSphere();

public:
	Vector3 Center;
	float	Radius; 
};

