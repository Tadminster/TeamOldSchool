#pragma once
#define INVENTORY_SIZE	32		// �κ��丮 ũ��
#define	BLUE_SLOT		32		// ��罽���� �ε���

enum class UILocation
{
	OnSlot, OnPannel, OnGround
};

class Inventory
{
	friend class Player;

private:
	class ItemProto*	inventory[INVENTORY_SIZE];	// �κ��丮 (���� �������� ����ų)

	// �̹���===========================================================================================
	UI*					inventoryUI;				// �κ��丮 UI
	UI*					pannel;						// �κ��丮 �г��� ����ų ������
	UI*					slot[INVENTORY_SIZE + 1];	// ������ ����ų ������(0~31 ���Ľ���, 32 ��罽��)
	// ������ ����===========================================================================================
	struct OnMouseItem
	{
		ItemProto*	item	{ nullptr };	// ���콺�� ����ִ� ������
		UI*			image	{ nullptr };	// ���콺�� ����ִ� ������ �̹���
		int			index	{ -1 };			// �������� ���� �ε���	
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

