#pragma once

class Inventory
{
private:
	map<string, Item*> playerInventory;

public:
	Inventory();
	~Inventory();

	void AddItem(Item* item);
	void DeleteItem(string name);
	
};

