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

	for (int i = 0; i < 32; i++)
	{
		if (INPUT->KeyDown(VK_LBUTTON) && slot[i]->MouseOver())
		{
			// 인벤토리에 아이템이 있으면
			if (inventory[i])
			{
				cout << "아이템 집기" << endl;
				// 해당 슬롯의 아이템과 인덱스를 저장
				onMouse.item = inventory[i];
				onMouse.image = inventory[i]->GetIcon();
				onMouse.index = i;
			}
		}
	}

	// 클릭된 아이템이 있으면
	if (onMouse.item)
	{
		// 아이템의 아이콘이 마우스를 따라다님
		onMouse.image->SetWorldPos(Utility::MouseToNDC());

		// 마우스 오른쪽 버튼을 누르면 아이템이 원래 위치로 돌아감
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
					cout << "슬롯 변경" << endl;
					// 다른 슬롯에 아이템이 있다면
					if (inventory[mLocation.index])
					{
						// 다른 슬롯의 아이템을 드래그 중인 슬롯으로 이동
						inventory[onMouse.index] = inventory[mLocation.index];
						inventory[onMouse.index]->GetIcon()->SetWorldPos(slot[onMouse.index]->GetWorldPos());
					}
					// 다른 슬롯에 아이템이 없다면 원래 슬롯을 비움
					else
					{
						inventory[onMouse.index] = nullptr;
					}

					// 드래그 중인 아이템은 다른 슬롯으로 이동
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
				// 아이템을 원래 슬롯으로
				onMouse.item = nullptr;
				onMouse.image->SetWorldPos(slot[onMouse.index]->GetWorldPos());
				onMouse.image = nullptr;
				onMouse.index = -1;
			}
			else if (mLocation.location == UILocation::OnGround)
			{
				// 원래 슬롯을 비우고
				inventory[onMouse.index] = nullptr;
				
				// 아이템을 마우스 위치로 이동
				Ray tempRay; Vector3 rayHitPoint;
				tempRay.position = PLAYER->GetActor()->GetWorldPos() + PLAYER->GetActor()->GetForward() * 2 + PLAYER->GetActor()->GetUp() * 100;
				tempRay.direction = Vector3(0.0f, -1.0f, 0.f);
				if (Utility::RayIntersectMap(tempRay, MAP, rayHitPoint))
				{
					onMouse.item->GetActor()->SetWorldPos(rayHitPoint + Vector3(0, 0.5f, 0));
				}
				
				// 아이템의 상태를 OnGround로 변경
				onMouse.item->SetState(ItemState::OnGround);

				//  들고 있는 아이템 정보를 초기화
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
	// 인벤토리가 열려있을 때, 마우스가 인벤토리 위에 있다면
	if (inventoryUI->Find("SlotBottom")->visible && pannel->MouseOver())
	{
		//	모든 인벤토리 슬롯을 순회
		for (int i = 0; i < 32; i++)
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
		if (inventory[i] == nullptr)
		{
			// 인벤토리에 아이템 추가
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