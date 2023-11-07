#include "stdafx.h"
#include "InventoryUiPannel.h"

InventoryUiPannel::InventoryUiPannel()
{
	playerInventory = UI::Create("playerInventory");
	playerInventory->LoadFile("InvenUI.xml");
	//인벤토리 처음에 감추기 메인슬롯은 보여줍니다
	playerInventory->Find("PLAYER_PANNEL_INVEN")->visible = false;
	for (int i = 0; i < 8; i++)
	{
		playerInventory->Find("mainSlot" + to_string(i))->visible = true;
		playerInventory->Find("subSlot" + to_string(i))->visible = false;
		playerInventory->Find("SecondsubSlot" + to_string(i))->visible = false;
		playerInventory->Find("ThirdsubSlot" + to_string(i))->visible = false;
	}
}

InventoryUiPannel::~InventoryUiPannel()
{

}

void InventoryUiPannel::Init()
{
}

void InventoryUiPannel::Release()
{
}

void InventoryUiPannel::Update()
{
	ImGui::Begin("Hierarchy");
	{
		playerInventory->RenderHierarchy();
	}
	ImGui::End();

	playerInventory->Update();

	//ui 위치코드로 배정해주기
	for (int i = 0; i < 8; i++)
	{
		playerInventory->Find("subSlot" + to_string(i))->SetLocalPos(Vector3(-0.320 + i * 0.090, 0.110, 0));
		playerInventory->Find("subSlot" + to_string(i))->scale.x = 0.110f;
		playerInventory->Find("subSlot" + to_string(i))->scale.y = 0.170f;

		playerInventory->Find("SecondsubSlot" + to_string(i))->SetLocalPos(Vector3(-0.320 + i * 0.090, -0.050, 0));
		playerInventory->Find("SecondsubSlot" + to_string(i))->scale.x = 0.110f;
		playerInventory->Find("SecondsubSlot" + to_string(i))->scale.y = 0.170f;

		playerInventory->Find("ThirdsubSlot" + to_string(i))->SetLocalPos(Vector3(-0.320 + i * 0.090, -0.200, 0));
		playerInventory->Find("ThirdsubSlot" + to_string(i))->scale.x = 0.110f;
		playerInventory->Find("ThirdsubSlot" + to_string(i))->scale.y = 0.170f;
	}
}

void InventoryUiPannel::LateUpdate()
{
	//탭키로 인벤토리 온오프
	if (INPUT->KeyDown(VK_TAB))
	{
		playerInventory->Find("PLAYER_PANNEL_INVEN")->visible = !playerInventory->Find("PLAYER_PANNEL_INVEN")->visible;
		for (int i = 0; i < 8; i++)
		{
			playerInventory->Find("subSlot" + to_string(i))->visible = !playerInventory->Find("subSlot" + to_string(i))->visible;
			playerInventory->Find("SecondsubSlot" + to_string(i))->visible = !playerInventory->Find("SecondsubSlot" + to_string(i))->visible;
			playerInventory->Find("ThirdsubSlot" + to_string(i))->visible = !playerInventory->Find("ThirdsubSlot" + to_string(i))->visible;
		}
	}
    //템칸에 마우스올릴때 이미지변경 불들어오는 효과
	// 인벤토리가 켜져있을때@
	if (playerInventory->Find("PLAYER_PANNEL_INVEN")->visible)
	{
		for (int i = 0; i < 8; i++)
		{
			if (dynamic_cast<UI*>(playerInventory->Find("mainSlot" + to_string(i)))->MouseOver())
			{
				playerInventory->Find("mainSlot" + to_string(i))->material->LoadFile("mainSlotBlue.mtl");
			}
			else
				playerInventory->Find("mainSlot" + to_string(i))->material->LoadFile("mainSlot.mtl");

			if (dynamic_cast<UI*>(playerInventory->Find("subSlot" + to_string(i)))->MouseOver())
			{
				playerInventory->Find("subSlot" + to_string(i))->material->LoadFile("mainSlotBlue.mtl");
			}
			else
				playerInventory->Find("subSlot" + to_string(i))->material->LoadFile("mainSlot.mtl");

			if (dynamic_cast<UI*>(playerInventory->Find("SecondsubSlot" + to_string(i)))->MouseOver())
			{
				playerInventory->Find("SecondsubSlot" + to_string(i))->material->LoadFile("mainSlotBlue.mtl");
			}
			else
				playerInventory->Find("SecondsubSlot" + to_string(i))->material->LoadFile("mainSlot.mtl");

			if (dynamic_cast<UI*>(playerInventory->Find("ThirdsubSlot" + to_string(i)))->MouseOver())
			{
				playerInventory->Find("ThirdsubSlot" + to_string(i))->material->LoadFile("mainSlotBlue.mtl");
			}
			else
				playerInventory->Find("ThirdsubSlot" + to_string(i))->material->LoadFile("mainSlot.mtl");
		}
	}
	

}

void InventoryUiPannel::PreRender()
{
}

void InventoryUiPannel::Render()
{
	playerInventory->Render();
}

void InventoryUiPannel::ResizeScreen()
{
}
