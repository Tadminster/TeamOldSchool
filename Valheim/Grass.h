#pragma once

class Grass : public Prototype
{
private:

public:
	explicit Grass(Vector3 spawnPos);
	~Grass();
	void Init() override;
	void Update() override;
	void LateUpdate() override;
	void Render() override;
	void RenderHierarchy() override {};
};

