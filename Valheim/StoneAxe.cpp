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

	if (state == ItemState::OnGround || state == ItemState::Equipped)
	{
		actor->Update();
	}
	else if (state == ItemState::OnInventory)
	{
		//icon->Update();
	}

}

void StoneAxe::LateUpdate()
{
	if (state == ItemState::OnGround)
	{
		groundRay.position = actor->GetWorldPos();

		if (Utility::RayIntersectMap(groundRay, MAP, rayCollisionPoint))
		//if (MAP->ComputePicking(groundRay, rayCollisionPoint))
		{
			if (actor->GetWorldPos().y > rayCollisionPoint.y + 0.5f)
			{
				actor->MoveWorldPos(-actor->GetUp() * gravity * DELTA);
			}
		}
	}
}

void StoneAxe::Render()
{
	if (state == ItemState::OnGround || state == ItemState::Equipped)
	{
		actor->Render();
	}
	else if (state == ItemState::OnInventory)
	{
		//icon->Render();
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
}

void StoneAxe::Fix()
{
}

