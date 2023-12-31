#include "stdafx.h"
#include "ItemProto.h"
#include "Inventory.h"

Inventory::Inventory()
{
	// 모든 인벤토리를 nullptr로 초기화
	for (int i = 0; i < INVENTORY_SIZE; i++)
	{
		inventoryItem[i] = nullptr;
		inventoryIcon[i] = nullptr;
		isUse[i] = false;
	}

	// 인벤토리 UI 생성 및 로드
	inventoryUI = UI::Create("Inventory");
	inventoryUI->LoadFile("UI_Inventory.xml");
	tooltopBox = UI::Create("ToolTipBox");
	tooltopBox->LoadFile("UI_TooltipBox.xml");


	// 매번 static_cast를 사용하지 않기 위해, 사용할 UI들을 미리 저장
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
	// 저장한 UI 포인터들을 nullptr로 초기화
	panel = nullptr;
	tooltopBox = nullptr;
	for (int i = 0; i < INVENTORY_SIZE; i++)
	{
		slot[i] = nullptr;
		inventoryItem[i] = nullptr;
		inventoryIcon[i] = nullptr;
	}
	slot[BLUE_SLOT] = nullptr;

	// 인벤토리 UI 해제
	inventoryUI->Release();
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
	for (int i = 0; i < INVENTORY_SIZE; i++)
	{
		SafeDelete(inventoryItem[i]);
		SafeDelete(inventoryIcon[i]);
	}
	// =========

	panel= nullptr;
	tooltopBox = nullptr;
	for (int i = 0; i < INVENTORY_SIZE + 1; i++)
	{
		slot[i] = nullptr;
	}


	inventoryUI->Release();
}

void Inventory::Update()
{
	/*ImGui::Begin("UI Hierarchy");
	{
		inventoryUI->RenderHierarchy();
	}
	ImGui::End();*/

	// Tab키를 누르면 인벤토리가 열림
	if (INPUT->KeyDown(VK_TAB))
	{
		isOpen = !isOpen;

		// 인벤토리가 열렸으면
		if (isOpen)
		{
			// 모든 슬롯을 보이게 함
			inventoryUI->Find("SlotBottom")->visible = true;

			// 열림 사운드 재생
			SoundName randomPlay = static_cast<SoundName>(RANDOM->Int(UI_SHOW_01, UI_SHOW_03));
			SOUND->Play(randomPlay);
		}
		// 닫혔으면
		else
		{
			// 아래쪽 슬롯을 숨김
			inventoryUI->Find("SlotBottom")->visible = false;

			// 닫힘 사운드 재생
			SoundName randomPlay = static_cast<SoundName>(RANDOM->Int(UI_HIDE_01, UI_HIDE_03));
			SOUND->Play(randomPlay);
		}

		Init();
	}

	// ESC키를 누르면 인벤토리가 닫힘
	if (isOpen && INPUT->KeyDown(VK_ESCAPE))
	{
		isOpen = false;

		// 아래쪽 슬롯을 숨김
		inventoryUI->Find("SlotBottom")->visible = false;

		// 닫힘 사운드 재생
		SoundName randomPlay = static_cast<SoundName>(RANDOM->Int(UI_HIDE_01, UI_HIDE_03));
		SOUND->Play(randomPlay);

		Init();
	}

	for (auto icon : inventoryIcon)
		if (icon) icon->Update();

	// 인벤토리 UI 업데이트
	inventoryUI->Update();

	// 인벤토리가 열려있을 때
	if (isOpen)
	{
		// 툴팁박스 업데이트
		if (isOnTooltip)
		{
			tooltopBox->Update();
		}
	}
}

