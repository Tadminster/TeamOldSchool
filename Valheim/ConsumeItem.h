#pragma once
class ConsumeItem : public Item
{
protected:
	int      itemFreshness;
	int      itemHealthPoint;
	int      itemStaminaPoint;

public:
	ConsumeItem(const string itemName, const int itemNumber);
	~ConsumeItem();

	virtual void CreateItem() override;
	virtual void EquipItem() override;
	virtual void DestroyItem() override;
	virtual void FixItem() override;
};

