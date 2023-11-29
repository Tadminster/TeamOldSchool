#pragma once
#define MOVINGSPACE 7
class Goblin : public Unit
{
	class GoblinState* state = nullptr;
	
	float waitingTime = 0;
	float attackTime = 0;
	vector<Vector3> idlePos = {};
	int idlePosNum = 0;
	bool isAngry = false;
	bool firstHit = false;
	float angryTime = 0;
public:
	Goblin(Vector3 spawnPos={});
	~Goblin();
	void Init() override;
	void Update() override;
	void LateUpdate() override;
	void Render() override;
	void Release() override;
	void RenderHierarchy() override;
	bool ReceivedDamageEvent(float damage, WeaponType wType) override;
	bool IsDestroyed() override;
	void DestructionEvent() override;

	void SetState(GoblinState* state);
	void BehaviorPatern();
	void DoFSM();
	void Death();
};

