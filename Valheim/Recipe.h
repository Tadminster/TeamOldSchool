#pragma once

#include "ItemProto.h"
//enum class Item;

class Recipe
{
	friend class Craft;

private:
	map<Item, bool>				discoveryItemList;		// �߰��� ������ ���
	map<Item, bool>				discoveryRecipeList;	// �߰��� ������ ���
	map<Item, set<Item>>		recipeList;				// ������<�����Ǹ�, set<����>>

private:
	struct RecipeInfo									// ���� ������ ����
	{
		Item			enumName;						// ������ �̸�(enum)
		wstring			wstringName;					// ������ �̸�(wstring)
		wstring			description;					// ������ ����
		map<Item, int>	material;						// ������ ���<����, ����>
	};
	vector<RecipeInfo*> recipeInfo;						// ������ ���� ���

public:
	Recipe();
	~Recipe();

	bool DiscoveryItemUpdate(class ItemProto* item);	// ������ �߰� ������Ʈ (���ο� ������ ȹ��� ȣ��)
	bool RecipeUpdate(class ItemProto* item);			// ������ ������Ʈ (���ο� ������ ȹ��� ȣ��)

	map<Item, bool>& GetRecipeList() { return discoveryRecipeList; }
	const struct RecipeInfo* GetRecipe(Item item);
};

