#pragma once
#define MATERIAL_SIZE			4		// 재료 크기
#define RECIPE_SIZE				9		// 레서피 크기
#define RECIPE_MOUSE_OVER		9		// 마우스 오버
#define RECIPE_MOUSE_CLICK		10		// 마우스 클릭

#include "Recipe.h"

class Craft
{
	friend class Player;

private:
	Item	recipeItem[RECIPE_SIZE];		// 레시피 아이템
	// 이미지===========================================================================================
	UI*		craftUI;						// 크래프팅 UI	
	UI*		panel;							// 크래프팅 패널을 가리킬 포인터
	UI*		btnRecipe[RECIPE_SIZE + 2];		// 레시피 선택 버튼을 가리킬 포인터(0~8 레시피, 9 마우스오버, 10 마우스클릭)
	UI*		iconMaterial[MATERIAL_SIZE];	// 재료 아이콘을 가리킬 포인터

	// 크래프팅 창 조작=================================================================================
	bool	hasRecipe[RECIPE_SIZE];			// 레시피가 존재하는지 여부

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

