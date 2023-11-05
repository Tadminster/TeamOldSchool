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

	virtual void CreateItem() override;
	virtual void EquipItem() override;
	virtual void DestroyItem() override;
	virtual void FixItem() override;
};

