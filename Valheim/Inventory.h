#pragma once
class Inventory
{
private:
	map<string, Item*> playerInventory;

public:
	void AddItem(Item* item);
	void DeleteItem(string name);
	
};

