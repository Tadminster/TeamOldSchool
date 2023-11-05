#pragma once
class LivingItem : public Item
{
private:

protected:
	int      itemDurability = 0;


public:
	LivingItem();
	~LivingItem();

	virtual void CreateItem() override;
	virtual void EquipItem() override;
	virtual void DestroyItem() override;
	virtual void FixItem() override;

};

