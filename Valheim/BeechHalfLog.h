//#include "FeatureProto.h"
#pragma once
class BeechHalfLog : public FeatureProto
{

public:
	BeechHalfLog();
	~BeechHalfLog();

	void Init() override;
	void Update() override;
	void LateUpdate() override;
	void Render() override;
	void RenderHierarchy() override;
};

