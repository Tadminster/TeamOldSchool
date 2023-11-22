#pragma once
class Recipe
{
private:
	map<string, bool>					discoveryItemList;		// �߰��� ������ ���
	map<string, bool>					discoveryRecipeList;	// �߰��� ������ ���
	map<string, set<string>>			recipeList;				// ������<�����Ǹ�, set<����>>

public:
	Recipe();
	~Recipe();

	bool DiscoveryItemUpdate(ItemProto* item);
	bool RecipeUpdate(ItemProto* item);

	map<string, bool>& GetDiscoveryRecipeList() { return discoveryRecipeList; }
};

