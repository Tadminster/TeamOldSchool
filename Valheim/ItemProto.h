#pragma once

//====================================================================================================
enum class ItemState { OnGround, OnInventory };
enum class ItemType  { Weapon, Tool, Armor, Food, Material };
enum class ItemName 
{ 
	StoneAxe 
};
//====================================================================================================
class ItemProto : public Prototype
{
protected:
	string		name;		// 이름
	ItemType	type;		// 종류
	ItemState	state;		// 상태
	int			weight;		// 무게

public:
	static ItemProto* Create(ItemName name);
	virtual ~ItemProto() {};
	virtual void Use() = 0;
};
//====================================================================================================
class ToolProto : public ItemProto
{

};
//====================================================================================================
class WeaponProto : public ItemProto
{
protected:
	int		damage;			// 공격력
	int		durability;		// 내구도

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