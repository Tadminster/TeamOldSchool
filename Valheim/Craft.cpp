#include "stdafx.h"
#include "ItemProto.h"
#include "Recipe.h"
#include "Craft.h"

Craft::Craft()
{
	// 모든 크래프팅을 변수 초기화
	for (int i = 0; i < RECIPE_SIZE; i++)
	{
		recipeItem[i] = nullptr;
		hasRecipe[i] = false;
	}
	selectedRecipe = nullptr;
	btnCreateState = BtnState::NONE;

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

	for (int i = 0; i < RECIPE_SIZE; i++)
	{
		btnRecipe[i] = static_cast<UI*>(craftUI->Find("2_Btn_Recipe" + to_string(i + 1))); \
			iconRecipe[i] = static_cast<UI*>(craftUI->Find("3_Icon_Recipe" + to_string(i + 1)));
	}
	btnRecipe[RECIPE_MOUSE_OVER] = static_cast<UI*>(craftUI->Find("2_Btn_Recipe98"));
	btnRecipe[RECIPE_MOUSE_CLICK] = static_cast<UI*>(craftUI->Find("2_Btn_Recipe99"));

	for (int i = 0; i < MATERIAL_SIZE; i++)
		iconMaterial[i] = static_cast<UI*>(craftUI->Find("3_Icon_Material" + to_string(i + 1)));

	btnCreate = static_cast<UI*>(craftUI->Find("2_Btn_Crafting"));
}

Craft::~Craft()
{
}

void Craft::Init()
{
	// 초기화
	selectedRecipe = nullptr;				// 선택된 레시피 초기화
	for (int i = 0; i < RECIPE_SIZE; i++)
	{
		recipeItem[i] = nullptr;			// 레시피 정보 초기화
		hasRecipe[i] = false;				// 레시피가 존재하는지 여부 초기화
		IconChanger(iconRecipe[i]);			// 레시피 아이콘 초기화
	}

	for (int i = 0; i < MATERIAL_SIZE; i++)
	{
		needMaterial[i] = false;			// 재료가 필요한지 여부 초기화
		IconChanger(iconMaterial[i]);			// 재료 아이콘 초기화
	}

	// 레시피 업데이트
	RecipeUpdate();

	// 상호작용 배경 초기화
	btnRecipe[RECIPE_MOUSE_OVER]->visible = false;
	btnRecipe[RECIPE_MOUSE_CLICK]->visible = false;
}

void Craft::Release()
{
}

void Craft::Update()
{
	ImGui::Begin("CraftHierarchy");
	{
		craftUI->RenderHierarchy();
	}
	ImGui::End();

	// 탭 키를 누르면 크래프팅 창 열기
	if (INPUT->KeyDown('C'))
	{
		// 크래프팅 창이 열려있다면 닫기
		if (isOpen) isOpen = false;
		// 크래프팅 창이 닫혀있다면
		else
		{
			// 초기화 후
			Init();

			// 열기
			isOpen = true;
		}
	}

	if (isOpen)
	{
		craftUI->Update();
	}
}

void Craft::LateUpdate()
{
	if (isOpen)
	{
		// 마우스 오버시 슬롯 강조
		MouseOverRecipe();

		// 레시피 선택
		RecipeSelect();

		// 제작 버튼 업데이트
		CreateBtnUpdate();
	}
}

void Craft::PreRender()
{
}

void Craft::Render()
{
	if (isOpen)
	{
		craftUI->Render();

		for (int i = 0; i < RECIPE_SIZE; i++)
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
			RecipeIconUpdate(index);
		}
	}
}

void Craft::RecipeIconUpdate(int BtnIndex)
{
	// 버튼에 레시피가 있다면
	if (hasRecipe[BtnIndex])
	{
		// 해당 아이템으로 이미지 변경
		string iconFileName = GetIconFileName(recipeItem[BtnIndex]->enumName);
		IconChanger(iconRecipe[BtnIndex], iconFileName);
	}
	else
	{
		IconChanger(iconRecipe[BtnIndex]);
	}
}

void Craft::IconChanger(UI* icon, string path)
{
	path = "Item/" + path;
	SafeReset(icon->material->diffuseMap);
	icon->material->diffuseMap = RESOURCE->textures.Load(path);
 
}

void Craft::MouseOverRecipe()
{
	bool isMouseOver = false;

	// 마우스가 인벤토리 패널 위에 있다면
	if (panel->MouseOver())
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

				MaterialIconUpdate(selectedRecipe);
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
		appHalfHeight * detailUI->S._22 };

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
		float iconCorrectY = appHalfHeight * iconMaterial[0]->S._22 * 0.5f;
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

