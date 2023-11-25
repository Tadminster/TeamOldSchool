#pragma once

class Grass : public Prototype
{
private:

public:
	explicit Grass(Vector3 spawnPos);
	~Grass();
	void Init() override;
	void Update() override;
	void LateUpdate() override;
	void Render() override;
	void Release() override;
	void RenderHierarchy() override {};

	// Prototype을(를) 통해 상속됨
	bool ReceivedDamageEvent(float damage, WeaponType wType) override;
	bool IsDestroyed() override;
	void DestructionEvent() override;
};

