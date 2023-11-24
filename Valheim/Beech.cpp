#include "stdafx.h"
//#include "Prototype.h"
#include "FeatureProto.h"
#include "Beech.h"

Beech::Beech()
{
	actor = Actor::Create();
	actor->LoadFile("Beech.xml");

	static int index = 0;
	actor->name = "Beech" + index++;

	hitPoint = 10;
}

Beech::~Beech()
{
}

void Beech::Init()
{
}

void Beech::Update()
{
	FeatureProto::Update();
	actor->Update();
}

void Beech::LateUpdate()
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

void Beech::Render()
{
	actor->Render();
}

void Beech::Release()
{
	Beech::~Beech();
}

void Beech::RenderHierarchy()
{
	actor->RenderHierarchy();
}

void Beech::LodUpdate(LodLevel lv)
{
	actor->Find("Lod0")->visible = false;
	actor->Find("Lod1")->visible = false;
	actor->Find("Lod3")->visible = false;

	if (lv == LodLevel::LOD0)
		actor->Find("Lod0")->visible = true;
	else if (lv == LodLevel::LOD1)
		actor->Find("Lod1")->visible = true;
	else if (lv == LodLevel::LOD3)
		actor->Find("Lod3")->visible = true;
}

void Beech::DestructionEvent()
{
	// ������Ʈ ���� (�׷��ͱ�)
	FeatureProto* stump = FeatureProto::Create(FeatureType::BeechStump);
	stump->GetActor()->SetWorldPos(this->actor->GetWorldPos());

	// ������Ʈ ���� (�볪��)
	FeatureProto* log = FeatureProto::Create(FeatureType::BeechLog);
	Vector3 spawnPos = this->actor->GetWorldPos() + Vector3(0.0f, 5.0f, 0.0f);
	log->GetActor()->SetWorldPos(spawnPos);
	log->Init();
	//log->GetActor()->rotation = this->actor->rotation;
	//log->GetActor()->scale = this->actor->scale;

	// ����Ʈ�� ������Ʈ �߰�
	OBJ->AddObject(stump);
	OBJ->AddObject(log);

	//�ӽ÷� ������Ʈ �ı��� ��ƼŬȿ�� �߰��մϴ�------------
	// PlayParticleEffect �Լ��� ����Ʈ�� Ÿ�԰� Vector3 pos ����Ʈ ������ġ�� �����̿��ϴ� ��ġ�� �������ֽø� �˴ϴ�
	//���� ��ü Ÿ�� ����Ʈ �Դϴ�
	PARTICLE->PlayParticleEffect(EffectType::HITBEECH, this->actor->GetWorldPos());
	//���� �ı��� �������� �������� ����Ʈ�Դϴ�
	PARTICLE->PlayParticleEffect(EffectType::BEECHDROP, this->actor->GetWorldPos());
	//���� Ÿ�ݽ� �߻��ϴ� ���� ����Ʈ �Դϴ�
	PARTICLE->PlayParticleEffect(EffectType::WOODHITDUST, this->actor->GetWorldPos());
	//-------------------------------------------------
	// ������Ʈ ���� (����)
	Beech::~Beech();
}
