#include "stdafx.h"
#include "Craft.h"

Craft::Craft()
{
	// 모든 크래프팅을 nullptr로 초기화
	for (int i = 0; i < RECIPE_SIZE; ++i)
	{
		hasRecipe[i] = false;
	}

	// 크래프팅 UI 생성 및 로드
	craftUI = UI::Create("Craft");
	craftUI->LoadFile("UI_Craft.xml");
	craftUI->SetWorldPosX(App.GetWidth() * 0.5f / App.GetWidth());
	craftUI->SetWorldPosY(-App.GetHalfHeight() * 0.1f / App.GetHalfHeight());

	// 재료 아이콘 배경
	int index = 1;
	for (auto& material : iconMaterial)
	{
		material = UI::Create("Material" + index);
		material->LoadFile("UI_Empty.xml");
		string targetName = "2_BG_Material" + to_string(index);
		material->SetWorldPos(craftUI->Find(targetName)->GetWorldPos());

		index++;
	}

	// 매번 static_cast를 사용하지 않기 위해, 사용할 UI들을 미리 저장
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
		// 마우스 오버시 슬롯 강조
		MouseOverRecipe();

		// 레시피 선택
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

	// 인벤토리가 열려있을 때, 마우스가 인벤토리 위에 있다면
	if (INVEN->isOpen && panel->MouseOver())
	{
		//	모든 레서피 버튼을 순회
		for (int i = 0; i < RECIPE_SIZE; i++)
		{
			// 마우스가 해당 버튼 있다면
			if (btnRecipe[i]->MouseOver())
			{
				isMouseOver = true;

				// 반투명 배경을 해당 버튼 위치로 이동
				btnRecipe[RECIPE_MOUSE_OVER]->SetLocalPos(btnRecipe[i]->GetLocalPos());
				
				// 반투명 배경 visible
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
			// 버튼에 레시피가 있다면
			//if (hasRecipe[i])
			{
				// 해당 슬롯의 아이템과 인덱스를 저장
				
				//selectedItem.item = inventoryItem[i];
				//selectedItem.image = inventoryIcon[i];
				//selectedItem.index = i;

				// 반투명 배경을 해당 버튼 위치로 이동
				btnRecipe[RECIPE_MOUSE_CLICK]->SetLocalPos(btnRecipe[i]->GetLocalPos());

				// 반투명 배경 visible
				btnRecipe[RECIPE_MOUSE_CLICK]->visible = true;
			}
		}
	}
}
