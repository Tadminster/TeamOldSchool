#pragma once
#include "Prototype.h"
#include "FeatureProto.h"

enum class BirchLod
{
	LOD0, LOD1
};

class Birch : public FeatureProto
{
private:
	friend class FeatureProto;

private:
	BirchLod lod;
	Birch();
	~Birch() override;

public:
	void Init() override;
	void Update() override;
	void LateUpdate() override;
	void Render() override;
	void Release() override;
	void RenderHierarchy() override;

	void LodUpdate(float distance) override;
	void UpdateLight() override;

	bool ReceivedDamageEvent(float damage, WeaponType wType) override;
	void DestructionEvent() override;
};

