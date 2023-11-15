#pragma once
#define INVENTORY_SIZE	32		// 인벤토리 크기
#define	BLUE_SLOT		32		// 블루슬롯의 인덱스

enum class UILocation
{
	OnSlot, OnPannel, OnGround
};

class Inventory
{
	friend class Player;

private:
	class ItemProto*	inventory[INVENTORY_SIZE];	// 인벤토리 (실제 아이템을 가리킬)

	// 이미지===========================================================================================
	UI*					inventoryUI;				// 인벤토리 UI
	UI*					pannel;						// 인벤토리 패널을 가리킬 포인터
	UI*					slot[INVENTORY_SIZE + 1];	// 슬롯을 가리킬 포인터(0~31 알파슬롯, 32 블루슬롯)
	// 아이템 조작===========================================================================================
	struct OnMouseItem
	{
		ItemProto*	item	{ nullptr };	// 마우스에 들고있는 아이템
		UI*			image	{ nullptr };	// 마우스에 들고있는 아이템 이미지
		int			index	{ -1 };			// 아이템의 슬롯 인덱스	
	};
	struct MouseLocation
	{
		UILocation	location;
		int			index	{ -1 };
	};
	OnMouseItem onMouse;

public:
	Inventory();
	~Inventory();

	void Init();
	void Release();
	void Update();
	void LateUpdate();
	void PreRender();
	void Render();
	void ResizeScreen();

	// ==================================================================================================
	void MouseOverSlot();
	Inventory::MouseLocation CheckMouseLocation();
	// ==================================================================================================
	void AddItem(ItemProto* item);
	void DeleteItem(string name);
	void ChangeItem();

};

