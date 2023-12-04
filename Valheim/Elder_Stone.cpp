#include "stdafx.h"
#include "Unit.h"
#include "Elder_Stone.h"

Elder_Stone::Elder_Stone()
{
	actor = Actor::Create();
	actor->LoadFile("Unit/Monster_Elder_BossStone.xml");
	actor->name = "BossStone";

	ment = UI::Create();
	ment->LoadFile("Unit/BossStone1.xml");
	ment->name = "BossStone_Ment";
	ment->visible = false;

	ment2 = UI::Create();
	ment2->LoadFile("Unit/EndingMent.xml");
	ment2->name = "BossStone_Ment2";
	ment2->visible = false;
}

Elder_Stone::~Elder_Stone()
{
}

void Elder_Stone::Init()
{
}

void Elder_Stone::Update()
{
	//ShowCursor(true);
	actor->RenderHierarchy();
	ment->RenderHierarchy();
	ment2->RenderHierarchy();

	if ((PLAYER->GetActor()->GetWorldPos()-actor->GetWorldPos()).Length()<10.0f)
	{
		// 카메라 위치 -> 마우스로 레이를 생성
		Ray GetItem = Utility::MouseToRay(Camera::main);
		Vector3 hit = {};
		
		if (ELDER->GetIsDeath() && PLAYER->isElderTrophy)
		{
			if (Utility::RayIntersectTri(GetItem, actor->Find("Model"), hit))
			{
				ment->visible = true;
				// E키를 누르면
				if (INPUT->KeyDown('E'))
				{
					goEnding = true;
				}
			}
			else ment->visible = false;
		}
	}

	if (goEnding)
	{
		endingTime += DELTA;
		ment->visible = false;
		ment2->visible = true;
		if (endingTime > 7.0f)
		{
			PLAYER->isEnding = true;
			Camera::main->SetLocalPos
			(Vector3(RANDOM->Float(-0.3f, 0.3f), RANDOM->Float(-0.3f, 0.3f), RANDOM->Float(-0.3f, 0.3f)));
		}
		else if (endingTime > 3.0f)
		{
			Camera::main->SetLocalPos
			(Vector3(RANDOM->Float(-0.3f, 0.3f), RANDOM->Float(-0.3f, 0.3f), RANDOM->Float(-0.3f, 0.3f)));
		}
	}
	float lightRatio = max(0.2f, LIGHT->GetTimeRatio());
	Color color(lightRatio, lightRatio, lightRatio, 1.0f);
	{
		actor->Find("Model")->material->ambient = color;
		actor->Find("Model")->material->diffuse = color;
	}

	SetOnTerrain();

	actor->Update();
	ment->Update();
	ment2->Update();
}

void Elder_Stone::LateUpdate()
{
	if (PLAYER->GetCollider()->Intersect(actor->collider)) PLAYER->MoveBack(actor);
}

void Elder_Stone::Render()
{
	actor->Render();
	ment->Render();
	ment2->Render();
}
