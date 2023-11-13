#include "stdafx.h"
#include "Item.h"
#include "BattleItem.h"
#include "StoneAxe.h"

StoneAxe::StoneAxe(Vector3 spwanpos)
{
	actor = Actor::Create("StoneAxe");
	actor->LoadFile("StoneAxe.xml");
	actor->name = "StoneAxe";
	actor->SetWorldPos(spwanpos);

	itemName = "StoneAxe";
	itemDurability = 100;
	itemWeight = 2;

	itemDamage = 10;
	woodAdditionalDamage = 5;
}

StoneAxe::~StoneAxe()
{

}

void StoneAxe::Init()
{
	
}

void StoneAxe::Update()
{
	actor->Update();
}

void StoneAxe::LateUpdate()
{
	
}

void StoneAxe::Render()
{
	actor->Render();
}

void StoneAxe::RenderHierarchy()
{
	ImGui::Begin("Hierarchy");
	{
		actor->RenderHierarchy();
	}
	ImGui::End();
}

bool StoneAxe::IsDestroyed()
{
	return false;
}

void StoneAxe::DestructionEvent()
{
}

void StoneAxe::Release()
{
}
