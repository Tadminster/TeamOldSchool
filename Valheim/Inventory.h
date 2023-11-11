#pragma once

class Inventory
{
	friend class Player;
private:
	map<string, Item*> playerInventory;
	bool                     ItemIn = false;

protected:

public:
	Inventory();
	~Inventory();

	void AddItem(string name, Item* item);
	void DeleteItem(string name);
	void SlotChange();
};

