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

	class		 UI*		  ment1 = nullptr;
	class		 UI*		  ment2 = nullptr;
	class		 UI*		  ment3 = nullptr;
	class		 UI*		  ment4 = nullptr;

	class		 UI*		  hp = nullptr;

	float					  mentTime = 0;

	int						  paternType = 0;
	float					  paternTime = 0;
	int						  jumpAttackMotion = 0;
	bool					  stompPatern = true;
	bool					  isElder = false;
	bool					  isDeath = false;
public:
	float					  deathTime = 0;
	Elder();
	~Elder();
	void Init() override;
	void Update() override;
	void LateUpdate() override;
	void Render() override;
	void Release() override;
	void RenderHierarchy() override;
	void UpdateLight() override;
	bool IsDestroyed() override;
	bool ReceivedDamageEvent(float damage, WeaponType wType) override;
	void DestructionEvent() override;

	void SetState(ElderState* state);
	ElderState* GetState() { return state; }
	int GetJumpAttackMotion() { return jumpAttackMotion; }
	bool GetIsElder() { return isElder; }
	bool GetIsDeath() { return isDeath; }
	void BehaviorPatern();
	void DoFSM();
};

