#pragma once
#include "ItemProto.h"
//class PlayerState;
class Player : public Unit
{
	friend class JumpState;
	friend class SwingState;
	friend class FistState;
	friend class BlockState;
	friend class DeathState;
	friend class BlockFailState;
	friend class PlayerStatus;
	friend class ElderJumpAttack;
	friend class ElderSummonSpear;
	friend class PlayerSound;

	class PlayerState*		state = nullptr;
	class PlayerStatus*		status = nullptr;
	class PlayerSound*		sound = nullptr;
	class WeaponProto*		equippedWeapon = nullptr;
	class ShieldProto*		equippedShield = nullptr;

	UI* mouseIcon;
	UI* mouseIcon2;
	UI* revive;
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
	//(할일) 손보기----------------------------------------
	Ray playerCamRay;
	Vector3 playerCamHit;
	Ray playerReverseCamRay;
	Vector3 playerReverseCamRayHit;
	
	//Hp 변수----------------------------------------------
	float					growthHp = 0.1f;
	float					healTime = 0;
	float					healGetTick = 0;
	//St 변수----------------------------------------------
	float					staminar = 30.0f;
	float					maxStaminar = 30.0f;
	float					growthStaminar = 0.05f;
	float					staminarTime = 0;
	bool					staminarOn = false;
	//경험치 변수-------------------------------------------
	int						jumpCount = 0;
	int						fistCount = 0;
	int						swingCount = 0;
	int						axeCount = 0;
	int						blockCount = 0;
	//능력치-------------------------------------------------
	float					fistDMG = 5.0f;
	float					blockStaminar = 10.0f;
	//피격 파티클 위치
	Vector3					playerhitPos = {};
	//파괴한 나무 카운트--------------------------------------
	int						treeCount = 0;

	bool					isJump = false;
	bool					isPlayerCam = true;
	bool					CamtoTerrain = false;
	bool					isHit = false;
	bool					cleanHitFrame = false;
	bool					isGuard = false;

	int						isEquip = 0;

	float					hitTime = 0;
	float					respawnTime = 0;

	float					randomDMG = 0;
public:
	bool isElderTrophy{ false };
	bool isEnding{ false };
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
	void UpdateLight() override;

	//플레이어 쪽 오류 찾으려고 만듬. 나중에 GetActor로 바꿀예정
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
	int				GetTreeCount() { return treeCount; }
	void			SetTreeCount() { treeCount++; }


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
	//Hp---------------------------------------------------------------
	void			PlayerHealth();
	//St---------------------------------------------------------------
	void			PlayerStaminar();
	float			GetStaminar() { return staminar; }
};