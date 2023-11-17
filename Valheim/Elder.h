#pragma once
class Elder : public Unit
{
	Actor* bossStone = nullptr;


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
};

