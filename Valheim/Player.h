#pragma once
#define GRAVITYPOWER 30

//class PlayerState;
class Player : public Prototype
{
	friend class JumpState;
	friend class SwingState;
	
	class PlayerState*		state = nullptr;
	Vector3					lastPos = {};
	Vector3					moveDir = {};

	Ray						slidingVector;
	Vector3					slidingVectorHit = {};

	float					moveSpeed = 0;
	float					gravity = 0;
	bool					isLand = 0;
	bool					isJump = 0;
	bool					isPlayerCam = 1;
	bool					CamtoTerrain = 0;

	int						isEquip = 0;

public:
	bool istouch = 0;
	Player();
	~Player();
	void Init() override;
	void Update() override;
	void LateUpdate() override;
	void Render() override;
	void Release() override;
	void RenderHierarchy() override;
	void DestructionEvent() override;
	bool IsDestroyed() override;

	Actor* GetPlayer() { return actor; }
	Camera* GetPlayerCam() { return static_cast<Camera*>(actor->Find("PlayerCam")); }
	Camera* GetFrustumCam() { return static_cast<Camera*>(actor->Find("FrustumCam")); }
	bool GetPlayerJump() { return isJump; }
	bool CleanHit(string name, Collider* object);
	bool CleanFrame();

	void SetState(PlayerState* state);
	void AvtivatePlayerCam();
	void PlayerControl();
	void PlayerMove();
	void EquipToHand(Prototype* item);
	void ReleaseToHand();
	void MoveBack(Actor* col);
	void GetItem(ItemProto* item);
};