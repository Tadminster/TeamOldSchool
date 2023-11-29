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
	//��ƼŬ ȿ���� ���۵ǰ��� ��ġ�������ִ� �޼���
	void    PlayParticleEffect(EffectType type, Vector3 pos);
};

