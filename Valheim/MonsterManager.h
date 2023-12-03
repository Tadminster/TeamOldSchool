#pragma once
#define	JELLYFISHNUM 16
class MonsterManager
{
	class Goblin* goblin[9] = {};
	class Goblin* goblin2[4] = {};

	vector<Prototype*> unit;

	Actor* jellyFish[JELLYFISHNUM] = {};

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

