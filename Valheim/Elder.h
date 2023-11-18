#pragma once
class Elder : public Unit
{
	class ElderState* state = nullptr;
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
	void BehaviorPatern();
};

