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

void Unit::RotationForMove(Vector3 targetPos)
{
	ImGui::Text("targetPos x %f", targetPos.x);
	ImGui::Text("targetPos y %f", targetPos.y);
	ImGui::Text("targetPos z %f", targetPos.z);

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
	if (moveTime > 0)
	{
		actor->MoveWorldPos(moveDir * moveSpeed * DELTA);
		moveTime -= DELTA;
	}
}

void Unit::Astar()
{
	AstarRay.position = PLAYER->GetPlayer()->GetWorldPos() + Vector3(0, 100, 0);
	AstarRay.direction = Vector3(0, -1, 0);
	Vector3 target;
	if (Utility::RayIntersectMap(AstarRay, MAP, target))
	//if(MAP->ComputePicking(AstarRay,target))
	{
		astar->PathFinding(actor->GetWorldPos(), target, way);
		
		
	}
	if (!way.empty())
	{
		//RotationForMove(way.back());
		for (auto& it : way)
		{
			ImGui::Text("way x %f", it.x);
			ImGui::Text("way y %f", it.y);
			ImGui::Text("way z %f", it.z);
		}
		ImGui::Text("way size %d", way.size());
		ImGui::Text("rotation %f", actor->rotation.y);
		way.pop_back();
	}
}
