#include "stdafx.h"
//#include "Prototype.h"
#include "FeatureProto.h"
#include "Rock.h"

Rock::Rock()
{
	actor = Actor::Create();
	if (RANDOM->Int(0, 1)) actor->LoadFile("Feature_Rock1.xml");
	else actor->LoadFile("Feature_Rock2.xml");
	static int index = 0;
	actor->name = "Rock" + to_string(index++);

	float x = RANDOM->Float(1.0f, 3.0f);
	float y = RANDOM->Float(2.0f, 3.0f);
	float z = RANDOM->Float(1.0f, 3.0f);
	actor->scale = Vector3(x, y, z);
	actor->collider->rotation = actor->rotation;

	rotation = &actor->Find("RootNode")->rotation;

	//==================================================
	type = FeatureArmorType::Rock;
	hitPoint = 80;
}

Rock::~Rock()
{
}

void Rock::Init()
{
}

void Rock::Update()
{
	// ������Ʈ�� ī�޶��� �Ÿ� ���
	playerDistance = Vector3::DistanceSquared(PLAYER->GetActor()->GetWorldPos(), actor->GetWorldPos());

	// �Ÿ��� 3000.0f �̻��̸� ����(������Ʈ ���� ����)
	if (playerDistance > MAXMUM_UPDATE_DISTANCE) return;

	FeatureProto::Update();
}

void Rock::LateUpdate()
{
	groundRay.position = actor->GetWorldPos();

	if (MAP->ComputePicking(groundRay, rayCollisionPoint))
	{
		if (actor->GetWorldPos().y > rayCollisionPoint.y)
		{
			actor->MoveWorldPos(actor->GetUp() * gravity * DELTA);
		}
	}
}

void Rock::Render()
{
	actor->Render();
}

void Rock::Release()
{
	Rock::~Rock();
}

void Rock::RenderHierarchy()
{
	actor->RenderHierarchy();
}

void Rock::DestructionEvent()
{
	// �� ������ ����
	for (int i = 0; i < RANDOM->Int(2, 3); i++)
	{
		ItemProto* item = ItemProto::Create(Item::Stone);
		Vector3 randomPos = Vector3(RANDOM->Float(-1.0f, 1.0f), RANDOM->Float(1.0f, 2.0f), RANDOM->Float(-1.0f, 1.0f));
		item->GetActor()->SetWorldPos(actor->GetWorldPos() + randomPos);
		OBJ->AddItem(item);
	}

	// �� �ı� ����Ʈ ���
	Vector3 effectPos = this->actor->GetWorldPos() + this->actor->GetUp() * 2.0f;
	PARTICLE->PlayParticleEffect(EffectType::BEECHDROP, effectPos);

	// ������Ʈ ���� (����)
	delete this;
}
