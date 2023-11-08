#pragma once

class ObjectManager
{
private:
	list<Prototype*>	mPrototypes;
	

public:
	ObjectManager();
	~ObjectManager();

	void	Init();
	void	Release();
	void	Update();
	void	LateUpdate();
	void	Render();
	void    RenderHierarchy();
	
	void	GenerateFeatures();
};

