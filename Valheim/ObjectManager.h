#pragma once

class ObjectManager
{
private:
	list<Prototype*>	objects;
	

public:
	ObjectManager();
	~ObjectManager();

	void	Init();
	void	Release();
	void	Update();
	void	LateUpdate();
	void	Render();
	void	FrustumCulling(Camera* cam);
	void    RenderHierarchy();
	
	void	GenerateFeatures();
	void	GenerateInstanceFeature();
	void	GenerateInstanceGrass();
};

