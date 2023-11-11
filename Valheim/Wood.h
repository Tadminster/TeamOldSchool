#pragma once
class Wood : public ResourceItem
{
private:

protected:

public:
	
	explicit Wood(Vector3 spwanpos = Vector3());
   	~Wood();


	void CreateItem() override;
	void EquipItem() override;
	void DestroyItem() override;
	void FixItem() override;

	// ResourceItem��(��) ���� ��ӵ�
	void Init() override;
	void Update() override;
	void LateUpdate() override;
	void Render() override;

};

