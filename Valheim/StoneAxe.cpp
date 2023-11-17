#include "stdafx.h"
#include "ItemProto.h"
#include "StoneAxe.h"

StoneAxe::StoneAxe()
{
	static int index = 0;
	actor = Actor::Create("StoneAxe");
	actor->LoadFile("StoneAxe.xml");
	actor->name = "StoneAxe" + index++;
	actor->SetWorldPos(Vector3(0, 50, 0));

	icon = UI::Create("StoneAxeIcon");
	icon->LoadFile("Icon_StoneAxe.xml");

	ItemProto::Init();

	//=========================
	type = ItemType::Weapon;
	state = ItemState::OnGround;
	//=========================
	name		= "StoneAxe";
	
	damage		= 10;
	durability	= 100;
	weight		= 2;
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
	if (state == ItemState::OnGround )
	{
		//actor->Update();
	}
	else if (state == ItemState::OnInventory)
	{
		//icon->Update();
	}
	else if (state == ItemState::Equipped)
	{
		//actor->Update();
	}

}

void StoneAxe::LateUpdate()
{
	//ItemProto::LateUpdate();
}

void StoneAxe::Render()
{
	if (state == ItemState::OnGround)
	{
		actor->Render();
	}
	else if (state == ItemState::OnInventory)
	{
		//icon->Render();
	}
	else if (state == ItemState::Equipped)
	{
		if (DEBUGMODE) actor->Render();
	}
}

void StoneAxe::RenderHierarchy()
{

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
	durability = 100;
}

