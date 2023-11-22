#include "stdafx.h"
#include "ItemProto.h"
#include "Recipe.h"

Recipe::Recipe()
{
    // 발견한 아이템 목록 초기화 ================================================
	discoveryItemList["StoneAxe"] = false;
	discoveryItemList["Woodpile"] = false;

    // 발견한 레시피 목록 초기화 ==============================================
    discoveryRecipeList["StoneAxe"] = false;
    discoveryRecipeList["WorkBench"] = false;

    // 레시피 목록 초기화 ======================================================
    recipeList.emplace("StoneAxe", set<string>{"Wood", "Stone"});
    recipeList.emplace("WorkBench", set<string>{"Wood"});
}

Recipe::~Recipe()
{
}

bool Recipe::DiscoveryItemUpdate(ItemProto* item)
{
    string itemName = item->GetName();

    // 발견한 아이템 목록에서 해당 key(아이템 이름)이 존재하는지 확인
    if (discoveryItemList.find(itemName) != discoveryItemList.end())
    {
        // 해당 아이템이 존재하고, 발견된 적이 없다면
        if (!discoveryItemList[itemName])
        {
            // 발견한 아이템 목록에 추가함
            discoveryItemList[itemName] = true;
            // 아이템 발견 메세지 출력
            cout << "Item '" << itemName << "' discovered." << endl;
            return true;
        }
        else return false;
    }
    // 키가 존재하지 않을 때
    else cout << "Item '" << itemName << "' not found in map." << endl;

    return false;
}

bool Recipe::RecipeUpdate(ItemProto* item)
{
    string itemName = item->GetName();

    // 레서피 목록을 순회함
    for (auto& recipe : recipeList)
    {
        // 레서피의 재료를 담은 Set에서 해당 아이템을 삭제함
        recipe.second.erase(itemName);

        // 레서피의 재료가 모두 삭제되었다면
        if (recipe.second.empty())
        {
			// 레서피를 발견한 아이템 목록에 추가함
            discoveryRecipeList[recipe.first] = true;

            // 레서피 발견 메시지 출력
			cout << "Recipe '" << recipe.first << "' discovered." << endl;
		}

        return true;
    }
    return false;
}
