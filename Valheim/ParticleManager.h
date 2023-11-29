#pragma once

class ParticleManager
{

private:

public:

	Rain* woodHitDust;

	Pop* beechDrop;
	Pop* hitBeech;
	Pop* hitBlood;
	Pop* hitRock;

public:
	ParticleManager();
	~ParticleManager();

	void	Init();
	void	Release();
	void	Update();
	void	LateUpdate();
	void	Render();
	void    RenderHierarchy();
	//파티클 효과를 시작되게할 위치지정해주는 메서드
	void    PlayParticleEffect(EffectType type, Vector3 pos);
};

