#pragma once

enum class Item;

class Recipe
{
private:
	map<Item, bool>	discoveryItemList;		// �߰��� ������ ���
	map<Item, bool>				discoveryRecipeList;	// �߰��� ������ ���
	map<Item, set<Item>>		recipeList;				// ������<�����Ǹ�, set<����>>

public:
	Recipe();
	~Recipe();

	bool DiscoveryItemUpdate(class ItemProto* item);
	bool RecipeUpdate(class ItemProto* item);

	map<Item, bool>& GetDiscoveryRecipeList() { return discoveryRecipeList; }
};

