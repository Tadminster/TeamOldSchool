#pragma once

class ObjectManager
{
private:
	list<Prototype*> objects;

public:
	ObjectManager();
	~ObjectManager();

	void	Init();
	void	Release();
	void	Update();
	void	LateUpdate();
	void	Render();
	void    RenderHierarchy();
	
	void	GenerateTree();
	//void	GenerateInstanceTree();
	void	GenerateInstanceGrass();

	void	AddObject(Prototype* object);
};

