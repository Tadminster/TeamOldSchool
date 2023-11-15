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

	for (int i = 0; i < 32; i++)
	{
		if (INPUT->KeyDown(VK_LBUTTON) && slot[i]->MouseOver())
		{
			// �κ��丮�� �������� ������
			if (inventory[i])
			{
				cout << "������ ����" << endl;
				// �ش� ������ �����۰� �ε����� ����
				onMouse.item = inventory[i];
				onMouse.image = inventory[i]->GetIcon();
				onMouse.index = i;
			}
		}
	}

	// Ŭ���� �������� ������
	if (onMouse.item)
	{
		// �������� �������� ���콺�� ����ٴ�
		onMouse.image->SetWorldPos(Utility::MouseToNDC());

		// ���콺 ������ ��ư�� ������ �������� ���� ��ġ�� ���ư�
		if (INPUT->KeyDown(VK_RBUTTON))
		{
			onMouse.item = nullptr;
			onMouse.image->SetWorldPos(slot[onMouse.index]->GetWorldPos());
			onMouse.image = nullptr;
			onMouse.index = -1;
		}

		if (INPUT->KeyUp(VK_LBUTTON))
		{
			Inventory::MouseLocation mLocation = CheckMouseLocation();

			if (mLocation.location == UILocation::OnSlot)
			{
				cout << "OnSlot, " << mLocation.index << endl;
				// �������� �巡�� ���� ���Կ� ������
				if (mLocation.index == onMouse.index)
				{
					// �������� ���� ��������
					onMouse.item = nullptr;
					onMouse.image->SetWorldPos(slot[onMouse.index]->GetWorldPos());
					onMouse.image = nullptr;
					onMouse.index = -1;
				}
				// �������� ���� ������ �ƴ� �ٸ� ���Կ� ������
				// �������� �ٸ� ���԰� ��ġ�� �ٲ�
				else
				{
					cout << "���� ����" << endl;
					// �ٸ� ���Կ� �������� �ִٸ�
					if (inventory[mLocation.index])
					{
						// �ٸ� ������ �������� �巡�� ���� �������� �̵�
						inventory[onMouse.index] = inventory[mLocation.index];
						inventory[onMouse.index]->GetIcon()->SetWorldPos(slot[onMouse.index]->GetWorldPos());
					}
					// �ٸ� ���Կ� �������� ���ٸ� ���� ������ ���
					else
					{
						inventory[onMouse.index] = nullptr;
					}

					// �巡�� ���� �������� �ٸ� �������� �̵�
					inventory[mLocation.index] = onMouse.item;
					inventory[mLocation.index]->GetIcon()->SetWorldPos(slot[mLocation.index]->GetWorldPos());

					onMouse.item = nullptr;
					//onMouse.image->SetWorldPos(slot[mLocation.index]->GetWorldPos());
					onMouse.image = nullptr;
					onMouse.index = -1;
				}
			}
			else if (mLocation.location == UILocation::OnPannel)
			{
				// �������� ���� ��������
				onMouse.item = nullptr;
				onMouse.image->SetWorldPos(slot[onMouse.index]->GetWorldPos());
				onMouse.image = nullptr;
				onMouse.index = -1;
			}
			else if (mLocation.location == UILocation::OnGround)
			{
				// ���� ������ ����
				inventory[onMouse.index] = nullptr;
				
				// �������� ���콺 ��ġ�� �̵�
				Ray tempRay; Vector3 rayHitPoint;
				tempRay.position = PLAYER->GetActor()->GetWorldPos() + PLAYER->GetActor()->GetForward() * 2 + PLAYER->GetActor()->GetUp() * 100;
				tempRay.direction = Vector3(0.0f, -1.0f, 0.f);
				if (Utility::RayIntersectMap(tempRay, MAP, rayHitPoint))
				{
					onMouse.item->GetActor()->SetWorldPos(rayHitPoint + Vector3(0, 0.5f, 0));
				}
				
				// �������� ���¸� OnGround�� ����
				onMouse.item->SetState(ItemState::OnGround);

				//  ��� �ִ� ������ ������ �ʱ�ȭ
				onMouse.item = nullptr;
				onMouse.image = nullptr;
				onMouse.index = -1;
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

void Inventory::MouseOverSlot()
{
	// �κ��丮�� �������� ��, ���콺�� �κ��丮 ���� �ִٸ�
	if (inventoryUI->Find("SlotBottom")->visible && pannel->MouseOver())
	{
		//	��� �κ��丮 ������ ��ȸ
		for (int i = 0; i < 32; i++)
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

Inventory::MouseLocation Inventory::CheckMouseLocation()
{
	// ���콺�� ���� ��ġ�� ����ü ����
	Inventory::MouseLocation location;

	//	��� �κ��丮 ������ ��ȸ
	for (int i = 0; i < 32; i++)
	{
		// ���콺�� ���� ���� �ִٸ� false ��ȯ
		if (slot[i]->MouseOver())
		{
			location.location = UILocation::OnSlot;
			location.index = i;
			return location;
		}
	}

	if (pannel->MouseOver())
	{
		location.location = UILocation::OnPannel;
		return location;
	}
	else
	{
		location.location = UILocation::OnGround;
		return location;
	}
}

void Inventory::AddItem(ItemProto* item)
{
	// �������� ��ġ�� �ӽ÷� ����
	item->GetActor()->SetWorldPos(Vector3(0, -999, 0));
	item->Update();

	// �������� ���¸� �κ��丮�� ����
	item->SetState(ItemState::OnInventory);

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
}

void Inventory::DeleteItem(string name)
{
}

void Inventory::ChangeItem()
{
}