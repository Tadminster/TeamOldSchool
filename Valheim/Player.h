#pragma once
#define GRAVITYPOWER 30

//class PlayerState;
class Player : public Prototype
{
	friend class JumpState;
	friend class SwingState;
	
	class PlayerState* state = nullptr;
	Vector3 lastPos = {};

	float moveSpeed = 0;
	float gravity = 0;
	bool isLand = 0;
	bool isJump = 0;
	bool isPlayerCam = 1;

	int isEquip = 0;

public:
	Player();
	~Player();
	virtual void Init();
	virtual void Update();
	virtual void LateUpdate();
	virtual void Render();
	virtual void RenderHierarchy();

	Actor* GetPlayer() { return actor; }
	Camera* GetPlayerCam() { return static_cast<Camera*>(actor->Find("PlayerCam")); }
	bool GetPlayerJump() { return isJump; }
	void SetState(PlayerState* state);

	void AvtivatePlayerCam();
	void PlayerControl();
	void PlayerMove();
	void EquipToHand(Prototype* item);
	void ReleaseToHand();
	void TreeAttack(Prototype* tree);
};