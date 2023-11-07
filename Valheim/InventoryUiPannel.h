#pragma once
class InventoryUiPannel : public Actor
{
private:

	UI* playerInventory;
	
protected:

public:
	InventoryUiPannel();
	~InventoryUiPannel();

	void Init();
	void Release();
	void Update();
	void LateUpdate() ;
	void PreRender();
	void Render();
	void ResizeScreen();

};

