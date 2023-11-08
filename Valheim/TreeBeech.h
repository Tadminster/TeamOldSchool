#pragma once


class TreeBeech : public Prototype
{
private:

public:
	explicit TreeBeech(Vector3 spawnPos);
	~TreeBeech();
	void Init() override;
	void Update() override;
	void LateUpdate() override;
	void Render() override;
	void RenderHierarchy();
};

