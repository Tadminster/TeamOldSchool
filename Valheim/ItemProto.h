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
	UI*			icon;					// 아이콘
	float       tooltipBoxScaleY;		// 툴팁 박스의 스케일 Y

	Vector3     forwardDir	{};			// 앞 방향
	float		forwardForce{ 0.0f };	// 앞으로 나아가는 힘
	float		veclocity	{ 5.0f };	// 속도
	float		gravity		{ 0.0f };	// 중력
	Vector3		rayCollisionPoint;		// 레이가 땅과 충돌하는 지점

	Item		enumName;	// 이름
	ItemType	type;		// 종류
	ItemState	state;		// 상태
	string 		stringName; // 문자열 이름
	int			weight;		// 무게

	bool		isInteraction{ false };	// 상호작용 가능 여부
	RECT		text_interaction;	// 상호작용 텍스트 영역

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
	WeaponType	wType;			// 무기 종류
	float		damage;			// 공격력
	int			curDurability;	// 내구도
	int			maxDurability;	// 내구도

public:
	virtual void Fix() = 0;
};
//====================================================================================================
class ShieldProto : public ItemProto
{
	friend class Player;
	friend class Inventory;
protected:
	float		damageReduced;	// 데미지 감소율(%)
	int			curDurability;	// 내구도
	int			maxDurability;	// 내구도

public:
	virtual void Fix() = 0;
};
//====================================================================================================

class ArmorProto : public ItemProto
{
protected:
	int		defense;		// 방어력
	int		curDurability;	// 내구도
	int		maxDurability;	// 내구도

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
protected:
	RECT text_stack;	// 중첩수를 표시할 텍스트 영역
public:
	int currentStack;	// 현재 중첩수
	int maxStack;		// 최대 중첩수

	// @brief	두 아이템의 중첩수 더하는 함수
	// @brief	함수를 호출하는 객체는 수량이 줄어들 아이템
	// @param	수량이 증가하는 대상이 되는 아이템
	void StackMerge(MaterialProto* material);
	void DestructionEvent();
	virtual bool IsDestroyed() override;
};