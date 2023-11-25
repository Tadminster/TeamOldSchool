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
	 
	wstring exp = L"�ϼ��� �μ� �� �ִ� ���. \n���� ������� ���� ��������.\n";
	wstring exp_sub1 = L"\n�Ѽչ���";
	wstring exp_sub2 = L"\n����: 2.0";
	wstring exp_sub3 = L"\n������: " + to_wstring(curDurability) + L"/" + to_wstring(maxDurability);
	wstring exp_sub4 = L"\n���ݷ�: " + to_wstring(damage);

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

