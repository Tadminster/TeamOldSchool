#pragma once
#include "Prototype.h"
#include "FeatureProto.h"

class BeechInstancing : public FeatureProto
{
private:
	friend class FeatureProto;

	BeechInstancing();
	~BeechInstancing() override;

public:
	void Init() override;
	void Update() override;
	void LateUpdate() override;
	void Render() override;
	void Release() override;
	void RenderHierarchy() override;
	
	void DestructionEvent() override;

	
};

