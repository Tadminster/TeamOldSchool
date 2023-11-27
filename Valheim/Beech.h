#pragma once
#include "Prototype.h"
#include "FeatureProto.h"
//enum class RenderType
//{
//	SINGLE,
//	INSTANCING
//};

class Beech : public FeatureProto
{
private:
	friend class FeatureProto;
	
	Beech(RenderType renderType = RenderType::Normal);
	~Beech() override;

public:
	void Init() override;
	void Update() override;
	void LateUpdate() override;
	void Render() override;
	void Release() override;
	void RenderHierarchy() override;

	void LodUpdate(float distance) override;
	void DestructionEvent() override;
};

