#include "stdafx.h"
#include "ItemProto.h"
#include "StonePickaxe.h"

StonePickaxe::StonePickaxe()
{
	static int index = 0;
	actor = Actor::Create("StonePickaxe");
	actor->LoadFile("StonePickaxe.xml");
	actor->name = "StonePickaxe" + to_string(index);

	icon = UI::Create("StonePickaxeIcon");
	icon->LoadFile("Icon_StonePickaxe.xml");
	icon->name = "StonePickaxeIcon" + to_string(index++);
	tooltipBoxScaleY = 0.8f;

	ItemProto::Init();

	//=========================
	enumName = Item::StonePickaxe;
	type = ItemType::Weapon;
	wType = WeaponType::Axe;
	state = ItemState::OnGround;
	//=========================
	stringName = "StonePickaxe";

	damage = 10;
	maxDurability = 100;
	curDurability = maxDurability;
	weight = 2;
}

StonePickaxe::~StonePickaxe()
{

}

void StonePickaxe::Init()
{

}

void StonePickaxe::Release()
{
}

void StonePickaxe::Update()
{
	ImGui::Begin("ItemHierarchy");
	{
		actor->RenderHierarchy();
		icon->RenderHierarchy();
	}
	ImGui::End();


	ItemProto::Update();
}

void StonePickaxe::LateUpdate()
{
	//ItemProto::LateUpdate();
}

void StonePickaxe::Render()
{
	ItemProto::Render();
}

void StonePickaxe::RenderHierarchy()
{

}

wstring StonePickaxe::GetExplain()
{
	 
	wstring exp = L"암석을 부술 수 있는 곡괭이. \n돌로 만들어져 쉽게 망가진다.\n";
	wstring exp_sub1 = L"\n한손무기";
	wstring exp_sub2 = L"\n무게: 2.0";
	wstring exp_sub3 = L"\n내구도: " + to_wstring(curDurability) + L"/" + to_wstring(maxDurability);
	wstring exp_sub4 = L"\n공격력: " + to_wstring(damage);

	return exp + exp_sub1 + exp_sub2 + exp_sub3 + exp_sub4;
}

bool StonePickaxe::IsDestroyed()
{
	return false;
}

void StonePickaxe::DestructionEvent()
{
}

void StonePickaxe::Use()
{
	if (state == ItemState::OnInventory)
	{
		state = ItemState::Equipped;
		PLAYER->EquipToHand(this);
	}
	else if (state == ItemState::Equipped)
	{
		state = ItemState::OnInventory;
		PLAYER->ReleaseToHand();
	}
}

void StonePickaxe::Fix()
{
	curDurability = maxDurability;
}

