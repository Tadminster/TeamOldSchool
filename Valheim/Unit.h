#pragma once
#define GRAVITYPOWER 30
class Unit : public Prototype
{
protected:
	Ray UnitTopRay;
	Vector3 UnitHit = {};

	float gravity = 0;
	bool isLand = 0;

public:
	Unit();
	void SetonTerrain();
	void ApplyGravity();
};

