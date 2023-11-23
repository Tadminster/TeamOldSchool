#include "stdafx.h"
#include "ItemProto.h"
#include "Recipe.h"
#include "Craft.h"

Craft::Craft()
{
	// 모든 크래프팅을 변수 초기화
	for (int i = 0; i < RECIPE_SIZE; ++i)
	{
		recipeItem[i] = nullptr;
		hasRecipe[i] = false;
	}
	selectedRecipe = nullptr;

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
	detailUI = static_cast<UI*>(craftUI->Find("1_BG_CraftDetail"));
	
	for (int i = 0; i < RECIPE_SIZE; ++i)
	{
		btnRecipe[i] = static_cast<UI*>(craftUI->Find("2_Btn_Recipe" + to_string(i + 1)));\
		iconRecipe[i] = static_cast<UI*>(craftUI->Find("3_Icon_Recipe" + to_string(i + 1)));
	}
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
	{
		// UI 업데이트
		craftUI->Update();

		// 레시피 정보 업데이트
		RecipeUpdate();
	}
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
	{
		craftUI->Render();

		for (int i = 0; i < RECIPE_SIZE; ++i)
		{
			if (hasRecipe[i])
			{
				// 텍스트 위치 설정
				textRecipe[i].left = App.GetHalfWidth() * (btnRecipe[i]->GetWorldPos().x + 1.0f) + textRecipeCorrect.x;
				textRecipe[i].right = textRecipe[i].left + 1000;
				textRecipe[i].top = App.GetHalfHeight() * (1.0f - btnRecipe[i]->GetWorldPos().y) + textRecipeCorrect.y;
				textRecipe[i].bottom = textRecipe[i].top + 200;

				// 레시피 아이템 아이콘 표시
				DWRITE->RenderText(
					recipeItem[i]->wstringName,
					textRecipe[i],
					16.0f,
					L"Arial",
					Color(1.0f, 1.0f, 1.0f, 0.0f),
					DWRITE_FONT_WEIGHT_MEDIUM,
					DWRITE_FONT_STYLE_ITALIC,
					DWRITE_FONT_STRETCH_EXPANDED);
			}
		}

		if (selectedRecipe)
		{
			// 레시피 아이템 이름
			DWRITE->RenderText(
				selectedRecipe->wstringName,
				textDetailName,
				20.0f,
				L"Arial",
				Color(1.0f, 1.0f, 1.0f, 0.0f),
				DWRITE_FONT_WEIGHT_SEMI_BOLD,
				DWRITE_FONT_STYLE_ITALIC,
				DWRITE_FONT_STRETCH_EXPANDED);

			// 레시피 아이템 설명
			DWRITE->RenderText(
				selectedRecipe->description,
				textDetailExplain,
				16.0f,
				L"Arial",
				Color(1.0f, 1.0f, 1.0f, 0.0f),
				DWRITE_FONT_WEIGHT_MEDIUM,
				DWRITE_FONT_STYLE_ITALIC,
				DWRITE_FONT_STRETCH_EXPANDED);

			auto it = selectedRecipe->material.begin();
			for (int i = 0; i < MATERIAL_SIZE; i++)
			{
				// 표시할 재료가 있다면
				if (needMaterial[i])
				{
					// 수량 표시
					DWRITE->RenderText(
						to_wstring(it->second),
						textDetailMaterialNum[i],
						20.0f,
						L"Arial",
						Color(1.0f, 1.0f, 1.0f, 0.0f),
						DWRITE_FONT_WEIGHT_MEDIUM,
						DWRITE_FONT_STYLE_ITALIC,
						DWRITE_FONT_STRETCH_EXPANDED);

					it++;
				}
			}
		}
	}
}

void Craft::ResizeScreen()
{
}

void Craft::RecipeUpdate()
{
	map<Item, bool> discoveryRecipeList = RECIPE->GetRecipeList();

	// 레서피 목록을 순회
	for (int index = 0; auto recipe : discoveryRecipeList)
	{
		// 레시피가 해금되었다면
		if (recipe.second)
		{
			// 레시피 아이템을 생성
			recipeItem[index] = RECIPE->GetRecipe(recipe.first);

			// 레시피가 존재데이터 업데이트
			hasRecipe[index] = true;

			// 레서피 선택 버튼 업데이트
			RecipeButtonUpdate(index);
		}
	}
}

