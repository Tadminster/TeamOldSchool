#pragma once
#include "Prototype.h"
#include "FeatureProto.h"
class BeechStump : public FeatureProto
{

public:
	BeechStump();
	~BeechStump();

	void Init() override;
	void Update() override;
	void LateUpdate() override;
	void Render() override;
	void Release() override;
	void RenderHierarchy() override;

	void DestructionEvent() override;
};

