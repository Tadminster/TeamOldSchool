#pragma once

class ParticleManager : public Singleton<ParticleManager>
{

private:

public:
	Pop* levelUp;
	Pop* levelUpOnHead;
	Pop* healEffect;
	Rain* healEffect2;

	Pop* woodHitDust;

	Pop* beechDrop;
	Pop* hitBeech;
	Pop* hitBlood;
	Pop* hitRock;
	Pop* elderStomp;
	Pop* elderJumpAttack;

	Pop* waterSplash;
	Pop* waterWave;
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
	void	SetWorldPos();
};

