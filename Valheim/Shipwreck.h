#pragma once
#include "Prototype.h"

class Shipwreck : public FeatureProto
{
private:
	friend class FeatureProto;

	Shipwreck();
	~Shipwreck() override;

public:
	void Init() override;
	void Update() override;
	void LateUpdate() override;
	void Render() override;
	void Release() override;
	void RenderHierarchy() override;

	void UpdateLight() override;

	bool ReceivedDamageEvent(float damage, WeaponType wType) override;
	void DestructionEvent() override;
};

