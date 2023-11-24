#pragma once
#include "Prototype.h"
#include "FeatureProto.h"

class Rock : public FeatureProto
{
private:
	//RenderType type;

public:
	Rock();
	~Rock() override;
	void Init() override;
	void Update() override;
	void LateUpdate() override;
	void Render() override;
	void Release() override;
	void RenderHierarchy() override;

	void LodUpdate(LodLevel lv);
	void DestructionEvent() override;
};

