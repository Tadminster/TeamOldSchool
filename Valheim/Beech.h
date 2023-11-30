#pragma once
#include "Prototype.h"
#include "FeatureProto.h"

class Beech : public FeatureProto
{
private:
	friend class FeatureProto;
	
	Beech();
	~Beech() override;

public:
	void Init() override;
	void Update() override;
	void LateUpdate() override;
	void Render() override;
	void Release() override;
	void RenderHierarchy() override;

	void LodUpdate(float distance) override;
	bool ReceivedDamageEvent(float damage, WeaponType wType) override;
	void DestructionEvent() override;
};

