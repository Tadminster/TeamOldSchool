#pragma once

//====================================================================================================
enum class ItemState { OnGround, OnInventory, Equipped };
enum class ItemType  { Weapon, Shield, Armor, Food, Material };
enum class Item
{
	StoneAxe, StonePickaxe, Club,
	WoodShield,
	Stone, Woodpile, FineWood, Leather,
	ElderTrophy
};
//====================================================================================================
class ItemProto : public Prototype
{
	friend class Inventory;
protected:
	UI*			icon;					// ������
	float       tooltipBoxScaleY;		// ���� �ڽ��� ������ Y

	Vector3     forwardDir	{};			// �� ����
	float		forwardForce{ 0.0f };	// ������ ���ư��� ��
	float		veclocity	{ 5.0f };	// �ӵ�
	float		gravity		{ 0.0f };	// �߷�
	Vector3		rayCollisionPoint;		// ���̰� ���� �浹�ϴ� ����

	Item		enumName;	// �̸�
	ItemType	type;		// ����
	ItemState	state;		// ����
	string 		stringName; // ���ڿ� �̸�
	int			weight;		// ����

	bool		isInteraction{ false };	// ��ȣ�ۿ� ���� ����
	RECT		text_interaction;	// ��ȣ�ۿ� �ؽ�Ʈ ����

public:
	static ItemProto* Create(Item name);
	virtual ~ItemProto() {};
	void Init() override;
	void Update() override;
	void LateUpdate() override;
	void Render() override;

	UI*				GetIcon() { return icon; }
	Item			GetEnumName() { return enumName; }
	string			GetStringName() { return stringName; }
	virtual wstring	GetExplain() = 0;
	ItemType		GetType() { return type; }
	float			GetTooltipBoxScaleY() { return tooltipBoxScaleY; }
	void			SetState(ItemState state) { this->state = state; }
	void			SetIsInteraction(bool isInteraction) { this->isInteraction = isInteraction; }

	bool			ReceivedDamageEvent(float damage, WeaponType wType) override { return false; }

	void Drop();
	virtual void Use() = 0;
	//virtual bool IsDestroyed() override;
};
//====================================================================================================
class ToolProto : public ItemProto
{

};
//====================================================================================================
enum class WeaponType { Blunt, Axe, Pickaxe, Fist };
class WeaponProto : public ItemProto
{
	friend class Player;
	friend class Inventory;
protected:
	WeaponType	wType;			// ���� ����
	float		damage;			// ���ݷ�
	int			curDurability;	// ������
	int			maxDurability;	// ������

public:
	virtual void Fix() = 0;
};
//====================================================================================================
class ShieldProto : public ItemProto
{
	friend class Player;
	friend class Inventory;
protected:
	float		damageReduced;	// ������ ������(%)
	int			curDurability;	// ������
	int			maxDurability;	// ������

public:
	virtual void Fix() = 0;
};
//====================================================================================================

class ArmorProto : public ItemProto
{
protected:
	int		defense;		// ����
	int		curDurability;	// ������
	int		maxDurability;	// ������

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
protected:
	RECT text_stack;	// ��ø���� ǥ���� �ؽ�Ʈ ����
public:
	int currentStack;	// ���� ��ø��
	int maxStack;		// �ִ� ��ø��

	// @brief	�� �������� ��ø�� ���ϴ� �Լ�
	// @brief	�Լ��� ȣ���ϴ� ��ü�� ������ �پ�� ������
	// @param	������ �����ϴ� ����� �Ǵ� ������
	void StackMerge(MaterialProto* material);
	void DestructionEvent();
	virtual bool IsDestroyed() override;
};