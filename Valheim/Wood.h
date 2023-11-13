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

	// ResourceItem을(를) 통해 상속됨
	void Init() override;
	void Update() override;
	void LateUpdate() override;
	void Render() override;
	void Release() override;
	void RenderHierarchy() override;

	// ResourceItem을(를) 통해 상속됨
	bool IsDestroyed() override;
	void DestructionEvent() override;
};

