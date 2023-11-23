#pragma once

#include "ItemProto.h"
//enum class Item;

class Recipe
{
	friend class Craft;

private:
	map<Item, bool>				discoveryItemList;		// 발견한 아이템 목록
	map<Item, bool>				discoveryRecipeList;	// 발견한 레서피 목록
	map<Item, set<Item>>		recipeList;				// 레서피<레서피명, set<재료명>>

private:
	struct RecipeInfo									// 실제 레서피 정보
	{
		Item			enumName;						// 레서피 이름(enum)
		wstring			wstringName;					// 레서피 이름(wstring)
		wstring			description;					// 레서피 설명
		map<Item, int>	material;						// 레서피 재료<재료명, 개수>
	};
	vector<RecipeInfo*> recipeInfo;						// 레서피 정보 목록

public:
	Recipe();
	~Recipe();

	bool DiscoveryItemUpdate(class ItemProto* item);	// 아이템 발견 업데이트 (새로운 아이템 획득시 호출)
	bool RecipeUpdate(class ItemProto* item);			// 레서피 업데이트 (새로운 아이템 획득시 호출)

	map<Item, bool>& GetRecipeList() { return discoveryRecipeList; }
	const struct RecipeInfo* GetRecipe(Item item);
};

