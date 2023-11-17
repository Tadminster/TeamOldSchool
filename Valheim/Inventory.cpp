#include "stdafx.h"
#include "ItemProto.h"
#include "Inventory.h"

Inventory::Inventory()
{
	// ��� �κ��丮�� nullptr�� �ʱ�ȭ
	for (int i = 0; i < INVENTORY_SIZE; ++i)
	{
		inventoryItem[i] = nullptr;
		inventoryIcon[i] = nullptr;
		isUse[i] = false;
	}

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
	for (int i = 0; i < INVENTORY_SIZE; ++i)
	{
		slot[i]->visible = true;
	}
	slot[BLUE_SLOT]->visible = false;
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
		isOpen = !isOpen;

		if (isOpen) inventoryUI->Find("SlotBottom")->visible = true;
		else inventoryUI->Find("SlotBottom")->visible = false;

		Init();
	}

	inventoryUI->Update();
	for (auto icon : inventoryIcon)	
		if (icon) icon->Update();
}

void Inventory::LateUpdate()
{
	if (isOpen)
	{
		// ���콺 ������ ���� ����
		MouseOverSlot();	

		// ������ ���
		UseItem();

		// ������ ����
		ItemPickUp();

		// ������ ���
		ItemDrop();
	}

	// ����Ű �Է����� ������ ���
	InputShortcut();
}

void Inventory::PreRender()
{
}

void Inventory::Render()
{
	inventoryUI->Render();

	if (isOpen)
	{
		for (auto icon : inventoryIcon)
			if (icon) icon->Render();
	}
	else
	{
		for (int i = 0; i < INVENTORY_ROW_SIZE; i++ )
			if (inventoryIcon[i]) inventoryIcon[i]->Render();
	}
}

void Inventory::ResizeScreen()
{

}

