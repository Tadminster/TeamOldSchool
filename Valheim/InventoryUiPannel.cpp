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

	//�κ��丮 ó���� ���߱� ���ν����� �����ݴϴ�
	playerInventory->Find("PLAYER_PANNEL_INVEN")->visible = false;
	for (int i = 0; i < 8; i++)
	{
		playerInventory->Find("mainSlot" + to_string(i))->visible = true;
		playerInventory->Find("subSlot" + to_string(i))->visible = false;
		playerInventory->Find("SecondsubSlot" + to_string(i))->visible = false;
		playerInventory->Find("ThirdsubSlot" + to_string(i))->visible = false;

		//�κ��丮 ���Կ� ����� �ڽĳ�� �����α�
		/*playerInventory->Find("mainSlot" + to_string(i))->AddChild(UI::Create("main" + to_string(i) + "Img"));
		playerInventory->Find("subSlot" + to_string(i))->AddChild(UI::Create("sub" + to_string(i) + "Img"));
		playerInventory->Find("SecondsubSlot" + to_string(i))->AddChild(UI::Create("Secondsub" + to_string(i) + "Img"));
		playerInventory->Find("ThirdsubSlot" + to_string(i))->AddChild(UI::Create("Thirdsub" + to_string(i) + "Img"));*/
		//�ڽĳ�� mesh shader material �������ֱ�
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

	//ui ��ġ�ڵ�� �������ֱ�
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

	//������ �̹��� �̵����
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
	//��Ű�� �κ��丮 �¿���
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
	//��ĭ�� ���콺�ø��� �̹������� �ҵ����� ȿ��
	// �κ��丮�� ����������@
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

	//������ȹ��� ������ �̹��� �κ��丮�� ����
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
