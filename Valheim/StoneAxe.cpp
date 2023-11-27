#include "stdafx.h"
#include "ItemProto.h"
#include "StoneAxe.h"

StoneAxe::StoneAxe()
{
	static int index = 0;
	actor = Actor::Create("StoneAxe");
	actor->LoadFile("Item_StoneAxe.xml");
	actor->name = "Item_StoneAxe" + to_string(index);

	icon = UI::Create("StoneAxeIcon");
	icon->LoadFile("Icon_StoneAxe.xml");
	icon->name = "StoneAxeIcon" + to_string(index++);
	tooltipBoxScaleY = 0.8f;

	ItemProto::Init();

	//=========================
	enumName	= Item::StoneAxe;
	type		= ItemType::Weapon;
	wType		= WeaponType::Axe;
	state		= ItemState::OnGround;
	//=========================
	stringName		= "StoneAxe";
	
	damage			= 10;
	maxDurability	= 100;
	curDurability	= maxDurability;
	weight			= 2;
}

StoneAxe::~StoneAxe()
{

}

void StoneAxe::Init()
{
	
}

void StoneAxe::Release()
{
}

void StoneAxe::Update()
{
	ImGui::Begin("ItemHierarchy");
	{
		actor->RenderHierarchy();
		icon->RenderHierarchy();
	}
	ImGui::End();

	
	ItemProto::Update();
}

void StoneAxe::LateUpdate()
{
	//ItemProto::LateUpdate();
}

void StoneAxe::Render()
{
	ItemProto::Render();
}

void StoneAxe::RenderHierarchy()
{

}

wstring StoneAxe::GetExplain()
{
	wstring exp = L"나무를 베는데 사용하는 조잡한 \n도끼입니다.\n";
	wstring exp_sub1 = L"\n한손무기";
	wstring exp_sub2 = L"\n무게: 2.0";
	wstring exp_sub3 = L"\n내구도: " + to_wstring(curDurability) + L"/" + to_wstring(maxDurability);
	wstring exp_sub4 = L"\n공격력: " + to_wstring(damage);

	return exp + exp_sub1 + exp_sub2 + exp_sub3 + exp_sub4;
}

bool StoneAxe::IsDestroyed()
{
	return false;
}

void StoneAxe::DestructionEvent()
{
}

void StoneAxe::Use()
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

void StoneAxe::Fix()
{
	curDurability = maxDurability;
}

