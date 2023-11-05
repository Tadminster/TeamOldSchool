#pragma once
class ResourceItem : public Item
{
private:

protected:
	

public:
	ResourceItem();
	~ResourceItem();

	virtual void CreateItem() override;
	virtual void EquipItem() override;
	virtual void DestroyItem() override;
	virtual void FixItem() override;
};

