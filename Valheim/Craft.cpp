#include "stdafx.h"
#include "ItemProto.h"
#include "Recipe.h"
#include "Craft.h"

Craft::Craft()
{
	// ��� ũ�������� ���� �ʱ�ȭ
	for (int i = 0; i < RECIPE_SIZE; i++)
	{
		recipeItem[i] = nullptr;
		hasRecipe[i] = false;
	}
	selectedRecipe = nullptr;
	btnCreateState = BtnState::NONE;

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
	// �ʱ�ȭ
	selectedRecipe = nullptr;				// ���õ� ������ �ʱ�ȭ
	for (int i = 0; i < RECIPE_SIZE; i++)
	{
		recipeItem[i] = nullptr;			// ������ ���� �ʱ�ȭ
		hasRecipe[i] = false;				// �����ǰ� �����ϴ��� ���� �ʱ�ȭ
		IconChanger(iconRecipe[i]);			// ������ ������ �ʱ�ȭ
	}

	for (int i = 0; i < MATERIAL_SIZE; i++)
	{
		needMaterial[i] = false;			// ��ᰡ �ʿ����� ���� �ʱ�ȭ
		IconChanger(iconMaterial[i]);			// ��� ������ �ʱ�ȭ
	}

	// ������ ������Ʈ
	RecipeUpdate();

	// ��ȣ�ۿ� ��� �ʱ�ȭ
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

	// �� Ű�� ������ ũ������ â ����
	if (INPUT->KeyDown('C'))
	{
		// ũ������ â�� �����ִٸ� �ݱ�
		if (isOpen) isOpen = false;
		// ũ������ â�� �����ִٸ�
		else
		{
			// �ʱ�ȭ ��
			Init();

			// ����
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
		// ���콺 ������ ���� ����
		MouseOverRecipe();

		// ������ ����
		RecipeSelect();

		// ���� ��ư ������Ʈ
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
				// �ؽ�Ʈ ��ġ ����
				textRecipe[i].left = App.GetHalfWidth() * (btnRecipe[i]->GetWorldPos().x + 1.0f) + textRecipeCorrect.x;
				textRecipe[i].right = textRecipe[i].left + 1000;
				textRecipe[i].top = App.GetHalfHeight() * (1.0f - btnRecipe[i]->GetWorldPos().y) + textRecipeCorrect.y;
				textRecipe[i].bottom = textRecipe[i].top + 200;

				// ������ ������ ������ ǥ��
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
			// ������ ������ �̸�
			DWRITE->RenderText(
				selectedRecipe->wstringName,
				textDetailName,
				20.0f,
				L"Arial",
				Color(1.0f, 1.0f, 1.0f, 0.0f),
				DWRITE_FONT_WEIGHT_SEMI_BOLD,
				DWRITE_FONT_STYLE_ITALIC,
				DWRITE_FONT_STRETCH_EXPANDED);

			// ������ ������ ����
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
				// ǥ���� ��ᰡ �ִٸ�
				if (needMaterial[i])
				{
					// ���� ǥ��
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

	// ������ ����� ��ȸ
	for (int index = 0; auto recipe : discoveryRecipeList)
	{
		// �����ǰ� �رݵǾ��ٸ�
		if (recipe.second)
		{
			// ������ �������� ����
			recipeItem[index] = RECIPE->GetRecipe(recipe.first);

			// �����ǰ� ���絥���� ������Ʈ
			hasRecipe[index] = true;

			// ������ ���� ��ư ������Ʈ
			RecipeIconUpdate(index);
		}
	}
}

void Craft::RecipeIconUpdate(int BtnIndex)
{
	// ��ư�� �����ǰ� �ִٸ�
	if (hasRecipe[BtnIndex])
	{
		// �ش� ���������� �̹��� ����
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

	// ���콺�� �κ��丮 �г� ���� �ִٸ�
	if (panel->MouseOver())
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
			if (hasRecipe[i])
			{
				// ������ ������ ����
				selectedRecipe = recipeItem[i];

				// ������ ����� �ش� ��ư ��ġ�� �̵�
				btnRecipe[RECIPE_MOUSE_CLICK]->SetLocalPos(btnRecipe[i]->GetLocalPos());

				// ������ ��� visible
				btnRecipe[RECIPE_MOUSE_CLICK]->visible = true;

				// ������ â ������Ʈ
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

	//������ â ũ�� ��� (���μ��� ����ũ��, Pivot�� �߾��̹Ƿ�)
	Vector2 detailSize{
		appHalfWidth * detailUI->S._11,
		appHalfHeight * detailUI->S._22 };

	// ������ â ��ġ ���
	Vector2 Baseline{
		appHalfWidth * (detailUI->GetWorldPos().x + 1.0f),
		appHalfHeight * (1.0f - detailUI->GetWorldPos().y) };

	// �ؽ�Ʈ ��ġ ����
	{
		// ������ �̸�
		textDetailName.left = Baseline.x - detailSize.x * 0.8f;
		textDetailName.right = textDetailName.left + 1000;
		textDetailName.top = Baseline.y - detailSize.y * 0.85f;
		textDetailName.bottom = textDetailName.top + 200;

		// ����
		textDetailExplain.left = textDetailName.left;
		textDetailExplain.right = textDetailName.right;
		textDetailExplain.top = Baseline.y - detailSize.y * 0.7f;
		textDetailExplain.bottom = textDetailExplain.top + 1000;

		// ��� ����
		float iconCorrectY = appHalfHeight * iconMaterial[0]->S._22 * 0.5f;
		for (int i = 0; i < MATERIAL_SIZE; i++)
		{
			textDetailMaterialNum[i].left = appHalfWidth * (iconMaterial[i]->GetWorldPos().x + 1.0f);
			textDetailMaterialNum[i].right = textDetailMaterialNum[i].left + 1000;
			textDetailMaterialNum[i].top = appHalfHeight * (1.0f - iconMaterial[i]->GetWorldPos().y) + iconCorrectY;
			textDetailMaterialNum[i].bottom = textDetailMaterialNum[i].top + 200;
		}
	}

	// ǥ���� ��� �ʱ�ȭ
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

	// ������ ��ȸ 
	for (int i = 0; i < MATERIAL_SIZE; i++)
	{
		// ���� ǥ���� ��ᰡ �����ִٸ�
		if (needMaterial[i])
		{
			// ��ġ ����
			string targetName = "2_BG_Material" + to_string(i + 1);
			iconMaterial[i]->SetWorldPos(craftUI->Find(targetName)->GetWorldPos());

			// ������ ����
			string iconFileName = GetIconFileName(it->first);
			IconChanger(iconMaterial[i], iconFileName);
			
			it++;
		}
		// ǥ���� ��ᰡ ���ٸ�
		else
		{
			// ����	���������� ����
			IconChanger(iconMaterial[i]);
		}
	}
}

void Craft::CreateBtnUpdate()
{
	// �����ǰ� ���õ��� �ʾ����� ����
	if (!selectedRecipe) return;

	string path = "Craft/";

	// ��ư ���¿� ���� �̹��� ����
	// ��ư�� �������� ���� ����
	if (btnCreateState == BtnState::NONE)
	{
		// ���콺�� ��ư ���� �ִٸ�
		if (btnCreate->MouseOver())
		{
			path += "button_highlight.png";
			// ��ư �̹���&���� ���� (NORMAL -> HIGHLIGHT)
			btnCreate->material->diffuseMap = RESOURCE->textures.Load(path);
			btnCreateState = BtnState::MOUSE_OVER;
		}
	}
	// ���콺 ���� ����
	else if (btnCreateState == BtnState::MOUSE_OVER)
	{
		// ���콺�� ��ư ���� ���ٸ�
		if (!btnCreate->MouseOver())
		{
			path += "button_normal.png";
			// ��ư �̹���&���� ���� (HIGHLIGHT -> NORMAL)
			btnCreate->material->diffuseMap = RESOURCE->textures.Load(path);
			btnCreateState = BtnState::NONE;
		}
		else if (INPUT->KeyDown(VK_LBUTTON))
		{
			path += "button_pressed.png";
			// ��ư �̹���&���� ���� (HIGHLIGHT -> CLICK)
			btnCreate->material->diffuseMap = RESOURCE->textures.Load(path);
			btnCreateState = BtnState::MOUSE_CLICK;
		}
	}
	// ���콺 Ŭ�� ����
	else if (btnCreateState == BtnState::MOUSE_CLICK)
	{
		// ���콺�� ��ư ���� ���ٸ�
		if (!btnCreate->MouseOver())
		{
			path += "button_normal.png";
			// ��ư �̹���&���� ���� (CLICK -> NORMAL)
			btnCreate->material->diffuseMap = RESOURCE->textures.Load(path);
			btnCreateState = BtnState::NONE;
		}
		// ���콺�� �����ٸ�
		else if (INPUT->KeyUp(VK_LBUTTON))
		{
			path += "button_highlight.png";
			// ��ư �̹���&���� ���� (CLICK -> HIGHLIGHT)
			btnCreate->material->diffuseMap = RESOURCE->textures.Load(path);
			btnCreateState = BtnState::MOUSE_OVER;

			ItemCreate();
		}
	}

}

bool Craft::ItemCreate()
{
	// �κ��丮�� ��ȸ�ؼ� ��ᰡ �ִ��� Ȯ��
	auto it = selectedRecipe->material.begin();
	for (int i = 0; i < MATERIAL_SIZE; i++)
	{
		// ���� �˻��� ��ᰡ �����ִٸ�
		if (needMaterial[i])
		{
			// �κ��丮�� ��ᰡ ������� Ȯ��
			bool enoughMaterial = INVEN->CheckMaterial(it->first, it->second);

			// ��ᰡ �ִٸ� ���� ����
			if (enoughMaterial) it++;
			// ��ᰡ ���ٸ� false ��ȯ
			else return false;
		}
		// ���̻� �˻��� ��ᰡ ���ٸ� �ݺ��� Ż��
		else break;
	}

	// ��Ḧ �Ҹ��ϰ� 
	it = selectedRecipe->material.begin();
	for (int i = 0; i < MATERIAL_SIZE; i++)
	{
		// ���� �˻��� ��ᰡ �����ִٸ�
		if (needMaterial[i])
		{
			// �κ��丮���� ��� �Ҹ�
			INVEN->UseMaterial(it->first, it->second);

			// ���� ����
			it++;
		}
		// ���̻� �˻��� ��ᰡ ���ٸ� �ݺ��� Ż��
		else break;
	}

	// �������� ����
	ItemProto* item = ItemProto::Create(selectedRecipe->enumName);
	OBJ->AddItem(item);

	// �κ��丮�� �������� �߰�
	INVEN->AddItem(item);

	// �κ��丮�� �������� �߰��Ǿ��ٸ� true ��ȯ
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
