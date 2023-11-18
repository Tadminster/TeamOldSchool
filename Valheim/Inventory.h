#pragma once
#define INVENTORY_SIZE		32		// �κ��丮 ũ��
#define INVENTORY_ROW_SIZE	8		// �κ��丮 1�� ũ��
#define	BLUE_SLOT			32		// ��罽���� �ε���

enum class UILocation
{
	OnSlot, OnPannel, OnGround
};

class Inventory
{
	friend class Player;

private:
	// ���� �����۰� ������===========================================================================================
	class ItemProto*	inventoryItem[INVENTORY_SIZE];	// �κ��丮 ������
	class UI*			inventoryIcon[INVENTORY_SIZE];	// �κ��丮 ������
	// �̹���===========================================================================================
	UI*					inventoryUI;						// �κ��丮 UI
	UI*					pannel;								// �κ��丮 �г��� ����ų ������
	UI*					slot[INVENTORY_SIZE + 1];			// ������ ����ų ������(0~31 �Ϲݽ���, 32 ��罽��)
	RECT				text_number[INVENTORY_ROW_SIZE];	// ù ���� ���Ե� ���ڸ� ǥ���� �ؽ�Ʈ ����
	// ������ ����===========================================================================================
	bool			    isUse[INVENTORY_SIZE];				// ������ ��� ����
	struct EquippedItem						// �������� ������ �ε��� ���� ����ü
	{
		int		Weapon		{ -1 };
		int		Armor		{ -1 };
		int*    array[2]	{ &Weapon, &Armor };

		void swap(int index_x, int index_y)
		{
			int* matchX = nullptr;		// index_x�� ��ġ�ϴ� ������ ������
			int* matchY = nullptr;		// index_y�� ��ġ�ϴ� ������ ������

			// �� �ε����� ��ġ�ϴ� ���� ã��
			for (int i = 0; i < 2; ++i)
			{
				if (*(array[i]) == index_x)
					matchX = array[i];

				if (*(array[i]) == index_y)
					matchY = array[i];
			}

			// ��ȯ �Ǵ� ����
			// �� ���� ��� ��ġ�ϴ� ��� ���� ��ȯ
			if (matchX && matchY) swap(*matchX, *matchY);
			else if (matchX) *matchX = index_y;		// index_x�� ��ġ�ϴ� ���
			else if (matchY) *matchY = index_x;		// index_y�� ��ġ�ϴ� ���
		}
	};
	struct OnMouseItem
	{
		ItemProto*	item	{ nullptr };	// ���콺�� ����ִ� ������
		UI*			image	{ nullptr };	// ���콺�� ����ִ� ������ �̹���
		int			index	{ -1 };			// �������� ���� �ε���	
	};
	struct MouseLocation					// ������ �巡��&��� ��ġ ��ȯ ����ü
	{
		UILocation	location;
		int			index	{ -1 };
	};
	OnMouseItem		onMouse;
	EquippedItem	equippedItem;

public:
	bool 		isOpen	{ false };			// �κ��丮�� �����ִ��� ����

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
	void UseItem(int shortcut = 99);
	void InputShortcut();
	Inventory::MouseLocation CheckMouseLocation();
	// ==================================================================================================
	void AddItem(ItemProto* item);
	void DeleteItem(string name);
	void ChangeItem();

};

