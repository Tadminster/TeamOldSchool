#pragma once
class Elder : public Prototype
{
	float gravity = 0;

	bool isLand = 0;

public:
	Elder();
	~Elder();
	virtual void Init() override;
	virtual void Update() override;
	virtual void LateUpdate() override;
	virtual void Render() override;
	virtual void Release() override;
	virtual void RenderHierarchy() override;
	virtual bool IsDestroyed() override;
	virtual void DestructionEvent() override;
};

