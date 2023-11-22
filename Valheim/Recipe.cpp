#include "stdafx.h"
#include "ItemProto.h"
#include "Recipe.h"

Recipe::Recipe()
{
    // �߰��� ������ ��� �ʱ�ȭ ================================================
	discoveryItemList[Item::StoneAxe] = false;
	discoveryItemList[Item::Woodpile] = false;

    // �߰��� ������ ��� �ʱ�ȭ ==============================================
    discoveryRecipeList[Item::StoneAxe] = false;
    //discoveryRecipeList["WorkBench"] = false;

    // ������ ��� �ʱ�ȭ ======================================================
    recipeList.emplace(Item::StoneAxe,      set<Item>{Item::Woodpile});          // �� ����
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

        // �������� ��ᰡ ��� �����Ǿ��ٸ�
        if (recipe.second.empty())
        {
			// �����Ǹ� �߰��� ������ ��Ͽ� �߰���
            discoveryRecipeList[recipe.first] = true;

            // ������ �߰� �޽��� ���
			cout << "Recipe '" << item->GetStringName() << "' discovered." << endl;
		}

        return true;
    }
    return false;
}
