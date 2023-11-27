#pragma once
#include "ItemProto.h"
//class PlayerState;
class Player : public Unit
{
	friend class JumpState;
	friend class SwingState;
	
	class PlayerState*		state = nullptr;
	class WeaponProto*		equippedHand = nullptr;
	
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

	bool					isJump = false;
	bool					isPlayerCam = true;
	bool					CamtoTerrain = false;
	bool					isHit = false;
	bool					cleanHitFrame = false;

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

	//플레이어 쪽 오류 찾으려고 만듬. 나중에 GetActor로 이름 바꿀예정
	Actor*			GetPlayer()						{ return actor; }
	WeaponProto*	GetPlayerWeapon();
	float			GetWeaponDMG()					{ return equippedHand->damage; }
	WeaponType		GetWeaponType();
	Vector3			GetCollisionPoint();
	Camera*			GetPlayerCam()					{ return static_cast<Camera*>(actor->Find("PlayerCam")); }
	Camera*			GetFrustumCam()					{ return static_cast<Camera*>(actor->Find("FrustumCam")); }
	Collider*		GetCollider()					{ return actor->collider; }
	float			GetMoveSpeed()					{ return moveSpeed; }
	bool			GetPlayerJump()					{ return isJump; }
	
	bool CleanHit(Collider* object);
	bool CleanFrame();

	void ResetHitFrame() { cleanHitFrame = false; }
	
	void SetState(PlayerState* state);
	void AvtivatePlayerCam();
	void PlayerControl();
	void PlayerMove();
	void EquipToHand(WeaponProto* item);
	void ReleaseToHand();
	void MoveBack(Actor* col);
	bool GetItem(ItemProto* item);
	void PlayerHit(int damage = 1);

};