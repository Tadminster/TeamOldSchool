#include "stdafx.h"
//#include "ItemProto.h"
#include "Recipe.h"

Recipe::Recipe()
{
    // �߰��� ������ ��� �ʱ�ȭ ================================================
    discoveryItemList[Item::StoneAxe] = false;
    discoveryItemList[Item::StonePickaxe] = false;

    discoveryItemList[Item::Stone] = false;
    discoveryItemList[Item::Woodpile] = false;
    discoveryItemList[Item::Leather] = false;

    // �߰��� ������ ��� �ʱ�ȭ ==============================================
    discoveryRecipeList[Item::StoneAxe] = false;
    discoveryRecipeList[Item::StonePickaxe] = false;

    // ������ ��� �ʱ�ȭ ======================================================
    recipeList.emplace(Item::StoneAxe,      set<Item>{Item::Woodpile, Item::Stone});      // �� ����
    recipeList.emplace(Item::StonePickaxe,  set<Item>{Item::Woodpile, Item::Stone});      // �� ���

    // ������ ������ �ʱ�ȭ ============================================================
    recipeInfo.emplace_back(new RecipeInfo{ 
        Item::StoneAxe, L"�� ����", 
        L"���������� ���� �ݴٺ��� ���� \n���� �� �ִ� ����.",
        {{Item::Woodpile, 5}, {Item::Stone, 2}} });

    recipeInfo.emplace_back(new RecipeInfo{
    Item::StonePickaxe, L"�� ���",
    L"�ϼ��� �μ� �� �ִ� ���. \n���� ������� ���� ��������.",
    {{Item::Woodpile, 2}, {Item::Stone, 5}} });
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

void Recipe::RecipeUpdate(ItemProto* item)
{
    // ������ ����� ��ȸ��
    for (auto& recipe : recipeList)
    {
        // �������� ��Ḧ ���� Set���� �ش� �������� ������
        recipe.second.erase(item->GetEnumName());

        // �������� ��Ḧ ��� ��Ḧ ȹ���ߴٸ� (�����Ǿ��ٸ�)
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
            case Item::StonePickaxe: cout << "'StonePickaxe'"; break;
            }
            cout << " discovered." << endl;
		}
    }
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
