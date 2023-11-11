#pragma once

enum class RenderType
{
	SINGLE,
	INSTANCING
};

enum class LodLevel
{
	LOD0,
	LOD1,
	LOD3
};

class TreeBeech : public Prototype
{
private:
	RenderType type;

public:
	explicit TreeBeech(Vector3 spawnPos, RenderType type);
	~TreeBeech();
	void Init() override;
	void Update() override;
	void LateUpdate() override;
	void Render() override;
	void RenderHierarchy() override;

	void LodUpdate(LodLevel lv);
	RenderType GetRenderType() { return type; }
};

