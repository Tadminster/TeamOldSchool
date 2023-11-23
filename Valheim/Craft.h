#pragma once
#define MATERIAL_SIZE			4		// ��� ũ��
#define RECIPE_SIZE				9		// ������ ũ��
#define RECIPE_MOUSE_OVER		9		// ���콺 ����
#define RECIPE_MOUSE_CLICK		10		// ���콺 Ŭ��

#include "Recipe.h"

class Craft
{
	friend class Player;

private:
	Item	recipeItem[RECIPE_SIZE];		// ������ ������
	// �̹���===========================================================================================
	UI*		craftUI;						// ũ������ UI	
	UI*		panel;							// ũ������ �г��� ����ų ������
	UI*		btnRecipe[RECIPE_SIZE + 2];		// ������ ���� ��ư�� ����ų ������(0~8 ������, 9 ���콺����, 10 ���콺Ŭ��)
	UI*		iconMaterial[MATERIAL_SIZE];	// ��� �������� ����ų ������

	// ũ������ â ����=================================================================================
	bool	hasRecipe[RECIPE_SIZE];			// �����ǰ� �����ϴ��� ����

public:
	Craft();
	~Craft();

	void Init();
	void Release();
	void Update();
	void LateUpdate();
	void PreRender();
	void Render();
	void ResizeScreen();

	void RecipeUpdate();
	void MouseOverRecipe();
	void RecipeSelect();

	void ApplyMaterialIcon(Recipe::RecipeInfo recipeInfo);
	string GetIconFileName(Item item);
};

