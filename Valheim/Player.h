#pragma once
#include "ItemProto.h"
//class PlayerState;
class Player : public Unit
{
	friend class JumpState;
	friend class SwingState;

	class PlayerState*		state = nullptr;
	class WeaponProto*		equippedHand = nullptr;
	//ī�޶� ���� ����
	POINT					ptMouse;
	Vector3					Rot;
	//�̵� ���� ����
	Vector3					lastPos = {};
	Vector3					moveDir = {};
	//�����̵����� ����
	Ray						slidingVector;
	Vector3					slidingVectorHit = {};
	UI*						playerHp = nullptr;
	//(����) �պ���---------------------------------
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

	int						isEquip = 0;

	float					hitTime = 0;
	float					healTime = 0;
	float					healGetTick = 0;

	float					fistDMG = 5.0f;

	float					growthHp = 0.1f;
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

	//�÷��̾� �� ���� ã������ ����. ���߿� GetActor�� �̸� �ٲܿ���
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
	
	bool			CleanHit(Collider* object);
	bool			CleanFrame();

	void			ResetHitFrame() { cleanHitFrame = false; }
	
	void			SetState(PlayerState* state);
	void			AvtivatePlayerCam();
	void			PlayerControl();
	void			PlayerMove();
	void			EquipToHand(WeaponProto* item);
	void			ReleaseToHand();
	void			MoveBack(Actor* col);
	bool			GetItem(ItemProto* item);
	void			PlayerHit(float damage = 1.0f);
	void			GrowthAbility();
	void			PlayerHealth();
};