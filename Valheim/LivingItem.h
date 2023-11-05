#pragma once
class LivingItem : public Item
{
protected:
	int      itemDurability;


public:
	LivingItem();
	~LivingItem();

	virtual void CreateItem() override;
	virtual void EquipItem() override;
	virtual void DestroyItem() override;
	virtual void FixItem() override;

};

