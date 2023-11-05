#pragma once
#include "stdafx.h"
#include "Prototype.h"

enum class ItemState
{
	OnGround,
	OnInventory
};

class Item : public Prototype
{
protected:
	string    itemName;
	int        itemWeight =0;

public:
	Item();
	~Item();

	virtual void CreateItem() = 0;
	virtual void EquipItem() = 0;
	virtual void DestroyItem() = 0;
	virtual void FixItem() = 0;
};

