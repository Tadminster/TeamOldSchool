#include "stdafx.h"
#include "Prototype.h"
#include "FeatureProto.h"
#include "BeechStump.h"

BeechStump::BeechStump()
{
	actor = Actor::Create();
	actor->LoadFile("BeechStump.xml");

	static int index = 0;
	actor->name = "BeechStump" + index++;

	hitPoint = 10;
}

BeechStump::~BeechStump()
{

}

void BeechStump::Init()
{

}

void BeechStump::Update()
{
	actor->Update();
}

void BeechStump::LateUpdate()
{

}

void BeechStump::Render()
{
	actor->Render();
}

void BeechStump::RenderHierarchy()
{
	actor->RenderHierarchy();
}

void BeechStump::DestructionEvent()
{

}

void BeechStump::ReceivedDamageEvent(int damage)
{
}
