#include "stdafx.h"
//#include "Prototype.h"
#include "FeatureProto.h"
#include "BeechInstancing.h"

BeechInstancing::BeechInstancing()
{
	actor = Actor::Create();

	actor->LoadFile("Feature_BeechInstance.xml");
	actor->name = "Beech_Instance";

	//==================================================
	type = FeatureArmorType::Tree;
	hitPoint = 80;
}

BeechInstancing::~BeechInstancing()
{
}

void BeechInstancing::Init()
{
}

void BeechInstancing::Update()
{


	actor->Update();
}

void BeechInstancing::LateUpdate()
{
	groundRay.position = actor->GetWorldPos();

	//if (MAP->ComputePicking(groundRay, rayCollisionPoint))
	//{
	//	if (actor->GetWorldPos().y > rayCollisionPoint.y)
	//	{
	//		actor->MoveWorldPos(actor->GetUp() * gravity * DELTA);
	//	}
	//}
}

void BeechInstancing::Render()
{
	actor->Render();
}

void BeechInstancing::Release()
{
	BeechInstancing::~BeechInstancing();
}

void BeechInstancing::RenderHierarchy()
{
	actor->RenderHierarchy();
}

void BeechInstancing::DestructionEvent()
{

	// 오브젝트 삭제 (나무)
	delete this;
}
