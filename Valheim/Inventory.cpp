#include "stdafx.h"
#include "ItemProto.h"
#include "Inventory.h"

Inventory::Inventory()
{
	inventoryUI = UI::Create("InventoryUI");
	inventoryUI->LoadFile("InvenUI.xml");
}

Inventory::~Inventory()
{

}

void Inventory::Init()
{
}

void Inventory::Release()
{
}

void Inventory::Update()
{
	ImGui::Begin("Hierarchy");
	{
		inventoryUI->RenderHierarchy();
	}
	ImGui::End();

	if (INPUT->KeyDown(VK_TAB))
	{
		inventoryUI->Find("SlotBottom")->visible = !inventoryUI->Find("SlotBottom")->visible;
	}

	inventoryUI->Update();
}

void Inventory::LateUpdate()
{
	if (inventoryUI->Find("SlotBottom")->visible)
	{
		if (static_cast<UI*>(inventoryUI->Find("PANNEL"))->MouseOver())
		{
			for (int i = 1; i <= 32; i++)
			{
				string slotName;
				if (i < 10) slotName = "Slot0" + to_string(i);
				else slotName = "Slot" + to_string(i);

				if (static_cast<UI*>(inventoryUI->Find(slotName))->MouseOver())
				{
					cout << slotName << endl;
					//playerInventory->Find("itemSlot" + to_string(i))->material->LoadFile("mainSlotBlue.mtl");
				}
			}
		}
	}
}

void Inventory::PreRender()
{
}

void Inventory::Render()
{
	inventoryUI->Render();
}

void Inventory::ResizeScreen()
{
}

void Inventory::Add(ItemProto* item)
{
}

void Inventory::Delete(string name)
{
}

void Inventory::Change()
{
}
