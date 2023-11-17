#pragma once

//====================================================================================================
enum class ItemState { OnGround, OnInventory, Equipped };
enum class ItemType  { Weapon, Tool, Armor, Food, Material };
enum class ItemName 
{ 
	StoneAxe 
};
//====================================================================================================
class ItemProto : public Prototype
{
protected:
	UI*			icon;		// 아이콘

	Vector3     forwardDir	{};			// 앞 방향
	float		forwardForce{ 0.0f };	// 앞으로 나아가는 힘
	float		veclocity	{ 5.0f };	// 속도
	float		gravity		{ 0.0f };	// 중력
	Vector3		rayCollisionPoint;		// 레이가 땅과 충돌하는 지점

	string		name;		// 이름
	ItemType	type;		// 종류
	ItemState	state;		// 상태
	int			weight;		// 무게

public:
	static ItemProto* Create(ItemName name);
	virtual ~ItemProto() {};
	void Init() override;
	void Update() override;
	void LateUpdate() override;

	UI*	GetIcon() { return icon; }
	ItemType GetType() { return type; }
	void SetState(ItemState state) { this->state = state; }

	void Drop();
	virtual void Use() = 0;
};
//====================================================================================================
class ToolProto : public ItemProto
{

};
//====================================================================================================
enum class WeaponType { Sword, Axe, Pickaxes, Spear, Bow, Shield };
class WeaponProto : public ItemProto
{
protected:
	WeaponType	wType;			// 무기 종류
	int			damage;			// 공격력
	int			durability;		// 내구도

public:
	virtual void Fix() = 0;
};
//====================================================================================================
class ArmorProto : public ItemProto
{
protected:
	int		defense;		// 방어력
	int		durability;		// 내구도

public:
	virtual void Fix() = 0;
};
//====================================================================================================
class FoodProto : public ItemProto
{
protected:
	int duration;					// 지속시간	
	int hitPointRecoveryAmount;		// 체력 회복량
	int staminaPointRecoveryAmount;	// 스태미너 회복량
};
//====================================================================================================
class MaterialProto : public ItemProto
{

};