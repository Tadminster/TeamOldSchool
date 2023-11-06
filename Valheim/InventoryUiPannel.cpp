#include "stdafx.h"
#include "InventoryUiPannel.h"

InventoryUiPannel::InventoryUiPannel()
{
	InventoryUI->Create("PlayerInventory");
	InventoryUI->type = ObType::UI;
}

InventoryUiPannel::~InventoryUiPannel()
{

}