void Craft::MaterialIconUpdate(RecipeInfo* recipeInfo)
{
	auto it = selectedRecipe->material.begin();

	// 재료들을 순회 
	for (int i = 0; i < MATERIAL_SIZE; i++)
	{
		// 아직 표시할 재료가 남아있다면
		if (needMaterial[i])
		{
			// 위치 설정
			string targetName = "2_BG_Material" + to_string(i + 1);
			iconMaterial[i]->SetWorldPos(craftUI->Find(targetName)->GetWorldPos());

			// 아이콘 변경
			string iconFileName = GetIconFileName(it->first);
			IconChanger(iconMaterial[i], iconFileName);
			
			it++;
		}
		// 표시할 재료가 없다면
		else
		{
			// 투명	아이콘으로 변경
			IconChanger(iconMaterial[i]);
		}
	}
}

void Craft::CreateBtnUpdate()
{
	// 레시피가 선택되지 않았으면 리턴
	if (!selectedRecipe) return;

	string path = "Craft/";

	// 버튼 상태에 따라 이미지 변경
	// 버튼이 눌려있지 않은 상태
	if (btnCreateState == BtnState::NONE)
	{
		// 마우스가 버튼 위에 있다면
		if (btnCreate->MouseOver())
		{
			path += "button_highlight.png";
			// 버튼 이미지&상태 변경 (NORMAL -> HIGHLIGHT)
			btnCreate->material->diffuseMap = RESOURCE->textures.Load(path);
			btnCreateState = BtnState::MOUSE_OVER;
		}
	}
	// 마우스 오버 상태
	else if (btnCreateState == BtnState::MOUSE_OVER)
	{
		// 마우스가 버튼 위에 없다면
		if (!btnCreate->MouseOver())
		{
			path += "button_normal.png";
			// 버튼 이미지&상태 변경 (HIGHLIGHT -> NORMAL)
			btnCreate->material->diffuseMap = RESOURCE->textures.Load(path);
			btnCreateState = BtnState::NONE;
		}
		else if (INPUT->KeyDown(VK_LBUTTON))
		{
			path += "button_pressed.png";
			// 버튼 이미지&상태 변경 (HIGHLIGHT -> CLICK)
			btnCreate->material->diffuseMap = RESOURCE->textures.Load(path);
			btnCreateState = BtnState::MOUSE_CLICK;
		}
	}
	// 마우스 클릭 상태
	else if (btnCreateState == BtnState::MOUSE_CLICK)
	{
		// 마우스가 버튼 위에 없다면
		if (!btnCreate->MouseOver())
		{
			path += "button_normal.png";
			// 버튼 이미지&상태 변경 (CLICK -> NORMAL)
			btnCreate->material->diffuseMap = RESOURCE->textures.Load(path);
			btnCreateState = BtnState::NONE;
		}
		// 마우스를 떼었다면
		else if (INPUT->KeyUp(VK_LBUTTON))
		{
			path += "button_highlight.png";
			// 버튼 이미지&상태 변경 (CLICK -> HIGHLIGHT)
			btnCreate->material->diffuseMap = RESOURCE->textures.Load(path);
			btnCreateState = BtnState::MOUSE_OVER;

			ItemCreate();
		}
	}

}

bool Craft::ItemCreate()
{
	// 인벤토리를 순회해서 재료가 있는지 확인
	auto it = selectedRecipe->material.begin();
	for (int i = 0; i < MATERIAL_SIZE; i++)
	{
		// 아직 검사할 재료가 남아있다면
		if (needMaterial[i])
		{
			// 인벤토리에 재료가 충분한지 확인
			bool enoughMaterial = INVEN->CheckMaterial(it->first, it->second);

			// 재료가 있다면 다음 재료로
			if (enoughMaterial) it++;
			// 재료가 없다면 false 반환
			else return false;
		}
		// 더이상 검사할 재료가 없다면 반복문 탈출
		else break;
	}

	// 재료를 소모하고 
	it = selectedRecipe->material.begin();
	for (int i = 0; i < MATERIAL_SIZE; i++)
	{
		// 아직 검사할 재료가 남아있다면
		if (needMaterial[i])
		{
			// 인벤토리에서 재료 소모
			INVEN->UseMaterial(it->first, it->second);

			// 다음 재료로
			it++;
		}
		// 더이상 검사할 재료가 없다면 반복문 탈출
		else break;
	}

	// 아이템을 생성
	ItemProto* item = ItemProto::Create(selectedRecipe->enumName);
	OBJ->AddItem(item);

	// 인벤토리에 아이템을 추가
	INVEN->AddItem(item);

	// 인벤토리에 아이템이 추가되었다면 true 반환
	return true;

}

string Craft::GetIconFileName(Item item)
{
	switch (item)
	{
	case Item::StoneAxe:	return "axe_stone.png"; break;
	case Item::Woodpile:	return "woodpile.png"; break;
	case Item::Stone:		return "stone.png"; break;
	default:				return "ERROE: Undefined icon name";
	}
}
