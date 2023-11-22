#include "stdafx.h"
#include "Craft.h"

Craft::Craft()
{
	// ��� ũ�������� nullptr�� �ʱ�ȭ
	for (int i = 0; i < RECIPE_SIZE; ++i)
	{
		hasRecipe[i] = false;
	}

	// ũ������ UI ���� �� �ε�
	craftUI = UI::Create("Craft");
	craftUI->LoadFile("UI_Craft.xml");
	craftUI->SetWorldPosX(App.GetWidth() * 0.5f / App.GetWidth());
	craftUI->SetWorldPosY(-App.GetHalfHeight() * 0.1f / App.GetHalfHeight());

	// ��� ������ ���
	int index = 1;
	for (auto& material : iconMaterial)
	{
		material = UI::Create("Material" + index);
		material->LoadFile("UI_Empty.xml");
		string targetName = "2_BG_Material" + to_string(index);
		material->SetWorldPos(craftUI->Find(targetName)->GetWorldPos());

		index++;
	}

	// �Ź� static_cast�� ������� �ʱ� ����, ����� UI���� �̸� ����
	panel = static_cast<UI*>(craftUI->Find("0_Panel"));
	
	for (int i = 0; i < RECIPE_SIZE; ++i)
		btnRecipe[i] = static_cast<UI*>(craftUI->Find("2_Btn_Recipe" + to_string(i + 1)));\
	btnRecipe[RECIPE_MOUSE_OVER] = static_cast<UI*>(craftUI->Find("2_Btn_Recipe98"));
	btnRecipe[RECIPE_MOUSE_CLICK] = static_cast<UI*>(craftUI->Find("2_Btn_Recipe99"));
	
	for (int i = 0; i < MATERIAL_SIZE; ++i)
		iconMaterial[i] = static_cast<UI*>(craftUI->Find("2_BG_Material" + to_string(i + 1)));


}

Craft::~Craft()
{
}

void Craft::Init()
{
}

void Craft::Release()
{
}

void Craft::Update()
{
	ImGui::Begin("CraftHierarchy");
	{
		craftUI->RenderHierarchy();
		for (auto& material : iconMaterial)
		{
			material->RenderHierarchy();
		}
	}
	ImGui::End();

	if (INVEN->isOpen)
		craftUI->Update();
}

void Craft::LateUpdate()
{
	if (INVEN->isOpen)
	{
		// ���콺 ������ ���� ����
		MouseOverRecipe();

		// ������ ����
		RecipeSelect();
	}
}

void Craft::PreRender()
{
}

void Craft::Render()
{
	if (INVEN->isOpen)
		craftUI->Render();
}

void Craft::ResizeScreen()
{
}

void Craft::MouseOverRecipe()
{
	bool isMouseOver = false;

	// �κ��丮�� �������� ��, ���콺�� �κ��丮 ���� �ִٸ�
	if (INVEN->isOpen && panel->MouseOver())
	{
		//	��� ������ ��ư�� ��ȸ
		for (int i = 0; i < RECIPE_SIZE; i++)
		{
			// ���콺�� �ش� ��ư �ִٸ�
			if (btnRecipe[i]->MouseOver())
			{
				isMouseOver = true;

				// ������ ����� �ش� ��ư ��ġ�� �̵�
				btnRecipe[RECIPE_MOUSE_OVER]->SetLocalPos(btnRecipe[i]->GetLocalPos());
				
				// ������ ��� visible
				btnRecipe[RECIPE_MOUSE_OVER]->visible = true;
			}
		}
	}
	else
	{
		btnRecipe[RECIPE_MOUSE_OVER]->visible = false;
	}

	if (!isMouseOver)
	{
		btnRecipe[RECIPE_MOUSE_OVER]->visible = false;
	}

}

void Craft::RecipeSelect()
{
	for (int i = 0; i < RECIPE_SIZE; i++)
	{
		if (INPUT->KeyDown(VK_LBUTTON) && btnRecipe[i]->MouseOver())
		{
			// ��ư�� �����ǰ� �ִٸ�
			//if (hasRecipe[i])
			{
				// �ش� ������ �����۰� �ε����� ����
				
				//selectedItem.item = inventoryItem[i];
				//selectedItem.image = inventoryIcon[i];
				//selectedItem.index = i;

				// ������ ����� �ش� ��ư ��ġ�� �̵�
				btnRecipe[RECIPE_MOUSE_CLICK]->SetLocalPos(btnRecipe[i]->GetLocalPos());

				// ������ ��� visible
				btnRecipe[RECIPE_MOUSE_CLICK]->visible = true;
			}
		}
	}
}
