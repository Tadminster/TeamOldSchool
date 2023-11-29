#include "stdafx.h"
//#include "ItemProto.h"
#include "Notification.h"
#include "Recipe.h"

Recipe::Recipe()
{
    // �߰��� ������ ��� �ʱ�ȭ ================================================
    discoveryItemList[Item::Club] = false;
    discoveryItemList[Item::StoneAxe] = false;
    discoveryItemList[Item::StonePickaxe] = false;
    discoveryItemList[Item::WoodShield] = false;

    discoveryItemList[Item::Stone] = false;
    discoveryItemList[Item::Woodpile] = false;
    discoveryItemList[Item::Leather] = false;

    // �߰��� ������ ��� �ʱ�ȭ ==============================================
    discoveryRecipeList[Item::Club] = false;
    discoveryRecipeList[Item::StoneAxe] = false;
    discoveryRecipeList[Item::StonePickaxe] = false;
    discoveryRecipeList[Item::WoodShield] = false;

    // ������ ��� �ʱ�ȭ ======================================================
    recipeList.emplace(Item::Club,          set<Item>{Item::Woodpile});                 // ������
    recipeList.emplace(Item::StoneAxe,      set<Item>{Item::Woodpile, Item::Stone});    // �� ����
    recipeList.emplace(Item::StonePickaxe,  set<Item>{Item::Woodpile, Item::Stone});    // �� ���
    recipeList.emplace(Item::StonePickaxe,  set<Item>{Item::Woodpile, Item::Stone, Item::Leather});    // ��������

    // ������ ������ �ʱ�ȭ ============================================================
    recipeInfo.emplace_back(new RecipeInfo{ 
		Item::Club, L"������", 
		L"������ �ٵ�� ���� ������. \n���������� �����մϴ�.\n",
		{{Item::Woodpile, 3}} });

    recipeInfo.emplace_back(new RecipeInfo{ 
        Item::StoneAxe, L"�� ����", 
        L"���������� ���� �ݴٺ��� ���� \n���� �� �ִ� ����.\n",
        {{Item::Woodpile, 5}, {Item::Stone, 2}} });

    recipeInfo.emplace_back(new RecipeInfo{
        Item::StonePickaxe, L"�� ���",
        L"�ϼ��� �μ� �� �ִ� ���. \n���� ������� ���� ��������.\n",
        {{Item::Woodpile, 2}, {Item::Stone, 5}} });

    recipeInfo.emplace_back(new RecipeInfo{
    Item::StonePickaxe, L"���� ���� ����",
    L"�ܼ��� ���� �������� �ϳ� \n�ܴ��ϴ�.\n",
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
            //cout << "Item '" << item->GetStringName() << "' discovered." << endl;
            UIM->AddNotification(item->GetEnumName(), NotificationType::Discovery);

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

        // �߰ߵ��� ���� ����Ʈ�̰�
        // �������� ��Ḧ ��� ��Ḧ ȹ���ߴٸ� (�����Ǿ��ٸ�)
        if (!discoveryRecipeList[recipe.first] &&recipe.second.empty())
        {
            // ������ �߰� �˸�â ���
            UIM->AddNotification(recipe.first, NotificationType::Unlock);

			// �����Ǹ� �߰��� ������ ��Ͽ� �߰���
            discoveryRecipeList[recipe.first] = true;

            // ����â�� ������ �߰�
            CRAFT->RecipeUpdate();

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

    // ��ġ�ϴ� �����ǰ� ������
    return nullptr;
}
