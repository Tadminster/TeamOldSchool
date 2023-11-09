#pragma once

enum class RenderType
{
	SINGLE,
	INSTANCING
};

class TreeBeech : public Prototype
{
private:

public:
	explicit TreeBeech(Vector3 spawnPos, RenderType type);
	~TreeBeech();
	void Init() override;
	void Update() override;
	void LateUpdate() override;
	void Render() override;
	void RenderHierarchy();
};