void Craft::RecipeButtonUpdate(int BtnIndex)
{
	if (hasRecipe[BtnIndex])
	{
		// 버튼 이미지 변경
		string iconFileName = GetIconFileName(recipeItem[BtnIndex]->enumName);
		SafeReset(iconRecipe[BtnIndex]->material->diffuseMap);
		iconRecipe[BtnIndex]->material->diffuseMap = RESOURCE->textures.Load(iconFileName);
	}
	else
	{
		// 버튼 이미지 변경
		SafeReset(iconRecipe[BtnIndex]->material->diffuseMap);
		iconRecipe[BtnIndex]->material->diffuseMap = RESOURCE->textures.Load("Empty.png");
	}
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
			if (hasRecipe[i])
			{
				// 선택한 레시피 저장
				selectedRecipe = recipeItem[i];

				// 반투명 배경을 해당 버튼 위치로 이동
				btnRecipe[RECIPE_MOUSE_CLICK]->SetLocalPos(btnRecipe[i]->GetLocalPos());

				// 반투명 배경 visible
				btnRecipe[RECIPE_MOUSE_CLICK]->visible = true;

				// 상세정보 창 업데이트
				RecipeDetailUpdate();
			}
		}
	}
}

void Craft::RecipeDetailUpdate()
{
	float appHalfWidth = App.GetHalfWidth();
	float appHalfHeight = App.GetHalfHeight();

	//디테일 창 크기 계산 (가로세로 절반크기, Pivot이 중앙이므로)
	Vector2 detailSize{	
		appHalfWidth * detailUI->S._11, 
		appHalfHeight * detailUI->S._22	};

	// 디테일 창 위치 계산
	Vector2 Baseline{ 
		appHalfWidth * (detailUI->GetWorldPos().x + 1.0f),
		appHalfHeight * (1.0f - detailUI->GetWorldPos().y) };

	// 텍스트 위치 설정
	{
		// 아이템 이름
		textDetailName.left = Baseline.x - detailSize.x * 0.8f;
		textDetailName.right = textDetailName.left + 1000;
		textDetailName.top = Baseline.y - detailSize.y * 0.85f;
		textDetailName.bottom = textDetailName.top + 200;

		// 설명
		textDetailExplain.left = textDetailName.left;
		textDetailExplain.right = textDetailName.right;
		textDetailExplain.top = Baseline.y - detailSize.y * 0.7f;
		textDetailExplain.bottom = textDetailExplain.top + 1000;

		// 재료 수량
		float iconCorrectY = appHalfHeight * iconMaterial[0]->S._22 * 0.6f;
		for (int i = 0; i < MATERIAL_SIZE; i++)
		{
			textDetailMaterialNum[i].left = appHalfWidth * (iconMaterial[i]->GetWorldPos().x + 1.0f);
			textDetailMaterialNum[i].right = textDetailMaterialNum[i].left + 1000;
			textDetailMaterialNum[i].top = appHalfHeight * (1.0f - iconMaterial[i]->GetWorldPos().y) + iconCorrectY;
			textDetailMaterialNum[i].bottom = textDetailMaterialNum[i].top + 200;
		}
	}

	// 표시할 재료 초기화
	int baseline = selectedRecipe->material.size();
	for (int i = 0; i < MATERIAL_SIZE; i++)
	{
		if (i < baseline) needMaterial[i] = true;
		else needMaterial[i] = false;
	}
}

void Craft::ApplyMaterialIcon(RecipeInfo recipeInfo)
{
	int index = 1;
	// 재료들을 순회 (아직 표시할 재료가 남아있다면)
	for (auto& material : recipeInfo.material)
	{
		// 위치 설정
		string targetName = "2_BG_Material" + to_string(index);
		iconMaterial[index]->SetWorldPos(craftUI->Find(targetName)->GetWorldPos());

		// 아이콘 변경
		string iconFileName = GetIconFileName(recipeInfo.enumName);
		SafeReset(iconMaterial[index]->material->diffuseMap);
		iconMaterial[index]->material->diffuseMap = RESOURCE->textures.Load(iconFileName);

		index++;
	}

	// 모든 재료 아이콘을 표시하고 남은 재료 아이콘이 있다면
	if (index <= MATERIAL_SIZE)
	{
		// 남은 재료 아이콘은 Empty.png로 변경
		for (int i = index; i <= MATERIAL_SIZE; i++)
		{
			SafeReset(iconMaterial[index]->material->diffuseMap);
			iconMaterial[index]->material->diffuseMap = RESOURCE->textures.Load("Empty.png");
		}
	}
}

string Craft::GetIconFileName(Item item)
{
	string path = "Item/";
	switch (item)
	{
	case Item::StoneAxe:	path += "axe_stone.png"; break;
		case Item::Woodpile:	path += "woodpile.png"; break;
		case Item::Stone:		path += "stone.png"; break;
		default:				path += "ERROE: Undefined icon name";
	}

	return path;
}
