#include "stdafx.h"
#include "ItemProto.h"
#include "Inventory.h"

Inventory::Inventory()
{
	// ��� �κ��丮�� nullptr�� �ʱ�ȭ
	for (int i = 0; i < INVENTORY_SIZE; i++)
	{
		inventoryItem[i] = nullptr;
		inventoryIcon[i] = nullptr;
		isUse[i] = false;
	}

	// �κ��丮 UI ���� �� �ε�
	inventoryUI = UI::Create("Inventory");
	inventoryUI->LoadFile("UI_Inventory.xml");
	tooltopBox = UI::Create("ToolTipBox");
	tooltopBox->LoadFile("UI_TooltipBox.xml");


	// �Ź� static_cast�� ������� �ʱ� ����, ����� UI���� �̸� ����
	panel = static_cast<UI*>(inventoryUI->Find("PANEL"));
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
	for (int i = 0; i < INVENTORY_SIZE; i++)
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
		tooltopBox->RenderHierarchy();
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

	for (auto icon : inventoryIcon)	
		if (icon) icon->Update();

	// �κ��丮 UI ������Ʈ
	inventoryUI->Update();
	
	// �κ��丮�� �������� ��
	if (isOpen)
	{
		// �����ڽ� ������Ʈ
		if (isOnTooltip)
		{
			tooltopBox->Update();
		}
	}

	static float InitTime = 4.5f;
	if (TIMER->GetTick(InitTime, 5.0f))
	{
		GM->ResizeScreen();

		// �κ��丮 ù��° ���� ���Ե� �ؽ�Ʈ ��ġ ������Ʈ
		for (int i = 0; i < INVENTORY_ROW_SIZE; i++)
		{
			// App.GetWidth() = ������ ��ġ�� NDC��ǥ��� ��ȯ
			// slot[i]->GetWorldPos().x + 1.0f) / 2.0f = ���� ��ġ(-1~1)�� (0~1)�� ��ȯ
			// - 30 ���� ��������� 30�ȼ� �̵�(����)
			text_number[i].left = App.GetHalfWidth() * (slot[i]->GetWorldPos().x + 1.0f) + text_numberCorrect;
			text_number[i].right = text_number[i].left + 1000;
			text_number[i].top = App.GetHalfHeight() * (1.0f - slot[i]->GetWorldPos().y) + text_numberCorrect;
			text_number[i].bottom = text_number[i].top + 200;
		}
	}
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


	for (int i = 0; i < INVENTORY_ROW_SIZE; i++)
	{
		DWRITE->RenderText(
			to_wstring(i+1),
			text_number[i],
			20.0f,
			L"Arial",
			Color(0.0f, 0.7f, 1.0f, 0.0f),
			DWRITE_FONT_WEIGHT_SEMI_BOLD,
			DWRITE_FONT_STYLE_ITALIC,
			DWRITE_FONT_STRETCH_EXPANDED);
	}

	if (isOpen)
	{
		for (auto icon : inventoryIcon)
			if (icon) icon->Render();

		// �����ڽ�
		if (isOnTooltip)
		{
			tooltopBox->Render();

			DWRITE->RenderText(
				Utility::ToWString(inventoryItem[onMouseItemIndex]->GetStringName()),
				text_itemName,
				20.0f,
				L"Arial",
				Color(1.0f, 0.8f, 0.0f, 0.0f),
				DWRITE_FONT_WEIGHT_SEMI_BOLD,
				DWRITE_FONT_STYLE_ITALIC,
				DWRITE_FONT_STRETCH_EXPANDED);

			DWRITE->RenderText(
				inventoryItem[onMouseItemIndex]->GetExplain(),
				text_itemExplain,
				15.0f,
				L"Arial",
				Color(1.0f, 1.0f, 1.0f, 0.0f),
				DWRITE_FONT_WEIGHT_SEMI_BOLD,
				DWRITE_FONT_STYLE_ITALIC,
				DWRITE_FONT_STRETCH_EXPANDED);
		}
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
	bool isMouseOverItem = false;
	
	// �κ��丮�� �������� ��, ���콺�� �κ��丮 ���� �ִٸ�
	if (isOpen && panel->MouseOver())
	{
		//	��� �κ��丮 ������ ��ȸ
		for (int i = 0; i < INVENTORY_SIZE; i++)
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

				// �ش罽�Կ� �������� �ִٸ�
				if (inventoryItem[i])
				{
					isMouseOverItem = true;

					float appHalfWidth = App.GetHalfWidth();
					float appHalfHeight = App.GetHalfHeight();
					float screenBaselineX = 650.0f;
					float screenBaselineY = 425.0;

					// ȭ�� ũ�⿡ ���� �����ڽ� ũ�� ������ ����ġ
					float screenRatioX = screenBaselineX / appHalfWidth;
					float screenRatioY = screenBaselineY / appHalfHeight;

					// �����ڽ� x, yũ�� ����
					tooltopBox->scale.x = screenRatioX;
					tooltopBox->scale.y = inventoryItem[i]->GetTooltipBoxScaleY() * screenRatioY;

					// ���� �ڽ��� ���콺 ��ġ�� �̵�
					tooltopBox->SetWorldPos(Utility::MouseToNDC());

					// ���� �ؽ�Ʈ ��ġ ����
					Vector3 tooptipPos = tooltopBox->GetWorldPos();

					text_itemName.left = appHalfWidth * (tooptipPos.x + 1) + 70;
					text_itemName.right = text_itemName.left + 1000;
					text_itemName.top = appHalfHeight * (1 - tooptipPos.y) + 10;
					text_itemName.bottom = text_itemName.top + 200;

					text_itemExplain.left = appHalfWidth * (tooptipPos.x + 1) + 10;
					text_itemExplain.right = text_itemExplain.left + 1000;
					text_itemExplain.top = appHalfHeight * (1 - tooptipPos.y) + 50;
					text_itemExplain.bottom = text_itemExplain.top + 200;

					// ���� �ڽ� visible
					onMouseItemIndex = i;
					tooltopBox->visible = true;
					isOnTooltip = true;
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
		onMouseItemIndex = -1;
		slot[BLUE_SLOT]->visible = false;
	}

	if (!isMouseOverItem)
	{
		tooltopBox->visible = false;
		isOnTooltip = false;
	}
}

void Inventory::ItemPickUp()
{
	for (int i = 0; i < INVENTORY_SIZE; i++)
	{
		if (INPUT->KeyDown(VK_LBUTTON) && slot[i]->MouseOver())
		{
			// �κ��丮�� �������� ������
			if (inventoryItem[i])
			{
				// �ش� ������ �����۰� �ε����� ����
				selectedItem.item = inventoryItem[i];
				selectedItem.image = inventoryIcon[i];
				selectedItem.index = i;
			}
		}
	}
}

void Inventory::ItemDrop()
{
	// �Ⱦ��� �������� ������
	if (selectedItem.item)
	{
		// �������� �������� ���콺�� ����ٴ�
		selectedItem.image->SetWorldPos(Utility::MouseToNDC());

		// �Ⱦ��߿� ���콺 ������ ��ư�� ������ �������� ���� ��ġ�� ���ư�
		if (INPUT->KeyDown(VK_RBUTTON))
		{
			selectedItem.item = nullptr;
			selectedItem.image->SetWorldPos(slot[selectedItem.index]->GetWorldPos());
			selectedItem.image = nullptr;
			selectedItem.index = -1;
		}

		// �Ⱦ��߿� ���콺 ���� ��ư�� ����
		if (INPUT->KeyUp(VK_LBUTTON))
		{
			Inventory::MouseLocation mLocation = CheckMouseLocation();

			if (mLocation.location == UILocation::OnSlot)
			{
				// �������� �巡�� ���� ���Կ� ������
				if (mLocation.index == selectedItem.index)
				{
					// �������� ���� ��������
					selectedItem.item = nullptr;
					selectedItem.image->SetWorldPos(slot[selectedItem.index]->GetWorldPos());
					selectedItem.image = nullptr;
					selectedItem.index = -1;
				}
				// �������� ���� ������ �ƴ� �ٸ� ���Կ� ������
				// �������� �ٸ� ���԰� ��ġ�� �ٲ�
				else
				{
					// �������� ������ �ε��� ����
					equippedItem.swap(selectedItem.index, mLocation.index);

					// �ٸ� ���Կ� �������� �ִٸ�
					if (inventoryItem[mLocation.index])
					{
						// ���� ���� ����
						{
							// ���� ������ ������ �����, �ٸ� ������ ������ ������� �ƴ�
							if (isUse[selectedItem.index] && !isUse[mLocation.index])
							{
								// ���������� �Ϲݽ������� ����
								slot[selectedItem.index]->material->LoadFile("Inventory/InventorySlot.mtl");
								isUse[selectedItem.index] = false;

								// �ٸ������� ��罽������ ����
								slot[mLocation.index]->material->LoadFile("Inventory/InventorySlotBlue.mtl");
								isUse[mLocation.index] = true;
							}
							// ���� ������ ������ ������� �ƴ�, �ٸ� ������ ������ �����
							else if (!isUse[selectedItem.index] && isUse[mLocation.index])
							{
								// ���������� ��罽������ ����
								slot[selectedItem.index]->material->LoadFile("Inventory/InventorySlotBlue.mtl");
								isUse[selectedItem.index] = true;

								// �ٸ������� �Ϲݽ������� ����
								slot[mLocation.index]->material->LoadFile("Inventory/InventorySlot.mtl");
								isUse[mLocation.index] = false;
							}

						}



						// �ٸ� ������ �������� �巡�� ���� �������� �̵�
						inventoryItem[selectedItem.index] = inventoryItem[mLocation.index];
						inventoryIcon[selectedItem.index] = inventoryIcon[mLocation.index];
						inventoryIcon[selectedItem.index]->SetWorldPos(slot[selectedItem.index]->GetWorldPos());
					}
					// �ٸ� ���Կ� �������� ���ٸ� 
					else
					{
						// ���� ������ ������̾�����
						if (isUse[selectedItem.index])
						{
							// ���� ������ �Ϲݽ�������, �ٸ� ������ ��罽������ ����
							slot[selectedItem.index]->material->LoadFile("Inventory/InventorySlot.mtl");
							isUse[selectedItem.index] = false;

							slot[mLocation.index]->material->LoadFile("Inventory/InventorySlotBlue.mtl");
							isUse[mLocation.index] = true;
						}

						// ���� ������ ���
						inventoryItem[selectedItem.index] = nullptr;
						inventoryIcon[selectedItem.index] = nullptr;
					}



					// �巡�� ���� �������� �ٸ� �������� �̵�
					inventoryItem[mLocation.index] = selectedItem.item;
					inventoryIcon[mLocation.index] = selectedItem.image;
					inventoryIcon[mLocation.index]->SetWorldPos(slot[mLocation.index]->GetWorldPos());

					selectedItem.item = nullptr;
					selectedItem.image = nullptr;
					selectedItem.index = -1;
				}
			}
			else if (mLocation.location == UILocation::OnPanel)
			{
				// �������� ���� ��������
				selectedItem.item = nullptr;
				selectedItem.image->SetWorldPos(slot[selectedItem.index]->GetWorldPos());
				selectedItem.image = nullptr;
				selectedItem.index = -1;
			}
			else if (mLocation.location == UILocation::OnGround)
			{
				// ���� ������ ����
				inventoryItem[selectedItem.index] = nullptr;
				inventoryIcon[selectedItem.index] = nullptr;

				// ���� �������� Ÿ�� üũ
				ItemType type = selectedItem.item->GetType();
				// ������
				if (type == ItemType::Weapon)
				{
					// ���� �������� �������� üũ
					if (selectedItem.index == equippedItem.Weapon)
					{
						// �κ��丮 ���� ������Ʈ
						slot[equippedItem.Weapon]->material->LoadFile("Inventory/InventorySlot.mtl");
						isUse[equippedItem.Weapon] = false;
						equippedItem.Weapon = -1;

						// ���� ����
						selectedItem.item->Use();
					}
				}

				// �巡�� ���� �������� ���� ����߸�
				selectedItem.item->Drop();

				//  ��� �ִ� ������ ������ �ʱ�ȭ
				selectedItem.item = nullptr;
				selectedItem.image = nullptr;
				selectedItem.index = -1;
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

	if (panel->MouseOver())
	{
		location.location = UILocation::OnPanel;
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
	// �������� ������ġ�� �ӽ÷� ����
	item->GetActor()->SetWorldPos(Vector3(0, -999, 0));
	item->Update();

	// �������� ���¸� �κ��丮�� ����
	item->SetState(ItemState::OnInventory);

	// �������� ��ø ������ Ÿ��(���, ����)�̸�
	if (item->GetType() == ItemType::Material || item->GetType() == ItemType::Food)
	{
		MaterialProto* mItem = dynamic_cast<MaterialProto*>(item);
		if (mItem)
		{
			// �κ��丮�� ��ü�� ��ȸ�ؼ� ���� �������� �ִ��� üũ
			for (int i = 0; i < INVENTORY_SIZE; i++)
			{
				if (inventoryItem[i] == nullptr)
				{
					continue;
				}
				else if (inventoryItem[i]->GetStringName() == mItem->GetStringName())
				{
					MaterialProto* targetItem = static_cast<MaterialProto*>(inventoryItem[i]);
					mItem->StackMerge(targetItem);
				}

				if (mItem->currentStack == 0)
				{
					return;
				}
			}
		}
	}
		
	// �κ��丮�� ��ȸ�ϸ� �� ������ ã��
	for (int i = 0; i < INVENTORY_SIZE; i++)
	{
		// �� ������ ã����
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

bool Inventory::CheckMaterial(Item item, int quantity)
{
	// �κ��丮�� ��ȸ�ؼ� ��ᰡ �ִ��� üũ
	for (int i = 0; i < INVENTORY_SIZE; i++)
	{

		// �������� �ְ�, ��� �̸��� ������
		if (inventoryItem[i] && inventoryItem[i]->GetEnumName() == item)
		{
			// Down Casting
			MaterialProto* material = dynamic_cast<MaterialProto*>(inventoryItem[i]);
			if (material)
			{
				// ����� ���� ��ø���� �ʿ��� �� �̻��̸� ����0���� ����
				if (material->currentStack >= quantity) quantity = 0;
				// ����� ���� ��ø���� �ʿ��� �� �̸��̸� �ʿ��� ������ ���� ��ø���� ��
				else quantity -= material->currentStack;
			}
		}

		// �ʿ��� ����� ���� 0���ϸ� true ��ȯ
		if (quantity <= 0) return true;
	}

	return false;
}

void Inventory::UseMaterial(Item item, int quantity)
{
	// �κ��丮�� ��ȸ�ؼ� ��ᰡ �ִ��� üũ
	for (int i = 0; i < INVENTORY_SIZE; i++)
	{
		// �������� �ְ�, ��� �̸��� ������
		if (inventoryItem[i] && inventoryItem[i]->GetEnumName() == item)
		{
			// Down Casting
			MaterialProto* material = dynamic_cast<MaterialProto*>(inventoryItem[i]);
			if (material)
			{
				// ����� ���� ��ø���� �ʿ��� �� �̻��̸�
				if (material->currentStack >= quantity)
				{
					// ����� ���� ��ø������ �ʿ��� ���� ��
					material->currentStack -= quantity;
					// �ʿ��� ���� 0���� ����
					quantity = 0;

					// ����� ���� ��ø���� 0�̸�
					if (material->currentStack == 0)
					{
						// �κ��丮���� ������ ����
						inventoryItem[i] = nullptr;
						inventoryIcon[i] = nullptr;
					}
				}
				// ����� ���� ��ø���� �ʿ��� �� �̸��̸�
				else
				{
					// �ʿ��� ������ ����� ���� ��ø���� ��
					quantity -= material->currentStack;
					// ����� ���� ��ø���� 0���� ����
					material->currentStack = 0;

					// �κ��丮���� ������ ����
					inventoryItem[i] = nullptr;
					inventoryIcon[i] = nullptr;
				}
			}
		}

		// �ʿ��� ����� ���� 0���ϸ� true ��ȯ
		if (quantity <= 0) return;
	}
}
