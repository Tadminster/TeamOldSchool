#pragma once
class BattleItem : public Item
{
private:

protected:
	int      itemDurability =0;
	int      itemDamage = 0;

public:
	BattleItem();
	~BattleItem();

	void CreateItem() override;
	void EquipItem() override;
	void DestroyItem() override;
	void FixItem() override;
};

