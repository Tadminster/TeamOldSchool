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
		// forwardForce �� 0 �̻��̸�
		if (forwardForce > 0.0f)
		{
			// �̵����⿡ Forward ������ ����
			actor->MoveWorldPos(forwardDir * veclocity * DELTA);

			// forwardForce ����
			forwardForce -= 10.0f * DELTA;
		}
		
		// ���� �浹�ϴ� ������ ���
		groundRay.position = actor->GetWorldPos();
		if (Utility::RayIntersectMap(groundRay, MAP, rayCollisionPoint))
		{
			// �浹�������� ���� ������
			if (actor->GetWorldPos().y > rayCollisionPoint.y + 0.5f)
			{
				// �̵�
				actor->MoveWorldPos(actor->GetUp() * gravity * DELTA);

				// gravity ����
				gravity -= 20.0f * DELTA;
			}
			// �浹�������� ���� ������
			else
			{
				// �̵����� �ʰ� �ʱ�ȭ
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
