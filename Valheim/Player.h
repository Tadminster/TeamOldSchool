#pragma once
#define GRAVITYPOWER 30
//class PlayerState;
class Player : public Prototype
{
	friend class JumpState;
	

	class PlayerState* state = nullptr;
	Vector3 lastPos = {};

	float gravity = 0;
	bool isLand = 0;
	bool isJump = 0;
	bool isPlayerCam = 1;
public:
	Player();
	~Player();
	virtual void Init();
	virtual void Update();
	virtual void LateUpdate();
	virtual void Render();
	virtual void RenderHierarchy();
	Actor* GetPlayer() { return actor; }
	bool GetPlayerJump() { return isJump; }
	void SetState(PlayerState* state);
	void AvtivatePlayerCam();
	void PlayerControl();
};