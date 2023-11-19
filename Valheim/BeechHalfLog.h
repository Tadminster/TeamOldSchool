#pragma once
#include "Prototype.h"
#include "ItemProto.h"
#include "FeatureProto.h"
class BeechHalfLog : public FeatureProto
{

public:
	BeechHalfLog();
	~BeechHalfLog();

	void Init() override;
	void Update() override;
	void LateUpdate() override;
	void Render() override;
	void Release() override;
	void RenderHierarchy() override;

	void DestructionEvent() override;
};

