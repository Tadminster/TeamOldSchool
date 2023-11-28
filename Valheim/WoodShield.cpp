#include "stdafx.h"
#include "ItemProto.h"
#include "WoodShield.h"

WoodShield::WoodShield()
{
	static int index = 0;
	actor = Actor::Create("WoodShield");
	actor->LoadFile("Item_WoodShield.xml");
	actor->name = "Item_WoodShield" + to_string(index);

	icon = UI::Create("WoodShieldIcon");
	icon->LoadFile("Icon_WoodShield.xml");
	icon->name = "WoodShieldIcon" + to_string(index++);
	tooltipBoxScaleY = 0.8f;

	ItemProto::Init();

	//=========================
	enumName = Item::WoodShield;
	type = ItemType::Weapon;
	wType = WeaponType::Blunt;
	state = ItemState::OnGround;
	//=========================
	stringName = "WoodShield";

	damage = 10;
	maxDurability = 100;
	curDurability = maxDurability;
	weight = 2;
}

WoodShield::~WoodShield()
{

}

void WoodShield::Init()
{

}

void WoodShield::Release()
{
}

void WoodShield::Update()
{
	ImGui::Begin("ItemHierarchy");
	{
		actor->RenderHierarchy();
		icon->RenderHierarchy();
	}
	ImGui::End();


	ItemProto::Update();
}

void WoodShield::LateUpdate()
{
	//ItemProto::LateUpdate();
}

void WoodShield::Render()
{
	ItemProto::Render();
}

void WoodShield::RenderHierarchy()
{

}

wstring WoodShield::GetExplain()
{
	wstring exp = L"조잡하지만 유용한 무기입니다.\n";
	wstring exp_sub1 = L"\n한손무기";
	wstring exp_sub2 = L"\n무게: 2.0";
	wstring exp_sub3 = L"\n내구도: " + to_wstring(curDurability) + L"/" + to_wstring(maxDurability);
	wstring exp_sub4 = L"\n공격력: " + to_wstring(damage);

	return exp + exp_sub1 + exp_sub2 + exp_sub3 + exp_sub4;
}

bool WoodShield::IsDestroyed()
{
	return false;
}

void WoodShield::DestructionEvent()
{
}

void WoodShield::Use()
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

void WoodShield::Fix()
{
	curDurability = maxDurability;
}

