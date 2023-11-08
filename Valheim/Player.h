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
	void SetState(PlayerState* state);
};