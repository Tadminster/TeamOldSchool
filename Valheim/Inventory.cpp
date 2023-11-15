#include "stdafx.h"
#include "ItemProto.h"
#include "Inventory.h"

Inventory::Inventory()
{
	// 모든 인벤토리를 nullptr로 초기화
	for (int i = 0; i < INVENTORY_SIZE; ++i)
		inventory[i] = nullptr;

	// 인벤토리 UI 생성 및 로드
	inventoryUI = UI::Create("InventoryUI");
	inventoryUI->LoadFile("InvenUI.xml");

	// 매번 static_cast를 사용하지 않기 위해, 사용할 UI들을 미리 저장
	pannel = static_cast<UI*>(inventoryUI->Find("PANNEL"));
	for (int i = 1; i <= 32; i++)
	{
		string slotName;
		if (i < 10) slotName = "Slot0" + to_string(i);
		else slotName = "Slot" + to_string(i);

		slot[i - 1] = static_cast<UI*>(inventoryUI->Find(slotName));
	}
	slot[BLUE_SLOT] = static_cast<UI*>(inventoryUI->Find("Slot99"));
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

	// Tab키를 누르면 인벤토리가 열림
	if (INPUT->KeyDown(VK_TAB))
	{
		inventoryUI->Find("SlotBottom")->visible = !inventoryUI->Find("SlotBottom")->visible;
	}

	inventoryUI->Update();
}

void Inventory::LateUpdate()
{
	// 마우스 오버시 슬롯 강조
	MouseOverSlot();
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

void Inventory::MouseOverSlot()
{
	// 인벤토리가 열려있을 때, 마우스가 인벤토리 위에 있다면
	if (inventoryUI->Find("SlotBottom")->visible && pannel->MouseOver())
	{
		//	모든 인벤토리 슬롯을 순회
		for (int i = 0; i <= 31; i++)
		{
			// 마우스가 해당 슬롯 위에 있고,
			if (slot[i]->MouseOver())
			{
				// 해당슬롯이 visible이라면
				if (slot[i]->visible)
				{
					// 블루슬롯을 해당 슬롯 위치로 이동
					slot[BLUE_SLOT]->SetLocalPos(slot[i]->GetLocalPos());
					// 블루슬롯 visible, 해당 슬롯 invisible
					slot[BLUE_SLOT]->visible = true;
					slot[i]->visible = false;
				}
			}
			// 마우스가 해당 슬롯 위에 없다면 해당슬롯 visible
			else slot[i]->visible = true;
		}
	}
	else
	{
		slot[BLUE_SLOT]->visible = false;
	}
}

void Inventory::AddItem(ItemProto* item)
{
	// 인벤토리를 순회하며 빈 공간을 찾음
	for (int i = 0; i < INVENTORY_SIZE; ++i)
	{
		if (inventory[i] == nullptr)
		{
			// 인벤토리에 아이템 추가
			inventory[i] = item;
			item->GetIcon()->SetWorldPos(slot[i]->GetWorldPos());
			break;
		}
	}

	// 아이템의 상태를 인벤토리로 변경
	item->SetState(ItemState::OnInventory);
}

void Inventory::DeleteItem(string name)
{
}

void Inventory::ChangeItem()
{
}