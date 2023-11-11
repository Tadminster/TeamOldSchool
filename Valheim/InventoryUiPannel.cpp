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

	//인벤토리 처음에 감추기 메인슬롯은 보여줍니다
	playerInventory->Find("PLAYER_PANNEL_INVEN")->visible = false;
	for (int i = 0; i < 8; i++)
	{
		playerInventory->Find("mainSlot" + to_string(i))->visible = true;
		playerInventory->Find("subSlot" + to_string(i))->visible = false;
		playerInventory->Find("SecondsubSlot" + to_string(i))->visible = false;
		playerInventory->Find("ThirdsubSlot" + to_string(i))->visible = false;

		//인벤토리 슬롯에 사용할 자식노드 만들어두기
		/*playerInventory->Find("mainSlot" + to_string(i))->AddChild(UI::Create("main" + to_string(i) + "Img"));
		playerInventory->Find("subSlot" + to_string(i))->AddChild(UI::Create("sub" + to_string(i) + "Img"));
		playerInventory->Find("SecondsubSlot" + to_string(i))->AddChild(UI::Create("Secondsub" + to_string(i) + "Img"));
		playerInventory->Find("ThirdsubSlot" + to_string(i))->AddChild(UI::Create("Thirdsub" + to_string(i) + "Img"));*/
		//자식노드 mesh shader material 지정해주기
		/*playerInventory->Find("main" + to_string(i) + "Img")->mesh->LoadFile("6.UI.mesh");
		playerInventory->Find("main" + to_string(i) + "Img")->shader->LoadFile("6.UI.hlsl");
		playerInventory->Find("main" + to_string(i) + "Img")->material->LoadFile("woodImg.mtl");*/
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

	//아이템 이미지 이동기능
	/*if (stoneImg->mousePress)
	{
		stoneImg->MoveWorldPos(Vector3(INPUT->movePosition / App.GetWidth() * 2.0f,
			0,
			0
		);
	}*/

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

	//아이템획득시 아이템 이미지 인벤토리에 적용
	if (INPUT->KeyDown(VK_F8))
	{
		stoneImg->SetWorldPos(playerInventory->Find("subSlot0")->GetWorldPos());
		woodImg->SetWorldPos(playerInventory->Find("subSlot1")->GetWorldPos());
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
