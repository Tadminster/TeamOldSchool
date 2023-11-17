#include "stdafx.h"
#include "Unit.h"


Unit::Unit()
{
}

void Unit::SetonTerrain()
{
	//���� - �ͷ��� �浹(���� ����)
	UnitTopRay.position = actor->GetWorldPos() + Vector3(0, 1000, 0);
	UnitTopRay.direction = Vector3(0, -1, 0);
	if (Utility::RayIntersectMap(UnitTopRay, MAP, UnitHit))
	{
		if (actor->GetWorldPos().y - UnitHit.y < 0.1f) {
			actor->SetWorldPosY(UnitHit.y);
			isLand = true;
		}
		else isLand = false;
	}
	actor->Update();
}

void Unit::ApplyGravity()
{
	//�߷� ����
	actor->MoveWorldPos(-actor->GetUp() * gravity * DELTA);
	if (isLand) gravity = 0;
	else gravity += GRAVITYPOWER * DELTA;
}
