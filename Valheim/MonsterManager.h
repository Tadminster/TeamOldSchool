#pragma once
#define	JELLYFISHNUM 16
class MonsterManager
{
	class Goblin* goblin[9] = {};
	class Goblin* goblin2[4] = {};

	class Elder_Stone* stone;
	vector<Prototype*> unit;

	Actor* monster01[JELLYFISHNUM] = {};

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

