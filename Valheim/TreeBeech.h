#pragma once


class TreeBeech : public Prototype
{
private:

public:
	explicit TreeBeech(Vector3 spawnPos);
	~TreeBeech();
	virtual void Init();
	virtual void Update();
	virtual void LateUpdate();
	virtual void Render();
	virtual void RenderHierarchy();
};

