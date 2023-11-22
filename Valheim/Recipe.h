#pragma once
class Recipe
{
private:
	map<string, bool>					discoveryItemList;		// 발견한 아이템 목록
	map<string, bool>					discoveryRecipeList;	// 발견한 레서피 목록
	map<string, set<string>>			recipeList;				// 레서피<레서피명, set<재료명>>

public:
	Recipe();
	~Recipe();

	bool DiscoveryItemUpdate(ItemProto* item);
	bool RecipeUpdate(ItemProto* item);

	map<string, bool>& GetDiscoveryRecipeList() { return discoveryRecipeList; }
};

