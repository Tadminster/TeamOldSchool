#pragma once

enum class ItemState
{
	OnGround,
	OnInventory
};

class Item
{
protected:
	string    itemName;
	int        itemNumber;
	int        itemWeight;

public:
	Item(const string itemName, const int itemNumber);
	~Item();

	virtual void CreateItem() = 0;
	virtual void EquipItem() = 0;
	virtual void DestroyItem() = 0;
	virtual void FixItem() = 0;
};

