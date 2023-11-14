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
	string		name;		// �̸�
	ItemType	type;		// ����
	ItemState	state;		// ����
	int			weight;		// ����

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
	int		damage;			// ���ݷ�
	int		durability;		// ������

public:
	virtual void Fix() = 0;
};
//====================================================================================================
class ArmorProto : public ItemProto
{
protected:
	int		defense;		// ����
	int		durability;		// ������

public:
	virtual void Fix() = 0;
};
//====================================================================================================
class FoodProto : public ItemProto
{
protected:
	int duration;					// ���ӽð�	
	int hitPointRecoveryAmount;		// ü�� ȸ����
	int staminaPointRecoveryAmount;	// ���¹̳� ȸ����
};
//====================================================================================================
class MaterialProto : public ItemProto
{

};