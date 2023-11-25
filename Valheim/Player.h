#pragma once
#include "ItemProto.h"
//class PlayerState;
class Player : public Unit
{
	friend class JumpState;
	friend class SwingState;
	
	class PlayerState*		state = nullptr;
	class ItemProto*		equippedHand = nullptr;
	
	POINT					ptMouse;
	Vector3					Rot;

	Vector3					lastPos = {};
	Vector3					moveDir = {};

	Ray						slidingVector;
	Vector3					slidingVectorHit = {};
	//(할일) 손보기
	Ray playerCamRay;
	Vector3 playerCamHit;
	Ray playerReverseCamRay;
	Vector3 playerReverseCamRayHit;

	bool					isHit = 0;
	bool					isJump = 0;
	bool					isPlayerCam = 1;
	bool					CamtoTerrain = 0;

	int						isEquip = 0;
	float					hitTime = 0;
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

	
	Actor* GetPlayer()						{ return actor; }
	const ItemProto* GetPlayerWeapon()		{ return equippedHand; }
	Vector3 GetCollisionPoint()				{ return equippedHand->GetActor()->Find("CollisionPoint")->GetWorldPos(); }
	Camera* GetPlayerCam()					{ return static_cast<Camera*>(actor->Find("PlayerCam")); }
	Camera* GetFrustumCam()					{ return static_cast<Camera*>(actor->Find("FrustumCam")); }
	Collider* GetCollider()					{ return actor->collider; }
	float GetMoveSpeed()					{ return moveSpeed; }
	bool GetPlayerJump()					{ return isJump; }
	bool CleanHit(Collider* object);
	bool CleanFrame();

	void SetState(PlayerState* state);
	void AvtivatePlayerCam();
	void PlayerControl();
	void PlayerMove();
	void EquipToHand(ItemProto* item);
	void ReleaseToHand();
	void MoveBack(Actor* col);
	bool GetItem(ItemProto* item);
	void PlayerHit();
};