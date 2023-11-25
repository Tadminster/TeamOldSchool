#include "stdafx.h"
#include "Unit.h"

Unit::Unit()
{
	
}

void Unit::SetOnTerrain()
{
	//유닛 - 터레인 충돌(지면 안착)
	groundRay.position = actor->GetWorldPos() + Vector3(0, 1000, 0);
	groundRay.direction = Vector3(0, -1, 0);
	if (Utility::RayIntersectMap(groundRay, MAP, groundHit))
	{
		if (actor->GetWorldPos().y - groundHit.y < 0.1f)
		{
			actor->SetWorldPosY(groundHit.y);
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
	//이동할 방향으로 회전 보간(플레이어 전용)
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

void Unit::RotationForMove(Vector3 targetPos)
{
	//이동할 방향으로 회전 보간(타겟 정해서 이동, 랜덤한 곳으로 이동해야 할 때 필요)
	moveDir = targetPos - actor->GetWorldPos();
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
	//이동속도*이동시간
	if (moveTime > 0)
	{
		actor->MoveWorldPos(moveDir * moveSpeed * DELTA);
		moveTime -= DELTA;
	}
}

void Unit::Astar()
{
	if (astar != nullptr)
	{
		if (TIMER->GetTick(astarTime, 0.5f))
		{
			astar->PathFinding(actor->GetWorldPos(), PLAYER->GetPlayer()->GetWorldPos(), way);
		}
		if (!way.empty())
		{
			if ((way.back() - actor->GetWorldPos()).Length() >= 1.0f)
			{
				RotationForMove(way.back());
				MonsterMove();
			}
			else
			{
				way.pop_back();
			}
		}
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
