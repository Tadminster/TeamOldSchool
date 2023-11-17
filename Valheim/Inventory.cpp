#include "stdafx.h"
#include "ItemProto.h"
#include "Inventory.h"

Inventory::Inventory()
{
	// 모든 인벤토리를 nullptr로 초기화
	for (int i = 0; i < INVENTORY_SIZE; ++i)
	{
		inventoryItem[i] = nullptr;
		inventoryIcon[i] = nullptr;
		isUse[i] = false;
	}

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

	// Tab키를 누르면 인벤토리가 열림
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
		// 마우스 오버시 슬롯 강조
		MouseOverSlot();	

		// 아이템 사용
		UseItem();

		// 아이템 선택
		ItemPickUp();

		// 아이템 드랍
		ItemDrop();
	}

	// 단축키 입력으로 아이템 사용
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
	
	// 인벤토리가 열려있을 때, 마우스가 인벤토리 위에 있다면
	if (isOpen && pannel->MouseOver())
	{
		//	모든 인벤토리 슬롯을 순회
		for (int i = 0; i < 32; i++)
		{
			// 마우스가 해당 슬롯 위에 있고,
			if (slot[i]->MouseOver())
			{
				isMouseOver = true;
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
			// 인벤토리에 아이템이 있으면
			if (inventoryItem[i])
			{
				// 해당 슬롯의 아이템과 인덱스를 저장
				onMouse.item = inventoryItem[i];
				onMouse.image = inventoryIcon[i];
				onMouse.index = i;
			}
		}
	}
}

