#pragma once
class ConsumeItem : public Item
{
private:

protected:
	int      itemDurationTime =0;
	int      itemHealthPoint = 0;
	int      itemStaminaPoint = 0;

public:
	ConsumeItem();
	~ConsumeItem();

	void CreateItem() override;
	void EquipItem() override;
	void DestroyItem() override;
	void FixItem() override;
};

