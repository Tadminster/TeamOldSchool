#pragma once
#include "FeatureProto.h"
//enum class RenderType
//{
//	SINGLE,
//	INSTANCING
//};

enum class LodLevel
{
	LOD0,
	LOD1,
	LOD3
};

class Beech : public FeatureProto
{
private:
	//RenderType type;

public:
	Beech();
	~Beech();
	void Init() override;
	void Update() override;
	void LateUpdate() override;
	void Render() override;
	void RenderHierarchy() override;

	void LodUpdate(LodLevel lv);
	//RenderType GetRenderType() { return type; }
};

