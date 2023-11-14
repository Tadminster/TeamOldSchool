#pragma once

class Inventory
{
	friend class Player;
private:
	map<string, ItemProto*> playerInventory;
	bool                     ItemIn = false;

protected:

public:
	Inventory();
	~Inventory();

	void AddItem(string name, ItemProto* item);
	void DeleteItem(string name);
	void SlotChange();
};

