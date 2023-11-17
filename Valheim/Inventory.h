#pragma once
#define INVENTORY_SIZE		32		// 인벤토리 크기
#define INVENTORY_ROW_SIZE	8		// 인벤토리 1줄 크기
#define	BLUE_SLOT			32		// 블루슬롯의 인덱스

enum class UILocation
{
	OnSlot, OnPannel, OnGround
};

class Inventory
{
	friend class Player;

private:
	class ItemProto*	inventoryItem[INVENTORY_SIZE];	// 인벤토리 아이템
	class UI*			inventoryIcon[INVENTORY_SIZE];	// 인벤토리 아이콘
	// 이미지===========================================================================================
	UI*					inventoryUI;						// 인벤토리 UI
	UI*					pannel;								// 인벤토리 패널을 가리킬 포인터
	UI*					slot[INVENTORY_SIZE + 1];			// 슬롯을 가리킬 포인터(0~31 알파슬롯, 32 블루슬롯)
	bool				isUse[INVENTORY_SIZE];				// 사용중인(장착중인) 슬롯 확인용
	// 아이템 조작===========================================================================================
	struct OnMouseItem
	{
		ItemProto*	item	{ nullptr };	// 마우스에 들고있는 아이템
		UI*			image	{ nullptr };	// 마우스에 들고있는 아이템 이미지
		int			index	{ -1 };			// 아이템의 슬롯 인덱스	
	};
	struct MouseLocation					// 아이템 드래그&드랍 위치 반환 구조체
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
	void ItemPickUp();
	void ItemDrop();
	void UseItem();
	Inventory::MouseLocation CheckMouseLocation();
	// ==================================================================================================
	void AddItem(ItemProto* item);
	void DeleteItem(string name);
	void ChangeItem();

};

