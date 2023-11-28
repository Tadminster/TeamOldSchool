#pragma once
#include "Prototype.h"
#include "FeatureProto.h"

class Birch : public FeatureProto
{
private:
	friend class FeatureProto;

	Birch();
	~Birch() override;
public:
	void Init() override;
	void Update() override;
	void LateUpdate() override;
	void Render() override;
	void Release() override;
	void RenderHierarchy() override;


public:
	void LodUpdate(float distance);

	// FeatureProto을(를) 통해 상속됨
	void DestructionEvent() override;
};

