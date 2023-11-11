#include "stdafx.h"
#include "InventoryUiPannel.h"

InventoryUiPannel::InventoryUiPannel()
{
	playerInventory = UI::Create("playerInventory");
	playerInventory->LoadFile("InvenUI.xml");

	stoneImg = UI::Create("stoneImg");
	woodImg = UI::Create("woodImg");


	stoneImg->LoadFile("stoneImg.xml");
	woodImg->LoadFile("woodImg.xml");
	stoneImg->visible = false;
	woodImg->visible = false;

	//인벤토리 처음에 감추기 메인슬롯은 보여줍니다
	playerInventory->Find("PLAYER_PANNEL_INVEN")->visible = false;
	for (int i = 0; i < 32; i++)
	{
		if (i < 8)
		{
			playerInventory->Find("itemSlot" + to_string(i))->visible = true;
		}
		else
		{
			playerInventory->Find("itemSlot" + to_string(i))->visible = false;
		}
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
		stoneImg->RenderHierarchy();
		woodImg->RenderHierarchy();
	}
	ImGui::End();

	playerInventory->Update();
	stoneImg->Update();
	woodImg->Update();

	//ui 위치코드로 배정해주기
	for (int i = 0; i < 32; i++)
	{
		playerInventory->Find("itemSlot" + to_string(i))->scale.x = 0.050f;;
		playerInventory->Find("itemSlot" + to_string(i))->scale.y = 0.080f;;
		if (i < 8)
		{
			playerInventory->Find("itemSlot" + to_string(i))->SetLocalPosX(-0.870 + i * 0.100);
			playerInventory->Find("itemSlot" + to_string(i))->SetLocalPosY(0.800);
		}
		if (i < 16 and i >= 8)
		{
			playerInventory->Find("itemSlot" + to_string(i))->SetLocalPosX(-0.870 + (i-8) * 0.100);
			playerInventory->Find("itemSlot" + to_string(i))->SetLocalPosY(0.630);
		}
		if (i < 24 and i >= 16)
		{
			playerInventory->Find("itemSlot" + to_string(i))->SetLocalPosX(-0.870 + (i - 16) * 0.100);
			playerInventory->Find("itemSlot" + to_string(i))->SetLocalPosY(0.460);
		}
		if (i < 32 and i >=24)
		{
			playerInventory->Find("itemSlot" + to_string(i))->SetLocalPosX(-0.870 + (i - 24) * 0.100);
			playerInventory->Find("itemSlot" + to_string(i))->SetLocalPosY(0.290);
		}
	}
	//임시로 나무랑 돌멩이 위치해놓기
	stoneImg->SetWorldPos(playerInventory->Find("itemSlot8")->GetWorldPos());
	woodImg->SetWorldPos(playerInventory->Find("itemSlot9")->GetWorldPos());
}

void InventoryUiPannel::LateUpdate()
{
	//탭키로 인벤토리 온오프
	if (INPUT->KeyDown(VK_TAB))
	{
		playerInventory->Find("PLAYER_PANNEL_INVEN")->visible = !playerInventory->Find("PLAYER_PANNEL_INVEN")->visible;
		stoneImg->visible = !stoneImg->visible;
		woodImg->visible = !woodImg->visible;
		for (int i = 8; i < 32; i++)
		{
			playerInventory->Find("itemSlot" + to_string(i))->visible = !playerInventory->Find("itemSlot" + to_string(i))->visible;
		}
	}

	//템칸에 마우스올릴때 이미지변경 불들어오는 효과
	// 인벤토리가 켜져있을때@
	if (playerInventory->Find("PLAYER_PANNEL_INVEN")->visible)
	{
		for (int i = 0; i < 32; i++)
		{
			if (dynamic_cast<UI*>(playerInventory->Find("itemSlot" + to_string(i)))->MouseOver())
			{
				playerInventory->Find("itemSlot" + to_string(i))->material->LoadFile("mainSlotBlue.mtl");
			}
			else
				playerInventory->Find("itemSlot" + to_string(i))->material->LoadFile("mainSlot.mtl");
			//인벤토리 슬롯 이미지교체기능
		}
	}



	
}

void InventoryUiPannel::PreRender()
{
}

void InventoryUiPannel::Render()
{
	playerInventory->Render();
	stoneImg->Render();
	woodImg->Render();
}

void InventoryUiPannel::ResizeScreen()
{
}
