#include "stdafx.h"
#include "ItemProto.h"
#include "Recipe.h"

Recipe::Recipe()
{
    // �߰��� ������ ��� �ʱ�ȭ ================================================
	discoveryItemList["StoneAxe"] = false;
	discoveryItemList["Woodpile"] = false;

    // �߰��� ������ ��� �ʱ�ȭ ==============================================
    discoveryRecipeList["StoneAxe"] = false;
    discoveryRecipeList["WorkBench"] = false;

    // ������ ��� �ʱ�ȭ ======================================================
    recipeList.emplace("StoneAxe", set<string>{"Wood", "Stone"});
    recipeList.emplace("WorkBench", set<string>{"Wood"});
}

Recipe::~Recipe()
{
}

bool Recipe::DiscoveryItemUpdate(ItemProto* item)
{
    string itemName = item->GetName();

    // �߰��� ������ ��Ͽ��� �ش� key(������ �̸�)�� �����ϴ��� Ȯ��
    if (discoveryItemList.find(itemName) != discoveryItemList.end())
    {
        // �ش� �������� �����ϰ�, �߰ߵ� ���� ���ٸ�
        if (!discoveryItemList[itemName])
        {
            // �߰��� ������ ��Ͽ� �߰���
            discoveryItemList[itemName] = true;
            // ������ �߰� �޼��� ���
            cout << "Item '" << itemName << "' discovered." << endl;
            return true;
        }
        else return false;
    }
    // Ű�� �������� ���� ��
    else cout << "Item '" << itemName << "' not found in map." << endl;

    return false;
}

bool Recipe::RecipeUpdate(ItemProto* item)
{
    string itemName = item->GetName();

    // ������ ����� ��ȸ��
    for (auto& recipe : recipeList)
    {
        // �������� ��Ḧ ���� Set���� �ش� �������� ������
        recipe.second.erase(itemName);

        // �������� ��ᰡ ��� �����Ǿ��ٸ�
        if (recipe.second.empty())
        {
			// �����Ǹ� �߰��� ������ ��Ͽ� �߰���
            discoveryRecipeList[recipe.first] = true;

            // ������ �߰� �޽��� ���
			cout << "Recipe '" << recipe.first << "' discovered." << endl;
		}

        return true;
    }
    return false;
}
