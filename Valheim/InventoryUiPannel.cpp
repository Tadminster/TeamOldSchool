#include "stdafx.h"
#include "InventoryUiPannel.h"

InventoryUiPannel::InventoryUiPannel()
{
	playerInventory = UI::Create("playerInventory");
	playerInventory->LoadFile("InvenUI.xml");
	//�κ��丮 ó���� ���߱� ���ν����� �����ݴϴ�
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
