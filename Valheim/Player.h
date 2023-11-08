#pragma once
//class PlayerState;
class Player : public Prototype
{
	class PlayerState* state;
public:
	Player();
	~Player();
	virtual void Init();
	virtual void Update();
	virtual void LateUpdate();
	virtual void Render();
	virtual void RenderHierarchy();
	Actor* GetPlayer() { return actor; }
	void SetState(PlayerState* state);
	void AvtivatePlayerCam();
};