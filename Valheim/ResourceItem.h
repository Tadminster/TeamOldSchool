#pragma once
class ResourceItem : public Item
{
protected:
	

public:
	ResourceItem(const string itemName, const int itemNumber);
	~ResourceItem();

	virtual void CreateItem() override;
	virtual void EquipItem() override;
	virtual void DestroyItem() override;
	virtual void FixItem() override;
};

