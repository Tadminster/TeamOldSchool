#pragma once
class MonsterManager
{
	class Goblin* goblin[9] = {};
	class Goblin* goblin2[4] = {};
	class Elder*  elder = nullptr;
	
	list<Prototype*> unit;

public:
	MonsterManager();
	~MonsterManager();

	void	Init();
	void	Release();
	void	Update();
	void	LateUpdate();
	void    RenderHierarchy();
	void	Render();
};

