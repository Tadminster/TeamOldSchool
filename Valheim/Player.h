#pragma once
#define GRAVITYPOWER 30

//class PlayerState;
class Player : public Prototype
{
	friend class JumpState;
	
	class PlayerState* state = nullptr;
	Vector3 lastPos = {};

	float moveSpeed = 0;
	float gravity = 0;
	bool isLand = 0;
	bool isJump = 0;
	bool isPlayerCam = 1;

public:
	Player();
	~Player();
	virtual void Init() override;
	virtual void Update() override;
	virtual void LateUpdate() override;
	virtual void Render() override;
	virtual void Release() override;
	virtual void RenderHierarchy() override;

	Actor* GetPlayer() { return actor; }
	Camera* GetPlayerCam() { return static_cast<Camera*>(actor->Find("PlayerCam")); }
	bool GetPlayerJump() { return isJump; }
	void SetState(PlayerState* state);

	void AvtivatePlayerCam();
	void PlayerControl();
	void PlayerMove();
	void EquipToHand(Prototype* item);
	void ReleaseToHand();

	// Prototype을(를) 통해 상속됨
	bool IsDestroyed() override;
	void DestructionEvent() override;
};