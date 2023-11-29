#pragma once
#include "ItemProto.h"
//class PlayerState;
class Player : public Unit
{
	friend class JumpState;
	friend class SwingState;
	friend class FistState;

	class PlayerState*		state = nullptr;
	class WeaponProto*		equippedWeapon = nullptr;
	class ShieldProto*		equippedShield = nullptr;
	//카메라 관련 변수
	POINT					ptMouse;
	Vector3					Rot;
	//이동 관련 변수
	Vector3					lastPos = {};
	Vector3					moveDir = {};
	//슬라이딩벡터 변수
	Ray						slidingVector;
	Vector3					slidingVectorHit = {};
	UI*						playerHp = nullptr;
	UI*						playerSt = nullptr;
	//(할일) 손보기---------------------------------
	Ray playerCamRay;
	Vector3 playerCamHit;
	Ray playerReverseCamRay;
	Vector3 playerReverseCamRayHit;
	//---------------------------------------------
	bool					isJump = false;
	bool					isPlayerCam = true;
	bool					CamtoTerrain = false;
	bool					isHit = false;
	bool					cleanHitFrame = false;
	bool					isGuard = false;

	int						isEquip = 0;

	float					hitTime = 0;
	float					healTime = 0;
	float					healGetTick = 0;

	float					fistDMG = 5.0f;

	float					growthHp = 0.1f;
public:
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
	float			GetFistDMG()					{ return fistDMG; }
	WeaponProto*	GetPlayerWeapon();
	float			GetWeaponDMG();
	WeaponType		GetWeaponType();
	Vector3			GetCollisionPoint();
	Camera*			GetPlayerCam()					{ return static_cast<Camera*>(actor->Find("PlayerCam")); }
	Camera*			GetFrustumCam()					{ return static_cast<Camera*>(actor->Find("FrustumCam")); }
	Collider*		GetCollider()					{ return actor->collider; }
	bool			GetWeoponCollider(Collider* object);
	float			GetMoveSpeed()					{ return moveSpeed; }
	bool			GetPlayerJump()					{ return isJump; }
	bool			GetPlayerHit(Collider* atkcol);

	bool			CleanHit(Collider* object);
	bool			CleanFrame();

	void			ResetHitFrame() { cleanHitFrame = false; }
	
	void			SetState(PlayerState* state);
	void			AvtivatePlayerCam();
	void			PlayerControl();
	void			PlayerMove();
	void			EquipToHand(ItemProto* item);
	void			ReleaseToHand(ItemProto* item);
	void			MoveBack(Actor* col);
	bool			GetItem(ItemProto* item);
	void			PlayerHit(float damage = 1.0f);
	void			GrowthAbility();
	void			PlayerHealth();
};