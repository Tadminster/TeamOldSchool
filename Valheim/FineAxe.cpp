#include "stdafx.h"
#include "ItemProto.h"
#include "FineAxe.h"

FineAxe::FineAxe()
{
	static int index = 0;
	actor = Actor::Create("FineAxe");
	actor->LoadFile("Item_FineAxe.xml");
	actor->name = "Item_FineAxe" + to_string(index);

	icon = UI::Create("FineAxeIcon");
	icon->LoadFile("Icon_FineAxe.xml");
	icon->name = "FineAxeIcon" + to_string(index++);
	tooltipBoxScaleY = 0.8f;

	ItemProto::Init();

	//=========================
	enumName = Item::FineAxe;
	type = ItemType::Weapon;
	wType = WeaponType::Axe;
	state = ItemState::OnGround;
	//=========================
	stringName = "FineAxe";

	damage = 20;
	maxDurability = 100;
	curDurability = maxDurability;
	weight = 2;
}

FineAxe::~FineAxe()
{

}

void FineAxe::Init()
{

}

void FineAxe::Release()
{
}

void FineAxe::Update()
{
	//ImGui::Begin("ItemHierarchy");
	//{
	//	actor->RenderHierarchy();
	//	icon->RenderHierarchy();
	//}
	//ImGui::End();


	ItemProto::Update();
}

void FineAxe::LateUpdate()
{
	//ItemProto::LateUpdate();
}

void FineAxe::Render()
{
	ItemProto::Render();
}

void FineAxe::RenderHierarchy()
{

}

wstring FineAxe::GetExplain()
{
	wstring exp = L"뭐든 베어버릴 수 있을 것 같은 \n고급 도끼입니다.\n";
	wstring exp_sub1 = L"\n한손무기";
	wstring exp_sub2 = L"\n무게: " + to_wstring(weight);
	wstring exp_sub3 = L"\n내구도: " + to_wstring(curDurability) + L"/" + to_wstring(maxDurability);
	wstring exp_sub4 = L"\n공격력: " + to_wstring(damage);

	return exp + exp_sub1 + exp_sub2 + exp_sub3 + exp_sub4;
}

bool FineAxe::IsDestroyed()
{
	return false;
}

void FineAxe::DestructionEvent()
{
}

void FineAxe::Use()
{
	if (state == ItemState::OnInventory)
	{
		state = ItemState::Equipped;
		PLAYER->EquipToHand(this);
	}
	else if (state == ItemState::Equipped)
	{
		state = ItemState::OnInventory;
		PLAYER->ReleaseToHand(this);
	}
}

void FineAxe::Fix()
{
	curDurability = maxDurability;
}

