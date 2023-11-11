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

	//�κ��丮 ó���� ���߱� ���ν����� �����ݴϴ�
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

	//ui ��ġ�ڵ�� �������ֱ�
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
	//�ӽ÷� ������ ������ ��ġ�س���
	stoneImg->SetWorldPos(playerInventory->Find("itemSlot8")->GetWorldPos());
	woodImg->SetWorldPos(playerInventory->Find("itemSlot9")->GetWorldPos());
}

void InventoryUiPannel::LateUpdate()
{
	//��Ű�� �κ��丮 �¿���
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

	//��ĭ�� ���콺�ø��� �̹������� �ҵ����� ȿ��
	// �κ��丮�� ����������@
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
			//�κ��丮 ���� �̹�����ü���
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
