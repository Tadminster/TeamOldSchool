#pragma once
#define GRAVITYPOWER 30
class Unit : public Prototype
{
	

protected:
	//SetOnTerrain--------------------------------------
	Vector3				groundHit = {};
	//ApplyGravity--------------------------------------
	float				gravity = 0;
	bool				isLand = 0;
	//MonsterMove--------------------------------------
	Vector3				moveDir = {};
	float				moveTime = 0;
	float				moveSpeed = 0;
	float				srcRotation = 0;
	float				destRotation = 0;
	float				angleGap = 0;
	float				rotationSpeed = 0;
	float				rotationTime = 0;
	float				rotationScale = 0.4f;

	//A Star--------------------------------------
	Ray					AstarRay;
	vector<Vector3>		way = {};
	AStar*				astar = nullptr;
	float				astarTime = 0;

	//Death-----------------------------------------
	bool				isDeath = false;
public:
	Unit();
	// Prototype을(를) 통해 상속됨
	void Init() override;
	void Update() override;
	void LateUpdate() override;
	void Render() override;
	void Release() override;
	void RenderHierarchy() override;
	bool ReceivedDamageEvent(float damage, WeaponType wType) override;
	bool IsDestroyed() override;
	void DestructionEvent() override;
	//유닛 공용 함수
	void SetOnTerrain();
	void ApplyGravity();
	void RotationForMove();
	void RotationForMove(Vector3 targetPos);
	void MonsterMove();
	void Astar();
	void Astar(Vector3 targetPos);
};

