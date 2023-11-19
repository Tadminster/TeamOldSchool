#pragma once
#define GRAVITYPOWER 30
class Unit : public Prototype
{
protected:
	//SetOnTerrain
	Ray					UnitTopRay;
	Vector3				UnitHit = {};
	//ApplyGravity
	float				gravity = 0;
	bool				isLand = 0;
	//MonsterMove
	Vector3				moveDir = {};
	float				moveTime = 0;
	float				moveSpeed = 0;
	float				srcRotation = 0;
	float				destRotation = 0;
	float				angleGap = 0;
	float				rotationSpeed = 0;
	float				rotationTime = 0;
	float				rotationScale = 0.4f;
	//A Star
	Ray					AstarRay;
	vector<Vector3>		way = {};
	AStar*				astar = nullptr;
public:
	Unit();
	void SetOnTerrain();
	void ApplyGravity();
	void RotationForMove();
	void RotationForMove(Vector3 targetPos);
	void MonsterMove();
	virtual void Astar();
};

