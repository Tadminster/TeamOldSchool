#pragma once

class Inventory
{
	friend class Player;
private:
	vector<ItemProto*>	inventory;
	UI*					inventoryUI;

	UI*					pannel;
	UI*					slot[33];

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

	bool MouseOverSlot();

	void Add(ItemProto* item);
	void Delete(string name);
	void Change();
};

