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

	virtual void CreateItem() override;
	virtual void EquipItem() override;
	virtual void DestroyItem() override;
	virtual void FixItem() override;
};

