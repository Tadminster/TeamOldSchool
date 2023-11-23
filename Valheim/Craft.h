#pragma once
#define MATERIAL_SIZE			4		// 재료 크기
#define RECIPE_SIZE				9		// 레서피 크기
#define RECIPE_MOUSE_OVER		9		// 마우스 오버
#define RECIPE_MOUSE_CLICK		10		// 마우스 클릭

#include "Recipe.h"

// 제작 버튼 상태
enum class BtnState { NONE, MOUSE_OVER, MOUSE_CLICK };

class Craft
{
	friend class Player;

private:
	RecipeInfo*	recipeItem[RECIPE_SIZE];		// 레시피 정보
	RecipeInfo*	selectedRecipe;					// 선택된 레시피 정보
	// 이미지===========================================================================================
	UI*			craftUI;						// 크래프팅 UI	
	UI*			panel;							// 크래프팅 패널을 가리킬 포인터
	UI*			btnRecipe[RECIPE_SIZE + 2];		// 레시피 선택 버튼을 가리킬 포인터(0~8 레시피, 9 마우스오버, 10 마우스클릭)
	UI*			iconRecipe[RECIPE_SIZE];		// 레시피 아이콘을 가리킬 포인터
	RECT		textRecipe[RECIPE_SIZE];		// 레시피 텍스트를 표시할 영역
	Vector2     textRecipeCorrect{-20, -10};	// 레시피 텍스트 X, Y 보정값

	UI* 		detailUI;						// 레시피 상세정보창을 가리킬 포인터
	RECT		textDetailName;					// 레시피 상세정보 텍스트(이름)
	RECT		textDetailExplain;				// 레시피 상세정보 텍스트(설명)
	RECT		textDetailMaterialNum[4];		// 레시피 상세정보 텍스트(재료 개수)
	UI*			iconMaterial[MATERIAL_SIZE];	// 재료 아이콘을 가리킬 포인터
	UI*			btnCreate;						// 제작 버튼을 가리킬 포인터
	BtnState	btnCreateState;					// 제작 버튼 상태
	// 크래프팅 창 조작=================================================================================
	bool		hasRecipe[RECIPE_SIZE];			// 레시피가 존재하는지 여부
	bool		needMaterial[MATERIAL_SIZE];	// 재료가 필요한지 여부
	bool		isOpen{ false };				// 크래프팅 창이 열려있는지 여부

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

	// @brief 아이템 아이콘	변경
	// @param icon 초기화할 아이콘
	// @param path 아이콘 경로(default: Empty)
	void IconChanger(UI* icon, string path = "Empty.png");

	void RecipeUpdate();								// 레시피 정보 업데이트
	void RecipeIconUpdate(int BtnIndex);				// 레시피 아이콘 업데이트
	void MouseOverRecipe();								// 레시피 마우스 오버
	void RecipeSelect();								// 레시피 선택

	void RecipeDetailUpdate();							// 레시피 상세정보 업데이트
	void MaterialIconUpdate(RecipeInfo* recipeInfo);	// 재료 아이콘 업데이트
	void CreateBtnUpdate();								// 제작 버튼 업데이트
	bool ItemCreate();									// 아이템 제작

	string GetIconFileName(Item item);
};

