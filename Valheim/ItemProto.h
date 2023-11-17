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
	UI*			icon;		// ������

	Vector3     forwardDir	{};			// �� ����
	float		forwardForce{ 0.0f };	// ������ ���ư��� ��
	float		veclocity	{ 5.0f };	// �ӵ�
	float		gravity		{ 0.0f };	// �߷�
	Vector3		rayCollisionPoint;		// ���̰� ���� �浹�ϴ� ����

	string		name;		// �̸�
	ItemType	type;		// ����
	ItemState	state;		// ����
	int			weight;		// ����

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
	WeaponType	wType;			// ���� ����
	int			damage;			// ���ݷ�
	int			durability;		// ������

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