void Inventory::ItemDrop()
{
	// 픽업된 아이템이 있으면
	if (onMouse.item)
	{
		// 아이템의 아이콘이 마우스를 따라다님
		onMouse.image->SetWorldPos(Utility::MouseToNDC());

		// 픽업중에 마우스 오른쪽 버튼을 누르면 아이템이 원래 위치로 돌아감
		if (INPUT->KeyDown(VK_RBUTTON))
		{
			onMouse.item = nullptr;
			onMouse.image->SetWorldPos(slot[onMouse.index]->GetWorldPos());
			onMouse.image = nullptr;
			onMouse.index = -1;
		}

		// 픽업중에 마우스 왼쪽 버튼을 떼면
		if (INPUT->KeyUp(VK_LBUTTON))
		{
			Inventory::MouseLocation mLocation = CheckMouseLocation();

			if (mLocation.location == UILocation::OnSlot)
			{
				// 아이템을 드래그 중인 슬롯에 놓으면
				if (mLocation.index == onMouse.index)
				{
					// 아이콘이 원래 슬롯으로
					onMouse.item = nullptr;
					onMouse.image->SetWorldPos(slot[onMouse.index]->GetWorldPos());
					onMouse.image = nullptr;
					onMouse.index = -1;
				}
				// 아이템을 원래 슬롯이 아닌 다른 슬롯에 놓으면
				// 아이템을 다른 슬롯과 위치를 바꿈
				else
				{
					// 착용중인 아이템 인덱스 추적
					equippedItem.swap(onMouse.index, mLocation.index);

					// 다른 슬롯에 아이템이 있다면
					if (inventoryItem[mLocation.index])
					{
						// 슬롯 색상 변경
						{

							// 원래 슬롯은 아이템 사용중, 다른 슬롯은 아이템 사용중이 아님
							if (isUse[onMouse.index] && !isUse[mLocation.index])
							{
								// 원래슬롯은 일반슬롯으로 변경
								slot[onMouse.index]->material->LoadFile("Inventory/InventorySlot.mtl");
								isUse[onMouse.index] = false;

								// 다른슬롯은 블루슬롯으로 변경
								slot[mLocation.index]->material->LoadFile("Inventory/InventorySlotBlue.mtl");
								isUse[mLocation.index] = true;
							}
							// 원래 슬롯은 아이템 사용중이 아님, 다른 슬롯은 아이템 사용중
							else if (!isUse[onMouse.index] && isUse[mLocation.index])
							{
								// 원래슬롯은 블루슬롯으로 변경
								slot[onMouse.index]->material->LoadFile("Inventory/InventorySlotBlue.mtl");
								isUse[onMouse.index] = true;

								// 다른슬롯은 일반슬롯으로 변경
								slot[mLocation.index]->material->LoadFile("Inventory/InventorySlot.mtl");
								isUse[mLocation.index] = false;
							}

						}



						// 다른 슬롯의 아이템을 드래그 중인 슬롯으로 이동
						inventoryItem[onMouse.index] = inventoryItem[mLocation.index];
						inventoryIcon[onMouse.index] = inventoryIcon[mLocation.index];
						inventoryIcon[onMouse.index]->SetWorldPos(slot[onMouse.index]->GetWorldPos());
					}
					// 다른 슬롯에 아이템이 없다면 
					else
					{
						// 원래 슬롯이 사용중이었으면
						if (isUse[onMouse.index])
						{
							// 원래 슬롯은 일반슬롯으로, 다른 슬롯은 블루슬롯으로 변경
							slot[onMouse.index]->material->LoadFile("Inventory/InventorySlot.mtl");
							isUse[onMouse.index] = false;

							slot[mLocation.index]->material->LoadFile("Inventory/InventorySlotBlue.mtl");
							isUse[mLocation.index] = true;
						}

						// 원래 슬롯을 비움
						inventoryItem[onMouse.index] = nullptr;
						inventoryIcon[onMouse.index] = nullptr;
					}



					// 드래그 중인 아이템은 다른 슬롯으로 이동
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
				// 아이템을 원래 슬롯으로
				onMouse.item = nullptr;
				onMouse.image->SetWorldPos(slot[onMouse.index]->GetWorldPos());
				onMouse.image = nullptr;
				onMouse.index = -1;
			}
			else if (mLocation.location == UILocation::OnGround)
			{
				// 원래 슬롯을 비우고
				inventoryItem[onMouse.index] = nullptr;
				inventoryIcon[onMouse.index] = nullptr;

				// 버릴 아이템의 타입 체크
				ItemType type = onMouse.item->GetType();
				// 무기라면
				if (type == ItemType::Weapon)
				{
					// 지금 착용중인 무기인지 체크
					if (onMouse.index == equippedItem.Weapon)
					{
						// 인벤토리 정보 업데이트
						slot[equippedItem.Weapon]->material->LoadFile("Inventory/InventorySlot.mtl");
						isUse[equippedItem.Weapon] = false;
						equippedItem.Weapon = -1;

						// 장착 해제
						onMouse.item->Use();
					}
				}

				// 드래그 중인 아이템을 땅에 떨어뜨림
				onMouse.item->Drop();

				//  들고 있는 아이템 정보를 초기화
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
				// 인벤토리에 아이템이 있으면
				if (inventoryItem[i])
				{
					// 아이템 타입 체크
					ItemType type = inventoryItem[i]->GetType();
					if (type == ItemType::Weapon)
					{
						// 이전에 이미 착용중인 무기가 있으면
						if (equippedItem.Weapon != -1)
						{
							// 이전에 착용중이던 무기를 해제
							inventoryItem[equippedItem.Weapon]->Use();

							// 해당 슬롯을 원래 슬롯으로 변경
							slot[equippedItem.Weapon]->material->LoadFile("Inventory/InventorySlot.mtl");

							// 해당	슬롯을 사용중이 아니라고 표시
							isUse[equippedItem.Weapon] = false;
						}

						// 이전에 착용중인 무기가 자기 자신이면
						if (equippedItem.Weapon == i)
						{
							// 무기 인덱스 초기화
							equippedItem.Weapon = -1;
						}
						// 다른 무기라면
						else
						{
							// 새로운 무기를 착용
							inventoryItem[i]->Use();

							// 새로 착용한 무기슬롯을 블루슬롯으로 변경하고 인덱스 저장
							slot[i]->material->LoadFile("Inventory/InventorySlotBlue.mtl");

							// 해당	슬롯을 사용중이라고 표시
							isUse[i] = true;

							// 새로 착용한 무기 인덱스 저장
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
		// 인벤토리에 아이템이 있으면
		if (inventoryItem[shortcut])
		{
			// 아이템 타입 체크
			ItemType type = inventoryItem[shortcut]->GetType();
			if (type == ItemType::Weapon)
			{
				// 이전에 이미 착용중인 무기가 있으면
				if (equippedItem.Weapon != -1)
				{
					// 이전에 착용중이던 무기를 해제
					inventoryItem[equippedItem.Weapon]->Use();

					// 해당 슬롯을 원래 슬롯으로 변경
					slot[equippedItem.Weapon]->material->LoadFile("Inventory/InventorySlot.mtl");

					// 해당	슬롯을 사용중이 아니라고 표시
					isUse[equippedItem.Weapon] = false;
				}

				// 이전에 착용중인 무기가 자기 자신이면
				if (equippedItem.Weapon == shortcut)
				{
					equippedItem.Weapon = -1;
				}
				// 다른 무기라면
				else
				{
					// 아이템 착용
					inventoryItem[shortcut]->Use();

					// 인벤토리 데이터 업데이트
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
	// 마우스가 현재 위치를 구조체 생성
	Inventory::MouseLocation location;

	//	모든 인벤토리 슬롯을 순회
	for (int i = 0; i < 32; i++)
	{
		// 마우스가 슬롯 위에 있다면 false 반환
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
	// 아이템의 위치를 임시로 변경
	item->GetActor()->SetWorldPos(Vector3(0, -999, 0));
	item->Update();

	// 아이템의 상태를 인벤토리로 변경
	item->SetState(ItemState::OnInventory);

	// 인벤토리를 순회하며 빈 공간을 찾음
	for (int i = 0; i < INVENTORY_SIZE; ++i)
	{
		if (inventoryItem[i] == nullptr)
		{
			// 인벤토리에 아이템 추가
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