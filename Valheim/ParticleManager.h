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
	//��ƼŬ ȿ���� ���۵ǰ��� ��ġ�������ִ� �޼���
	//Vector3 SetParticlePos(Particle* effect, Vector3 startPos);
};