void Inventory::MouseOverSlot()
{
	bool isMouseOver = false;
	
	// �κ��丮�� �������� ��, ���콺�� �κ��丮 ���� �ִٸ�
	if (isOpen && pannel->MouseOver())
	{
		//	��� �κ��丮 ������ ��ȸ
		for (int i = 0; i < 32; i++)
		{
			// ���콺�� �ش� ���� ���� �ְ�,
			if (slot[i]->MouseOver())
			{
				isMouseOver = true;
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

	if (!isMouseOver)
	{
		slot[BLUE_SLOT]->visible = false;
	}
}

void Inventory::ItemPickUp()
{
	for (int i = 0; i < 32; i++)
	{
		if (INPUT->KeyDown(VK_LBUTTON) && slot[i]->MouseOver())
		{
			// �κ��丮�� �������� ������
			if (inventoryItem[i])
			{
				// �ش� ������ �����۰� �ε����� ����
				onMouse.item = inventoryItem[i];
				onMouse.image = inventoryIcon[i];
				onMouse.index = i;
			}
		}
	}
}

void Inventory::ItemDrop()
{
	// �Ⱦ��� �������� ������
	if (onMouse.item)
	{
		// �������� �������� ���콺�� ����ٴ�
		onMouse.image->SetWorldPos(Utility::MouseToNDC());

		// �Ⱦ��߿� ���콺 ������ ��ư�� ������ �������� ���� ��ġ�� ���ư�
		if (INPUT->KeyDown(VK_RBUTTON))
		{
			onMouse.item = nullptr;
			onMouse.image->SetWorldPos(slot[onMouse.index]->GetWorldPos());
			onMouse.image = nullptr;
			onMouse.index = -1;
		}

		// �Ⱦ��߿� ���콺 ���� ��ư�� ����
		if (INPUT->KeyUp(VK_LBUTTON))
		{
			Inventory::MouseLocation mLocation = CheckMouseLocation();

			if (mLocation.location == UILocation::OnSlot)
			{
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
					// �������� ������ �ε��� ����
					equippedItem.swap(onMouse.index, mLocation.index);

					// �ٸ� ���Կ� �������� �ִٸ�
					if (inventoryItem[mLocation.index])
					{
						// ���� ���� ����
						{

							// ���� ������ ������ �����, �ٸ� ������ ������ ������� �ƴ�
							if (isUse[onMouse.index] && !isUse[mLocation.index])
							{
								// ���������� �Ϲݽ������� ����
								slot[onMouse.index]->material->LoadFile("Inventory/InventorySlot.mtl");
								isUse[onMouse.index] = false;

								// �ٸ������� ��罽������ ����
								slot[mLocation.index]->material->LoadFile("Inventory/InventorySlotBlue.mtl");
								isUse[mLocation.index] = true;
							}
							// ���� ������ ������ ������� �ƴ�, �ٸ� ������ ������ �����
							else if (!isUse[onMouse.index] && isUse[mLocation.index])
							{
								// ���������� ��罽������ ����
								slot[onMouse.index]->material->LoadFile("Inventory/InventorySlotBlue.mtl");
								isUse[onMouse.index] = true;

								// �ٸ������� �Ϲݽ������� ����
								slot[mLocation.index]->material->LoadFile("Inventory/InventorySlot.mtl");
								isUse[mLocation.index] = false;
							}

						}



						// �ٸ� ������ �������� �巡�� ���� �������� �̵�
						inventoryItem[onMouse.index] = inventoryItem[mLocation.index];
						inventoryIcon[onMouse.index] = inventoryIcon[mLocation.index];
						inventoryIcon[onMouse.index]->SetWorldPos(slot[onMouse.index]->GetWorldPos());
					}
					// �ٸ� ���Կ� �������� ���ٸ� 
					else
					{
						// ���� ������ ������̾�����
						if (isUse[onMouse.index])
						{
							// ���� ������ �Ϲݽ�������, �ٸ� ������ ��罽������ ����
							slot[onMouse.index]->material->LoadFile("Inventory/InventorySlot.mtl");
							isUse[onMouse.index] = false;

							slot[mLocation.index]->material->LoadFile("Inventory/InventorySlotBlue.mtl");
							isUse[mLocation.index] = true;
						}

						// ���� ������ ���
						inventoryItem[onMouse.index] = nullptr;
						inventoryIcon[onMouse.index] = nullptr;
					}



					// �巡�� ���� �������� �ٸ� �������� �̵�
					inventoryItem[mLocation.index] = onMouse.item;
					inventoryIcon[mLocation.index] = onMouse.image;
					inventoryIcon[mLocation.index]->SetWorldPos(slot[mLocation.index]->GetWorldPos());

					onMouse.item = nullptr;
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
				inventoryItem[onMouse.index] = nullptr;
				inventoryIcon[onMouse.index] = nullptr;

				// ���� �������� Ÿ�� üũ
				ItemType type = onMouse.item->GetType();
				// ������
				if (type == ItemType::Weapon)
				{
					// ���� �������� �������� üũ
					if (onMouse.index == equippedItem.Weapon)
					{
						// �κ��丮 ���� ������Ʈ
						slot[equippedItem.Weapon]->material->LoadFile("Inventory/InventorySlot.mtl");
						isUse[equippedItem.Weapon] = false;
						equippedItem.Weapon = -1;

						// ���� ����
						onMouse.item->Use();
					}
				}

				// �巡�� ���� �������� ���� ����߸�
				onMouse.item->Drop();

				//  ��� �ִ� ������ ������ �ʱ�ȭ
				onMouse.item = nullptr;
				onMouse.image = nullptr;
				onMouse.index = -1;
			}
		}
	}
}

void Inventory::UseItem(int shortcut)
{
	if (shortcut == 99)
	{
		for (int i = 0; i < 32; i++)
		{
			if (INPUT->KeyDown(VK_RBUTTON) && slot[i]->MouseOver())
			{
				// �κ��丮�� �������� ������
				if (inventoryItem[i])
				{
					// ������ Ÿ�� üũ
					ItemType type = inventoryItem[i]->GetType();
					if (type == ItemType::Weapon)
					{
						// ������ �̹� �������� ���Ⱑ ������
						if (equippedItem.Weapon != -1)
						{
							// ������ �������̴� ���⸦ ����
							inventoryItem[equippedItem.Weapon]->Use();

							// �ش� ������ ���� �������� ����
							slot[equippedItem.Weapon]->material->LoadFile("Inventory/InventorySlot.mtl");

							// �ش�	������ ������� �ƴ϶�� ǥ��
							isUse[equippedItem.Weapon] = false;
						}

						// ������ �������� ���Ⱑ �ڱ� �ڽ��̸�
						if (equippedItem.Weapon == i)
						{
							// ���� �ε��� �ʱ�ȭ
							equippedItem.Weapon = -1;
						}
						// �ٸ� ������
						else
						{
							// ���ο� ���⸦ ����
							inventoryItem[i]->Use();

							// ���� ������ ���⽽���� ��罽������ �����ϰ� �ε��� ����
							slot[i]->material->LoadFile("Inventory/InventorySlotBlue.mtl");

							// �ش�	������ ������̶�� ǥ��
							isUse[i] = true;

							// ���� ������ ���� �ε��� ����
							equippedItem.Weapon = i;
						}
					}
					else if (type == ItemType::Tool)
					{
						equippedItem.Weapon = i;
					}
					else if (type == ItemType::Armor)
					{
						equippedItem.Armor = i;
					}
				}
			}
		}
	}
	else
	{
		// �κ��丮�� �������� ������
		if (inventoryItem[shortcut])
		{
			// ������ Ÿ�� üũ
			ItemType type = inventoryItem[shortcut]->GetType();
			if (type == ItemType::Weapon)
			{
				// ������ �̹� �������� ���Ⱑ ������
				if (equippedItem.Weapon != -1)
				{
					// ������ �������̴� ���⸦ ����
					inventoryItem[equippedItem.Weapon]->Use();

					// �ش� ������ ���� �������� ����
					slot[equippedItem.Weapon]->material->LoadFile("Inventory/InventorySlot.mtl");

					// �ش�	������ ������� �ƴ϶�� ǥ��
					isUse[equippedItem.Weapon] = false;
				}

				// ������ �������� ���Ⱑ �ڱ� �ڽ��̸�
				if (equippedItem.Weapon == shortcut)
				{
					equippedItem.Weapon = -1;
				}
				// �ٸ� ������
				else
				{
					// ������ ����
					inventoryItem[shortcut]->Use();

					// �κ��丮 ������ ������Ʈ
					slot[shortcut]->material->LoadFile("Inventory/InventorySlotBlue.mtl");
					equippedItem.Weapon = shortcut;
					isUse[shortcut] = true;
				}
			}
			else if (type == ItemType::Tool)
			{
				equippedItem.Weapon = shortcut;
			}
			else if (type == ItemType::Armor)
			{
				equippedItem.Armor = shortcut;
			}
		}
	}

}

void Inventory::InputShortcut()
{
	if (INPUT->KeyDown('1')) UseItem(0);
	else if (INPUT->KeyDown('2')) UseItem(1);
	else if (INPUT->KeyDown('3')) UseItem(2);
	else if (INPUT->KeyDown('4')) UseItem(3);
	else if (INPUT->KeyDown('5')) UseItem(4);
	else if (INPUT->KeyDown('6')) UseItem(5);
	else if (INPUT->KeyDown('7')) UseItem(6);
	else if (INPUT->KeyDown('8')) UseItem(7);
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
		if (inventoryItem[i] == nullptr)
		{
			// �κ��丮�� ������ �߰�
			inventoryItem[i] = item;
			inventoryIcon[i] = item->GetIcon();
			inventoryIcon[i]->SetWorldPos(slot[i]->GetWorldPos());
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