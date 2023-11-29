#include "stdafx.h"
#include "ItemProto.h"
#include "Club.h"

Club::Club()
{
	static int index = 0;
	actor = Actor::Create("Club");
	actor->LoadFile("Item_Club.xml");
	actor->name = "Item_Club" + to_string(index);

	icon = UI::Create("ClubIcon");
	icon->LoadFile("Icon_Club.xml");
	icon->name = "ClubIcon" + to_string(index++);
	tooltipBoxScaleY = 0.8f;

	ItemProto::Init();

	//=========================
	enumName = Item::Club;
	type = ItemType::Weapon;
	wType = WeaponType::Blunt;
	state = ItemState::OnGround;
	//=========================
	stringName = "Club";

	damage			= 10;
	maxDurability	= 100;
	curDurability	= maxDurability;
	weight			= 2;
}

Club::~Club()
{

}

void Club::Init()
{

}

void Club::Release()
{
}

void Club::Update()
{
	ImGui::Begin("ItemHierarchy");
	{
		actor->RenderHierarchy();
		icon->RenderHierarchy();
	}
	ImGui::End();


	ItemProto::Update();
}

void Club::LateUpdate()
{
	//ItemProto::LateUpdate();
}

void Club::Render()
{
	ItemProto::Render();
}

void Club::RenderHierarchy()
{

}

wstring Club::GetExplain()
{
	wstring exp = L"조잡하지만 유용한 무기입니다.\n";
	wstring exp_sub1 = L"\n한손무기";
	wstring exp_sub2 = L"\n무게: " + to_wstring(weight);
	wstring exp_sub3 = L"\n내구도: " + to_wstring(curDurability) + L"/" + to_wstring(maxDurability);
	wstring exp_sub4 = L"\n공격력: " + to_wstring(damage);

	return exp + exp_sub1 + exp_sub2 + exp_sub3 + exp_sub4;
}

bool Club::IsDestroyed()
{
	return false;
}

void Club::DestructionEvent()
{
}

void Club::Use()
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

void Club::Fix()
{
	curDurability = maxDurability;
}

