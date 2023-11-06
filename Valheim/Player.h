#pragma once
class Player : public Prototype, public Singleton<Player>
{
private:
	
public:
	Player();
	~Player();
	virtual void Init();
	virtual void Update();
	virtual void LateUpdate();
	virtual void Render();
};

