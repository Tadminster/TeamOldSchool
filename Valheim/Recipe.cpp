#include "stdafx.h"
//#include "ItemProto.h"
#include "Recipe.h"

Recipe::Recipe()
{
    // 발견한 아이템 목록 초기화 ================================================
    discoveryItemList[Item::Stone] = false;
    discoveryItemList[Item::StoneAxe] = false;
    discoveryItemList[Item::Woodpile] = false;

    // 발견한 레시피 목록 초기화 ==============================================
    discoveryRecipeList[Item::StoneAxe] = false;
    //discoveryRecipeList["WorkBench"] = false;

    // 레시피 목록 초기화 ======================================================
    recipeList.emplace(Item::StoneAxe, set<Item>{Item::Woodpile, Item::Stone});          // 돌 도끼

    // 레시피 데이터 초기화 ============================================================
    recipeInfo.emplace_back(new RecipeInfo{ 
        Item::StoneAxe, L"StoneAxe", 
        L"Axe is a tool used to cut down trees.",
        {{Item::Woodpile, 5}, {Item::Stone, 2}} });
}

Recipe::~Recipe()
{
}

bool Recipe::DiscoveryItemUpdate(ItemProto* item)
{
    // 발견한 아이템 목록에서 해당 key(아이템 이름)이 존재하는지 확인
    if (discoveryItemList.find(item->GetEnumName()) != discoveryItemList.end())
    {
        // 해당 아이템이 존재하고, 발견된 적이 없다면
        if (!discoveryItemList[item->GetEnumName()])
        {
            // 발견한 아이템 목록에 추가함
            discoveryItemList[item->GetEnumName()] = true;

            // 아이템 발견 메세지 출력
            cout << "Item '" << item->GetStringName() << "' discovered." << endl;

            // 레서피 업데이트
            RecipeUpdate(item);

            return true;
        }
        else return false;
    }
    // 키가 존재하지 않을 때
    else cout << "Item '" << item->GetStringName() << "' not found in map." << endl;

    return false;
}

bool Recipe::RecipeUpdate(ItemProto* item)
{
    // 레서피 목록을 순회함
    for (auto& recipe : recipeList)
    {
        // 레서피의 재료를 담은 Set에서 해당 아이템을 삭제함
        recipe.second.erase(item->GetEnumName());

        // 레서피의 재료가 모두 삭제되었다면 (모든 재료를 획득함)
        if (recipe.second.empty())
        {
			// 레서피를 발견한 아이템 목록에 추가함
            discoveryRecipeList[recipe.first] = true;

            // 제작창에 레서피 추가
            CRAFT->RecipeUpdate();

            // 레서피 발견 메시지 출력 (디버그용)
            cout << "Recipe ";
            switch (recipe.first)
            {
            case Item::StoneAxe: cout << "'StoneAxe'"; break;
            }
            cout << " discovered." << endl;
		}

        return true;
    }
    return false;
}

RecipeInfo* Recipe::GetRecipe(Item item)
{
    // 레서피 목록 순회
    for (auto& recipe : recipeInfo)
    {
        // 레서피의 enumName과 인자로 받은 item이 같다면
        if (recipe->enumName == item)
        {
            // 해당 레서피 구조체 리턴
            return recipe;
        }
    }
}
