#pragma once
#include "ElderPatern.h"
class Elder : public Unit
{
	friend class ElderPatern;
	friend class ElderStomp;
	friend class ElderJumpAttack;
	friend class ElderSummonSpear;

	class		 ElderPatern* patern = nullptr;
	class		 ElderState*  state  = nullptr;


	float					  paternTime = 0;
	int						  jumpAttackMotion = 0;
public:
	Elder();
	~Elder();
	void Init() override;
	void Update() override;
	void LateUpdate() override;
	void Render() override;
	void Release() override;
	void RenderHierarchy() override;
	bool IsDestroyed() override;
	void DestructionEvent() override;

	void SetState(ElderState* state);
	ElderState* GetState() { return state; }
	int GetJumpAttackMotion() { return jumpAttackMotion; }
	void BehaviorPatern();
	void DoFSM();
};

