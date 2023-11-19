#include "stdafx.h"
#include "Unit.h"


Unit::Unit()
{
}

void Unit::SetOnTerrain()
{
	//유닛 - 터레인 충돌(지면 안착)
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
	//중력 구현
	actor->MoveWorldPos(-actor->GetUp() * gravity * DELTA);
	if (isLand) gravity = 0;
	else gravity += GRAVITYPOWER * DELTA;
}

void Unit::RotationForMove()
{
	moveDir = PLAYER->GetPlayer()->GetWorldPos() - actor->GetWorldPos();
	moveTime = moveDir.Length() / moveSpeed;
	moveDir.Normalize();

	srcRotation = atan2f(actor->GetForward().x, actor->GetForward().z);
	destRotation = atan2f(moveDir.x, moveDir.z);
	angleGap = destRotation - srcRotation;

	if (angleGap > PI) srcRotation += PI * 2.0f;
	else if (angleGap < -PI) srcRotation -= PI * 2.0f;
	angleGap = destRotation - srcRotation;
	rotationSpeed = angleGap > 0 ? PI : -PI;

	actor->rotation.y = srcRotation;
	rotationTime = fabs(angleGap) / fabs(rotationSpeed);

	if (rotationTime > 0)
	{
		actor->rotation.y += rotationSpeed * DELTA * rotationScale;
		rotationTime -= DELTA * rotationScale;
	}
}

void Unit::MonsterMove()
{
	if (moveTime > 0)
	{
		actor->MoveWorldPos(moveDir * moveSpeed * DELTA);
		moveTime -= DELTA;
	}
}

void Unit::Init()
{
}

void Unit::Update()
{
}

void Unit::LateUpdate()
{
}

void Unit::Render()
{
}

void Unit::Release()
{
}

void Unit::RenderHierarchy()
{
}

bool Unit::ReceivedDamageEvent(int damage)
{
	return false;
}

bool Unit::IsDestroyed()
{
	return false;
}

void Unit::DestructionEvent()
{
}
