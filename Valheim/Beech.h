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
	//RenderType type;

public:
	Beech();
	~Beech() override;
	void Init() override;
	void Update() override;
	void LateUpdate() override;
	void Render() override;
	void Release() override;
	void RenderHierarchy() override;


public:
	void LodUpdate(LodLevel lv);

	// FeatureProto을(를) 통해 상속됨
	void DestructionEvent() override;
	void ReceivedDamageEvent(int damage) override;
};

