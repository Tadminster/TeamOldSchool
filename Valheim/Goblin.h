#pragma once
class Goblin : public Unit
{
	class GoblinState* state = nullptr;

	float waitingTime = 0;
	vector<Vector3> idlePos = {};
	int idlePosNum = 0;
	bool isAngry = false;
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
};

