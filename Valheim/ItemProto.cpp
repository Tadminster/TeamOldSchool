#include "stdafx.h"
//#include "Prototype.h"

#include "StoneAxe.h"
#include "ItemProto.h"

ItemProto* ItemProto::Create(ItemName name)
{
	switch (name)
	{
	case ItemName::StoneAxe:
		return new StoneAxe();
	default:
		throw std::invalid_argument("error");
	}
}

void ItemProto::Init()
{
	groundRay.direction = Vector3(0.0f, -1.0f, 0.0f);
}

void ItemProto::Update()
{
	if (state == ItemState::OnGround)
	{
		// forwardForce 가 0 이상이면
		if (forwardForce > 0.0f)
		{
			// 이동방향에 Forward 방향을 더함
			actor->MoveWorldPos(forwardDir * veclocity * DELTA);

			// forwardForce 감소
			forwardForce -= 10.0f * DELTA;
		}
		
		// 땅과 충돌하는 지점을 계산
		groundRay.position = actor->GetWorldPos();
		if (Utility::RayIntersectMap(groundRay, MAP, rayCollisionPoint))
		{
			// 충돌지점보다 높이 있으면
			if (actor->GetWorldPos().y > rayCollisionPoint.y + 0.5f)
			{
				// 이동
				actor->MoveWorldPos(actor->GetUp() * gravity * DELTA);

				// gravity 감소
				gravity -= 20.0f * DELTA;
			}
			// 충돌지점보다 낮게 있으면
			else
			{
				// 이동하지 않게 초기화
				gravity = 0.0f;
				forwardForce = 0.0f;
			}
		}

		actor->Update();
	}
}

void ItemProto::LateUpdate()
{

}

void ItemProto::Drop()
{
	actor->scale	= Vector3(1, 1, 1);
	actor->rotation = Vector3(0, PLAYER->GetActor()->rotation.y, 0);
	actor->SetWorldPos(PLAYER->GetActor()->GetWorldPos() + Vector3(0.0f, 1.0f, 0.0f));
	forwardDir		= PLAYER->GetActor()->GetForward();

	forwardForce	= 5.0f;
	gravity			= 5.0f;

	state			= ItemState::OnGround;
}