void Inventory::LateUpdate()
{
	static float resizeCycle = 9.0f;
	if (TIMER->GetTick(resizeCycle, 10.0f))
	{
		ResizeScreen();
	}

	if (isOpen)
	{
		// 마우스 오버시 슬롯 강조
		MouseOverSlot();

		// 아이템 사용
		CheckItem();

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


	for (int i = 0; i < INVENTORY_ROW_SIZE; i++)
	{
		DWRITE->RenderText(
			to_wstring(i + 1),
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

		// 툴팁박스
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
		for (int i = 0; i < INVENTORY_ROW_SIZE; i++)
			if (inventoryIcon[i]) inventoryIcon[i]->Render();
	}
}

void Inventory::ResizeScreen()
{
	float appHalfWidth = App.GetHalfWidth();
	float appHalfHeight = App.GetHalfHeight();

	// 숫자 창 크기 계산 (가로세로 절반크기, Pivot이 중앙이므로)
	Vector2 numberWindow{
		appHalfWidth * slot[0]->S._11,
		appHalfHeight * slot[0]->S._22 };


	// 인벤토리 첫번째 줄의 슬롯들 텍스트 위치 업데이트
	for (int i = 0; i < INVENTORY_ROW_SIZE; i++)
	{
		// 숫자 창 위치 계산
		Vector2 Baseline{
			appHalfWidth * (slot[i]->GetWorldPos().x + 1.0f),
			appHalfHeight * (1.0f - slot[i]->GetWorldPos().y) };

		// App.GetWidth() = 슬롯의 위치를 NDC좌표계로 변환
		// slot[i]->GetWorldPos().x + 1.0f) / 2.0f = 슬롯 위치(-1~1)를 (0~1)로 변환
		text_number[i].left = Baseline.x - numberWindow.x * 0.9f;
		text_number[i].right = text_number[i].left + 1000;
		text_number[i].top = Baseline.y - numberWindow.y * 0.9f;
		text_number[i].bottom = text_number[i].top + 200;
	}
}

void Inventory::MouseOverSlot()
{
	bool isMouseOver = false;
	bool isMouseOverItem = false;

	// 인벤토리가 열려있을 때, 마우스가 인벤토리 위에 있다면
	if (isOpen && panel->MouseOver())
	{
		//	모든 인벤토리 슬롯을 순회
		for (int i = 0; i < INVENTORY_SIZE; i++)
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

				// 해당슬롯에 아이템이 있다면
				if (inventoryItem[i])
				{
					isMouseOverItem = true;

					float appHalfWidth = App.GetHalfWidth();
					float appHalfHeight = App.GetHalfHeight();
					float screenBaselineX = 650.0f;
					float screenBaselineY = 425.0;

					// 화면 크기에 따라 툴팁박스 크기 조절할 가중치
					float screenRatioX = screenBaselineX / appHalfWidth;
					float screenRatioY = screenBaselineY / appHalfHeight;

					// 툴팁박스 x, y크기 조절
					tooltopBox->scale.x = screenRatioX;
					tooltopBox->scale.y = inventoryItem[i]->GetTooltipBoxScaleY() * screenRatioY;

					// 툴팁 박스를 마우스 위치로 이동
					tooltopBox->SetWorldPos(Utility::MouseToNDC());

					// 툴팁 텍스트 위치 조절
					Vector3 tooptipPos = tooltopBox->GetWorldPos();

					text_itemName.left = appHalfWidth * (tooptipPos.x + 1) + 70;
					text_itemName.right = text_itemName.left + 1000;
					text_itemName.top = appHalfHeight * (1 - tooptipPos.y) + 10;
					text_itemName.bottom = text_itemName.top + 200;

					text_itemExplain.left = appHalfWidth * (tooptipPos.x + 1) + 10;
					text_itemExplain.right = text_itemExplain.left + 1000;
					text_itemExplain.top = appHalfHeight * (1 - tooptipPos.y) + 50;
					text_itemExplain.bottom = text_itemExplain.top + 200;

					// 툴팁 박스 visible
					onMouseItemIndex = i;
					tooltopBox->visible = true;
					isOnTooltip = true;
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
			// 인벤토리에 아이템이 있으면
			if (inventoryItem[i])
			{
				// 해당 슬롯의 아이템과 인덱스를 저장
				selectedItem.item = inventoryItem[i];
				selectedItem.image = inventoryIcon[i];
				selectedItem.index = i;

				// 아이템 선택 사운드 재생
				SOUND->Play(UI_CLICK);
			}
		}
	}
}

void Inventory::ItemDrop()
{
	// 픽업된 아이템이 있으면
	if (selectedItem.item)
	{
		// 아이템의 아이콘이 마우스를 따라다님
		selectedItem.image->SetWorldPos(Utility::MouseToNDC());

		// 픽업중에 마우스 오른쪽 버튼을 누르면 아이템이 원래 위치로 돌아감
		if (INPUT->KeyDown(VK_RBUTTON))
		{
			selectedItem.item = nullptr;
			selectedItem.image->SetWorldPos(slot[selectedItem.index]->GetWorldPos());
			selectedItem.image = nullptr;
			selectedItem.index = -1;
		}

		// 픽업중에 마우스 왼쪽 버튼을 떼면
		if (INPUT->KeyUp(VK_LBUTTON))
		{
			Inventory::MouseLocation mLocation = CheckMouseLocation();

			if (mLocation.location == UILocation::OnSlot)
			{
				// 아이템을 드래그 중인 슬롯에 놓으면
				if (mLocation.index == selectedItem.index)
				{
					// 아이콘이 원래 슬롯으로
					selectedItem.item = nullptr;
					selectedItem.image->SetWorldPos(slot[selectedItem.index]->GetWorldPos());
					selectedItem.image = nullptr;
					selectedItem.index = -1;
				}
				// 아이템을 원래 슬롯이 아닌 다른 슬롯에 놓으면
				// 아이템을 다른 슬롯과 위치를 바꿈
				else
				{
					// 착용중인 아이템 인덱스 추적
					equippedItem.IndexSwap(selectedItem.index, mLocation.index);

					// 다른 슬롯에 아이템이 있다면
					if (inventoryItem[mLocation.index])
					{
						// 슬롯 색상 변경
						{
							// 원래 슬롯은 아이템 사용중, 다른 슬롯은 아이템 사용중이 아님
							if (isUse[selectedItem.index] && !isUse[mLocation.index])
							{
								// 원래슬롯은 일반슬롯으로 변경
								slot[selectedItem.index]->material->LoadFile("Inventory/InventorySlot.mtl");
								isUse[selectedItem.index] = false;

								// 다른슬롯은 블루슬롯으로 변경
								slot[mLocation.index]->material->LoadFile("Inventory/InventorySlotBlue.mtl");
								isUse[mLocation.index] = true;
							}
							// 원래 슬롯은 아이템 사용중이 아님, 다른 슬롯은 아이템 사용중
							else if (!isUse[selectedItem.index] && isUse[mLocation.index])
							{
								// 원래슬롯은 블루슬롯으로 변경
								slot[selectedItem.index]->material->LoadFile("Inventory/InventorySlotBlue.mtl");
								isUse[selectedItem.index] = true;

								// 다른슬롯은 일반슬롯으로 변경
								slot[mLocation.index]->material->LoadFile("Inventory/InventorySlot.mtl");
								isUse[mLocation.index] = false;
							}

						}



						// 다른 슬롯의 아이템을 드래그 중인 슬롯으로 이동
						inventoryItem[selectedItem.index] = inventoryItem[mLocation.index];
						inventoryIcon[selectedItem.index] = inventoryIcon[mLocation.index];
						inventoryIcon[selectedItem.index]->SetWorldPos(slot[selectedItem.index]->GetWorldPos());
					}
					// 다른 슬롯에 아이템이 없다면 
					else
					{
						// 원래 슬롯이 사용중이었으면
						if (isUse[selectedItem.index])
						{
							// 원래 슬롯은 일반슬롯으로, 다른 슬롯은 블루슬롯으로 변경
							slot[selectedItem.index]->material->LoadFile("Inventory/InventorySlot.mtl");
							isUse[selectedItem.index] = false;

							slot[mLocation.index]->material->LoadFile("Inventory/InventorySlotBlue.mtl");
							isUse[mLocation.index] = true;
						}

						// 원래 슬롯을 비움
						inventoryItem[selectedItem.index] = nullptr;
						inventoryIcon[selectedItem.index] = nullptr;
					}



					// 드래그 중인 아이템은 다른 슬롯으로 이동
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
				// 아이템을 원래 슬롯으로
				selectedItem.item = nullptr;
				selectedItem.image->SetWorldPos(slot[selectedItem.index]->GetWorldPos());
				selectedItem.image = nullptr;
				selectedItem.index = -1;
			}
			else if (mLocation.location == UILocation::OnGround)
			{
				// 원래 슬롯을 비우고
				inventoryItem[selectedItem.index] = nullptr;
				inventoryIcon[selectedItem.index] = nullptr;

				// 버릴 아이템의 타입 체크
				ItemType type = selectedItem.item->GetType();
				// 무기라면
				if (type == ItemType::Weapon)
				{
					// 지금 착용중인 무기인지 체크
					if (selectedItem.index == equippedItem.Weapon)
					{
						// 인벤토리 정보 업데이트
						slot[equippedItem.Weapon]->material->LoadFile("Inventory/InventorySlot.mtl");
						isUse[equippedItem.Weapon] = false;
						equippedItem.Weapon = -1;

						// 장착 해제
						selectedItem.item->Use();
					}
				}
				// 방패라면
				else if (type == ItemType::Shield)
				{
					// 지금 착용중인 방패인지 체크
					if (selectedItem.index == equippedItem.Shield)
					{
						// 인벤토리 정보 업데이트
						slot[equippedItem.Shield]->material->LoadFile("Inventory/InventorySlot.mtl");
						isUse[equippedItem.Shield] = false;
						equippedItem.Shield = -1;

						// 장착 해제
						selectedItem.item->Use();
					}
				}

				// 드래그 중인 아이템을 땅에 떨어뜨림
				selectedItem.item->Drop();

				// 아이템 버림 사운드 재생
				SOUND->Play(INVENTORY_ITEM_DROP);

				//  들고 있는 아이템 정보를 초기화
				selectedItem.item = nullptr;
				selectedItem.image = nullptr;
				selectedItem.index = -1;
			}
		}
	}
}

void Inventory::CheckItem(int shortcut)
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
						UseItem(equippedItem.Weapon, i);
					}
					else if (type == ItemType::Shield)
					{
						UseItem(equippedItem.Shield, i);
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
				UseItem(equippedItem.Weapon, shortcut);
			}
			else if (type == ItemType::Shield)
			{
				UseItem(equippedItem.Shield, shortcut);
			}
		}
	}

}

