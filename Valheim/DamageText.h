#pragma once
#define		TIME_LIMIT		2.0f 	// 알림이 사라질 시간
class DamageText
{
private:
	Billboard*	damageText;
	float		lifeTime{ 0.0f };

public:
	explicit	DamageText(int value, Vector3 spawnPos);
	~DamageText();
	void		Update();
	void		Render();
	void		Release();

	bool IsTimeOver() { return lifeTime >= TIME_LIMIT; }
};

