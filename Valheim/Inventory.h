#pragma once
#include "ItemProto.h"
#define INVENTORY_SIZE		32		// 인벤토리 크기
#define INVENTORY_ROW_SIZE	8		// 인벤토리 1줄 크기
#define	BLUE_SLOT			32		// 블루슬롯의 인덱스


enum class UILocation
{
	OnSlot, OnPanel, OnGround
};

class Inventory
{
	friend class Player;

private:
	// 실제 아이템과 아이콘=============================================================================
	class ItemProto*	inventoryItem[INVENTORY_SIZE];		// 인벤토리 아이템
	class UI*			inventoryIcon[INVENTORY_SIZE];		// 인벤토리 아이콘
	// 이미지===========================================================================================
	UI*					inventoryUI;						// 인벤토리 UI
	UI*					panel;								// 인벤토리 패널을 가리킬 포인터
	UI*					slot[INVENTORY_SIZE + 1];			// 슬롯을 가리킬 포인터(0~31 일반슬롯, 32 블루슬롯)
	UI*					tooltopBox;							// 툴팁 박스(검은 배경)
	RECT				text_itemName;						// 툴팁 박스(아이템 이름)
	RECT				text_itemExplain;					// 툴팁 박스(아이템 설명)
	RECT				text_number[INVENTORY_ROW_SIZE];	// 첫 줄의 슬롯들 숫자를 표시할 텍스트 영역
	// 아이템 조작======================================================================================
	bool			    isUse[INVENTORY_SIZE];				// 아이템 사용 여부
	bool				isOnTooltip;						// 아이템 툴팁 표시 여부
	struct EquippedItem						// 착용중인 아이템 인덱스 저장 구조체
	{
		int		Weapon{ -1 };
		int     Shield{ -1 };
		int		Armor{ -1 };
		int* array[3]{ &Weapon, &Shield, &Armor, };

		void IndexSwap(int& index_x, int& index_y)
		{
			int* matchX = nullptr;		// index_x와 일치하는 변수의 포인터
			int* matchY = nullptr;		// index_y와 일치하는 변수의 포인터

			// 각 인덱스와 일치하는 변수 찾기
			for (int i = 0; i < 3; i++)
			{
				if (*(array[i]) == index_x)
					matchX = array[i];

				if (*(array[i]) == index_y)
					matchY = array[i];
			}

			// 교환 또는 변경
			// 두 변수 모두 일치하는 경우 서로 교환
			if (matchX && matchY) swap(*matchX, *matchY);
			else if (matchX) *matchX = index_y;		// index_x만 일치하는 경우
			else if (matchY) *matchY = index_x;		// index_y만 일치하는 경우
		}
	};
	struct SelectedItem						// 마우스에 들고있는 아이템 tracking 구조체
	{
		ItemProto* item{ nullptr };			// 마우스에 들고있는 아이템
		UI* image{ nullptr };				// 마우스에 들고있는 아이템 이미지
		int			index{ -1 };			// 아이템의 슬롯 인덱스	
	};
	struct MouseLocation					// 아이템 드래그&드랍 위치 반환 구조체
	{
		UILocation	location;
		int			index{ -1 };
	};
	SelectedItem	selectedItem;			// 마우스에 들고있는 아이템 tracking
	EquippedItem	equippedItem;			// 착용중인 아이템 tracking
	int             onMouseItemIndex{ -1 };	// 마우스가 위치한 아이템 인덱스

public:
	bool 		isOpen{ false };			// 인벤토리가 열려있는지 여부

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
	void CheckItem(int shortcut = 99);
	void UseItem(int& equippedItem, int inventoryIndex);
	void InputShortcut();
	Inventory::MouseLocation CheckMouseLocation();
	// ==================================================================================================
	void AddItem(ItemProto* item);
	void DeleteItem(string name);
	void ChangeItem();

	bool CheckMaterial(Item item, int quantity);
	void UseMaterial(Item item, int quantity);

};

