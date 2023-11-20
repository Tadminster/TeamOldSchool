#pragma once

class Workbench : public Prototype
{
private:

public:
	Workbench();
	~Workbench() override;
	void Init() override;
	void Update() override;
	void LateUpdate() override;
	void Render() override;
	void Release() override;
	void RenderHierarchy() override;

	bool ReceivedDamageEvent(int damage) override;
	bool IsDestroyed() override;
	void DestructionEvent() override;
};

