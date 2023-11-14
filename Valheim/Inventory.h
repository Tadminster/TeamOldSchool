#pragma once

class Inventory
{
	friend class Player;
private:
	vector<ItemProto*>	inventory;
	UI*					inventoryUI;

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

	void Add(ItemProto* item);
	void Delete(string name);
	void Change();
};

