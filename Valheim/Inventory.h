#pragma once
#define INVENTORY_SIZE 32

class Inventory
{
	friend class Player;

private:
	ItemProto*			inventory[INVENTORY_SIZE];	// �κ��丮 (���� �������� ����ų)

	// �̹���===========================================================================================
	UI*					inventoryUI;				// �κ��丮 UI
	UI*					pannel;						// �κ��丮 �г��� ����ų ������
	UI*					slot[INVENTORY_SIZE + 1];	// ������ ����ų ������(0~31 ���Ľ���, 32 ��罽��)

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

	void MouseOverSlot();

	void AddItem(ItemProto* item);
	void DeleteItem(string name);
	void ChangeItem();

};

