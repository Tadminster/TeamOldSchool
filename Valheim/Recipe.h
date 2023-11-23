#pragma once

#include "ItemProto.h"
//enum class Item;

struct RecipeInfo									// ���� ������ ������ ������ ����ü
{
	Item			enumName;						// ������ �̸�(enum)
	wstring			wstringName;					// ������ �̸�(wstring)
	wstring			description;					// ������ ����
	map<Item, int>	material;						// ������ ���<����, ����>
};

class Recipe
{
	friend class Craft;

private:
	map<Item, bool>				discoveryItemList;		// �߰��� ������ ���
	map<Item, bool>				discoveryRecipeList;	// �߰��� ������ ���
	map<Item, set<Item>>		recipeList;				// ������<�����Ǹ�, set<����>>

private:
	vector<RecipeInfo*> recipeInfo;						// ������ ���� ���

public:
	Recipe();
	~Recipe();

	bool DiscoveryItemUpdate(class ItemProto* item);	// ������ �߰� ������Ʈ (���ο� ������ ȹ��� ȣ��)
	bool RecipeUpdate(class ItemProto* item);			// ������ ������Ʈ (���ο� ������ ȹ��� ȣ��)

	map<Item, bool>& GetRecipeList() { return discoveryRecipeList; }
	struct RecipeInfo* GetRecipe(Item item);
};

