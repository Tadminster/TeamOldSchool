#pragma once
class MonsterManager
{
	class Goblin* goblin[9] = {};
	

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

