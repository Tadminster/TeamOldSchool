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
	class ItemProto*	inventoryItem[INVENTORY_SIZE];	// �κ��丮 ������
	class UI*			inventoryIcon[INVENTORY_SIZE];	// �κ��丮 ������
	// �̹���===========================================================================================
	UI*					inventoryUI;						// �κ��丮 UI
	UI*					pannel;								// �κ��丮 �г��� ����ų ������
	UI*					slot[INVENTORY_SIZE + 1];			// ������ ����ų ������(0~31 ���Ľ���, 32 ��罽��)
	bool				isUse[INVENTORY_SIZE];				// �������(��������) ���� Ȯ�ο�
	// ������ ����===========================================================================================
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

