#include "stdafx.h"
#include "ItemProto.h"
#include "Inventory.h"

Inventory::Inventory()
{
	// ��� �κ��丮�� nullptr�� �ʱ�ȭ
	for (int i = 0; i < INVENTORY_SIZE; ++i)
		inventory[i] = nullptr;

	// �κ��丮 UI ���� �� �ε�
	inventoryUI = UI::Create("InventoryUI");
	inventoryUI->LoadFile("InvenUI.xml");

	// �Ź� static_cast�� ������� �ʱ� ����, ����� UI���� �̸� ����
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

	// TabŰ�� ������ �κ��丮�� ����
	if (INPUT->KeyDown(VK_TAB))
	{
		inventoryUI->Find("SlotBottom")->visible = !inventoryUI->Find("SlotBottom")->visible;
	}

	inventoryUI->Update();
}

void Inventory::LateUpdate()
{
	// ���콺 ������ ���� ����
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
	// �κ��丮�� �������� ��, ���콺�� �κ��丮 ���� �ִٸ�
	if (inventoryUI->Find("SlotBottom")->visible && pannel->MouseOver())
	{
		//	��� �κ��丮 ������ ��ȸ
		for (int i = 0; i <= 31; i++)
		{
			// ���콺�� �ش� ���� ���� �ְ�,
			if (slot[i]->MouseOver())
			{
				// �ش罽���� visible�̶��
				if (slot[i]->visible)
				{
					// ��罽���� �ش� ���� ��ġ�� �̵�
					slot[BLUE_SLOT]->SetLocalPos(slot[i]->GetLocalPos());
					// ��罽�� visible, �ش� ���� invisible
					slot[BLUE_SLOT]->visible = true;
					slot[i]->visible = false;
				}
			}
			// ���콺�� �ش� ���� ���� ���ٸ� �ش罽�� visible
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
	// �κ��丮�� ��ȸ�ϸ� �� ������ ã��
	for (int i = 0; i < INVENTORY_SIZE; ++i)
	{
		if (inventory[i] == nullptr)
		{
			// �κ��丮�� ������ �߰�
			inventory[i] = item;
			item->GetIcon()->SetWorldPos(slot[i]->GetWorldPos());
			break;
		}
	}

	// �������� ���¸� �κ��丮�� ����
	item->SetState(ItemState::OnInventory);
}

void Inventory::DeleteItem(string name)
{
}

void Inventory::ChangeItem()
{
}