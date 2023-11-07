#include "stdafx.h"
#include "TreeBeech.h"

TreeBeech::TreeBeech()
{
	actor = Actor::Create();
	actor->LoadFile("Beech.xml");
	static int index = 0;
	actor->name = "Beech" + index++;
}

TreeBeech::~TreeBeech()
{
}

void TreeBeech::Init()
{
}

void TreeBeech::Update()
{
	actor->Update();
}

void TreeBeech::LateUpdate()
{
}

void TreeBeech::Render()
{
	actor->Render();
}

void TreeBeech::RenderHierarchy()
{
	actor->RenderHierarchy();
}
