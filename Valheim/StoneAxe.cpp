#include "stdafx.h"
#include "ItemProto.h"
#include "StoneAxe.h"

StoneAxe::StoneAxe()
{
	static int index = 0;
	actor = Actor::Create("StoneAxe");
	actor->LoadFile("StoneAxe.xml");
	actor->name = "StoneAxe" + index++;

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

void StoneAxe::Use()
{
}

void StoneAxe::Fix()
{
}

