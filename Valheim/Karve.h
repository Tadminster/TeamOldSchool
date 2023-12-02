#pragma once
#include "Prototype.h"

class Karve : public FeatureProto
{
private:
	friend class FeatureProto;

	Karve();
	~Karve() override;

public:
	void Init() override;
	void Update() override;
	void LateUpdate() override;
	void Render() override;
	void Release() override;
	void RenderHierarchy() override;
};

