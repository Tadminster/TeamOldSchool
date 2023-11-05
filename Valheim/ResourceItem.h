#pragma once
class ResourceItem : public Item
{
private:

protected:
	

public:
	ResourceItem();
	~ResourceItem();

	void CreateItem() override;
	void EquipItem() override;
	void DestroyItem() override;
	void FixItem() override;
};

