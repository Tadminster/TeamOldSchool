#include "stdafx.h"
//#include "ItemProto.h"
#include "Recipe.h"

Recipe::Recipe()
{
    // �߰��� ������ ��� �ʱ�ȭ ================================================
    discoveryItemList[Item::Stone] = false;
    discoveryItemList[Item::StoneAxe] = false;
    discoveryItemList[Item::Woodpile] = false;

    // �߰��� ������ ��� �ʱ�ȭ ==============================================
    discoveryRecipeList[Item::StoneAxe] = false;
    //discoveryRecipeList["WorkBench"] = false;

    // ������ ��� �ʱ�ȭ ======================================================
    recipeList.emplace(Item::StoneAxe, set<Item>{Item::Woodpile, Item::Stone});          // �� ����

    // ������ ������ �ʱ�ȭ ============================================================
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
    // �߰��� ������ ��Ͽ��� �ش� key(������ �̸�)�� �����ϴ��� Ȯ��
    if (discoveryItemList.find(item->GetEnumName()) != discoveryItemList.end())
    {
        // �ش� �������� �����ϰ�, �߰ߵ� ���� ���ٸ�
        if (!discoveryItemList[item->GetEnumName()])
        {
            // �߰��� ������ ��Ͽ� �߰���
            discoveryItemList[item->GetEnumName()] = true;

            // ������ �߰� �޼��� ���
            cout << "Item '" << item->GetStringName() << "' discovered." << endl;

            // ������ ������Ʈ
            RecipeUpdate(item);

            return true;
        }
        else return false;
    }
    // Ű�� �������� ���� ��
    else cout << "Item '" << item->GetStringName() << "' not found in map." << endl;

    return false;
}

bool Recipe::RecipeUpdate(ItemProto* item)
{
    // ������ ����� ��ȸ��
    for (auto& recipe : recipeList)
    {
        // �������� ��Ḧ ���� Set���� �ش� �������� ������
        recipe.second.erase(item->GetEnumName());

        // �������� ��ᰡ ��� �����Ǿ��ٸ� (��� ��Ḧ ȹ����)
        if (recipe.second.empty())
        {
			// �����Ǹ� �߰��� ������ ��Ͽ� �߰���
            discoveryRecipeList[recipe.first] = true;

            // ����â�� ������ �߰�
            CRAFT->RecipeUpdate();

            // ������ �߰� �޽��� ��� (����׿�)
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
    // ������ ��� ��ȸ
    for (auto& recipe : recipeInfo)
    {
        // �������� enumName�� ���ڷ� ���� item�� ���ٸ�
        if (recipe->enumName == item)
        {
            // �ش� ������ ����ü ����
            return recipe;
        }
    }
}
