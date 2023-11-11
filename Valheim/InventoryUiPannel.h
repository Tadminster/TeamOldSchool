#pragma once

class InventoryUiPannel : public Actor
{
private:
	
	UI* playerInventory;

	UI* stoneImg;
	UI* woodImg;

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