void Inventory::UseItem(int& equippedItem, int inventoryIndex)
{
	// 이전에 이미 착용중인 무기가 있으면
	if (equippedItem != -1)
	{
		// 이전에 착용중이던 무기를 해제
		inventoryItem[equippedItem]->Use();

		// 해당 슬롯을 원래 슬롯으로 변경
		slot[equippedItem]->material->LoadFile("Inventory/InventorySlot.mtl");

		// 해당	슬롯을 사용중이 아니라고 표시
		isUse[equippedItem] = false;
	}

	// 이전에 착용중인 무기가 자기 자신이면
	if (equippedItem == inventoryIndex)
	{
		// 무기 인덱스 초기화
		equippedItem = -1;
	}

	// 다른 무기라면
	else
	{
		// 새로운 무기를 착용
		inventoryItem[inventoryIndex]->Use();

		// 새로 착용한 무기슬롯을 블루슬롯으로 변경하고 인덱스 저장
		slot[inventoryIndex]->material->LoadFile("Inventory/InventorySlotBlue.mtl");

		// 해당	슬롯을 사용중이라고 표시
		isUse[inventoryIndex] = true;

		// 새로 착용한 무기 인덱스 저장
		equippedItem = inventoryIndex;
	}

	// 아이템 사용 사운드 재생
	SoundName randomPlay = static_cast<SoundName>(RANDOM->Int(INVENTORY_ITEM_USE_01, INVENTORY_ITEM_USE_04));
	SOUND->Play(randomPlay);
}

