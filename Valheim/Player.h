#pragma once
//class PlayerState;
class Player : public Prototype
{
	class PlayerState* state;
public:
	Player();
	~Player();
	void Init();
	void Update();
	void LateUpdate();
	void Render();
	Actor* GetPlayer() { return actor; }
	void SetState(PlayerState* state);
};