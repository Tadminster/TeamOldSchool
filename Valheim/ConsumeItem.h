#pragma once
class ConsumeItem : public Item
{
private:

protected:
	int      itemDurationTime;
	int      itemHealthPoint;
	int      itemStaminaPoint;

public:
	ConsumeItem();
	~ConsumeItem();

	virtual void CreateItem() override;
	virtual void EquipItem() override;
	virtual void DestroyItem() override;
	virtual void FixItem() override;
};

