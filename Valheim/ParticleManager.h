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
	//��ƼŬ ȿ���� ���۵ǰ��� ��ġ�������ִ� �޼���
	void    PlayParticleEffect(EffectType type, Vector3 pos);
	void	SetWorldPos();
};