void Inventory::InputShortcut()
{
	if (INPUT->KeyDown('1')) CheckItem(0);
	else if (INPUT->KeyDown('2')) CheckItem(1);
	else if (INPUT->KeyDown('3')) CheckItem(2);
	else if (INPUT->KeyDown('4')) CheckItem(3);
	else if (INPUT->KeyDown('5')) CheckItem(4);
	else if (INPUT->KeyDown('6')) CheckItem(5);
	else if (INPUT->KeyDown('7')) CheckItem(6);
	else if (INPUT->KeyDown('8')) CheckItem(7);
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
	// 아이템의 액터위치를 임시로 변경
	item->GetActor()->SetWorldPos(Vector3(0, -999, 0));
	item->Update();

	// 아이템이 중첩 가능한 타입(재료, 음식)이면
	if (item->GetType() == ItemType::Material || item->GetType() == ItemType::Food)
	{
		MaterialProto* mItem = dynamic_cast<MaterialProto*>(item);
		if (mItem)
		{
			// 인벤토리를 전체를 순회해서 같은 아이템이 있는지 체크
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

	// 인벤토리를 순회하며 빈 공간을 찾음
	for (int i = 0; i < INVENTORY_SIZE; i++)
	{
		// 빈 공간을 찾으면
		if (inventoryItem[i] == nullptr)
		{
			// 인벤토리에 아이템 추가
			inventoryItem[i] = item;
			inventoryIcon[i] = item->GetIcon();
			inventoryIcon[i]->SetWorldPos(slot[i]->GetWorldPos());
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

bool Inventory::CheckMaterial(Item item, int quantity)
{
	// 인벤토리를 순회해서 재료가 있는지 체크
	for (int i = 0; i < INVENTORY_SIZE; i++)
	{

		// 아이템이 있고, 재료 이름이 같으면
		if (inventoryItem[i] && inventoryItem[i]->GetEnumName() == item)
		{
			// Down Casting
			MaterialProto* material = dynamic_cast<MaterialProto*>(inventoryItem[i]);
			if (material)
			{
				// 재료의 현재 중첩수가 필요한 수 이상이면 수량0으로 변경
				if (material->currentStack >= quantity) quantity = 0;
				// 재료의 현재 중첩수가 필요한 수 미만이면 필요한 수에서 현재 중첩수를 뺌
				else quantity -= material->currentStack;
			}
			WeaponProto* weapon = dynamic_cast<WeaponProto*>(inventoryItem[i]);
			if (weapon)
			{
				return true;
			}
		}

		// 필요한 재료의 수가 0이하면 true 반환
		if (quantity <= 0) return true;
	}

	return false;
}

void Inventory::UseMaterial(Item item, int quantity)
{
	// 인벤토리를 순회해서 재료가 있는지 체크
	for (int i = 0; i < INVENTORY_SIZE; i++)
	{
		// 아이템이 있고, 재료 이름이 같으면
		if (inventoryItem[i] && inventoryItem[i]->GetEnumName() == item)
		{
			// Down Casting
			WeaponProto* weapon = dynamic_cast<WeaponProto*>(inventoryItem[i]);
			if (weapon)
			{
				// 재료가 이미 착용중인 무기라면
				if (equippedItem.Weapon == i)
				{
					// 이전에 착용중이던 무기를 해제
					inventoryItem[i]->Use();

					// 해당	슬롯을 사용중이 아니라고 표시
					isUse[i] = false;
					
					// 해당 슬롯을 원래 슬롯으로 변경
					slot[equippedItem.Weapon]->material->LoadFile("Inventory/InventorySlot.mtl");

					// 무기 인덱스 초기화
					equippedItem.Weapon = -1;
				}

				weapon->currentStack = 0;

				inventoryItem[i] = nullptr;
				inventoryIcon[i] = nullptr;

				return;
			}

			// Down Casting
			MaterialProto* material = dynamic_cast<MaterialProto*>(inventoryItem[i]);
			if (material)
			{
				// 재료의 현재 중첩수가 필요한 수 이상이면
				if (material->currentStack >= quantity)
				{
					// 재료의 현재 중첩수에서 필요한 수를 뺌
					material->currentStack -= quantity;
					// 필요한 수를 0으로 변경
					quantity = 0;

					// 재료의 현재 중첩수가 0이면
					if (material->currentStack == 0)
					{
						// 인벤토리에서 아이템 삭제
						inventoryItem[i] = nullptr;
						inventoryIcon[i] = nullptr;
					}
				}
				// 재료의 현재 중첩수가 필요한 수 미만이면
				else
				{
					// 필요한 수에서 재료의 현재 중첩수를 뺌
					quantity -= material->currentStack;
					// 재료의 현재 중첩수를 0으로 변경
					material->currentStack = 0;

					// 인벤토리에서 아이템 삭제
					inventoryItem[i] = nullptr;
					inventoryIcon[i] = nullptr;
				}
			}
		}

		// 필요한 재료의 수가 0이하면 true 반환
		if (quantity <= 0) return;
	}
}
