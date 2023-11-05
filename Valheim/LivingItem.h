#pragma once
class LivingItem : public Item
{
private:

protected:
	int      itemDurability = 0;


public:
	LivingItem();
	~LivingItem();

	void CreateItem() override;
	void EquipItem() override;
	void DestroyItem() override;
	void FixItem() override;

};

