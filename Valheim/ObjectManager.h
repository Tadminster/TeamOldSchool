#pragma once

class ObjectManager
{
private:
	list<std::unique_ptr<Prototype>> objects;

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
};

