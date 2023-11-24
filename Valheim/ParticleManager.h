#pragma once

class ParticleManager
{

private:
	Pop* beechDrop;
	Pop* hitBeech;
	Rain* woodHitDust;

	Pop* hitBlood;

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
	//Vector3 SetParticlePos(Particle* effect, Vector3 startPos);
};

