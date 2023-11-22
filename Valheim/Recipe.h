#pragma once

enum class Item;

class Recipe
{
private:
	map<Item, bool>	discoveryItemList;		// 발견한 아이템 목록
	map<Item, bool>				discoveryRecipeList;	// 발견한 레서피 목록
	map<Item, set<Item>>		recipeList;				// 레서피<레서피명, set<재료명>>

public:
	Recipe();
	~Recipe();

	bool DiscoveryItemUpdate(class ItemProto* item);
	bool RecipeUpdate(class ItemProto* item);

	map<Item, bool>& GetDiscoveryRecipeList() { return discoveryRecipeList; }
};

