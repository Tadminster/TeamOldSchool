#pragma once
class BattleItem : public Item
{
protected:
	int      itemDurability;
	

public:
	BattleItem(const string itemName, const int itemNumber);
	~BattleItem();

	virtual void CreateItem() override;
	virtual void EquipItem() override;
	virtual void DestroyItem() override;
	virtual void FixItem() override;
};

