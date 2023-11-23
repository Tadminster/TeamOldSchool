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
	RecipeInfo*	recipeItem[RECIPE_SIZE];		// ������ ����
	RecipeInfo*	selectedRecipe;					// ���õ� ������ ����
	// �̹���===========================================================================================
	UI*			craftUI;						// ũ������ UI	
	UI*			panel;							// ũ������ �г��� ����ų ������
	UI*			btnRecipe[RECIPE_SIZE + 2];		// ������ ���� ��ư�� ����ų ������(0~8 ������, 9 ���콺����, 10 ���콺Ŭ��)
	UI*			iconRecipe[RECIPE_SIZE];		// ������ �������� ����ų ������
	RECT		textRecipe[RECIPE_SIZE];		// ������ �ؽ�Ʈ�� ǥ���� ����
	Vector2     textRecipeCorrect{-20, -10};	// ������ �ؽ�Ʈ X, Y ������
	UI*			iconMaterial[MATERIAL_SIZE];	// ��� �������� ����ų ������

	UI* 		detailUI;						// ������ ������â�� ����ų ������
	RECT		textDetailName;					// ������ ������ �ؽ�Ʈ(�̸�)
	RECT		textDetailExplain;				// ������ ������ �ؽ�Ʈ(����)
	RECT		textDetailMaterialNum[4];		// ������ ������ �ؽ�Ʈ(��� ����)
	// ũ������ â ����=================================================================================
	bool		hasRecipe[RECIPE_SIZE];			// �����ǰ� �����ϴ��� ����
	bool		needMaterial[MATERIAL_SIZE];	// ��ᰡ �ʿ����� ����

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
	void RecipeButtonUpdate(int BtnIndex);
	void MouseOverRecipe();
	void RecipeSelect();

	void RecipeDetailUpdate();

	void ApplyMaterialIcon(RecipeInfo recipeInfo);
	string GetIconFileName(Item item);
};

