#include "stdafx.h"
//#include "Prototype.h"
#include "FeatureProto.h"
#include "Beech.h"

Beech::Beech()
{
	static int index = 0;

	actor = Actor::Create();
	actor->LoadFile("Feature_Beech.xml");
	actor->name = "Beech" + to_string(index++);

	float x = RANDOM->Float(0.8f, 1.2f);
	float y = RANDOM->Float(0.4f, 0.6f);
	float z = RANDOM->Float(0.8f, 1.2f);
	actor->rotation.y = RANDOM->Float(0.0f, 360.0f) * ToRadian;
	actor->scale = Vector3(x, y, z);

	rotation = &actor->Find("RootNode")->rotation;

	//==================================================
	type = FeatureArmorType::Tree;
	hitPoint = 80;
}

Beech::~Beech()
{
}

void Beech::Init()
{
}

void Beech::Update()
{
	//������Ʈ�� ī�޶��� �Ÿ� ���
	float distance = Vector3::DistanceSquared(Camera::main->GetWorldPos(), actor->GetWorldPos());
	
	// �Ÿ��� 3000.0f �̻��̸� ����(������Ʈ ���� ����)
	if (distance > MAXMUM_UPDATE_DISTANCE) return;
	else LodUpdate(distance);

	FeatureProto::Update();
}

void Beech::LateUpdate()
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

void Beech::LodUpdate(float distance)
{
	actor->Find("Lod0")->visible = false;
	actor->Find("Lod1")->visible = false;
	actor->Find("Lod3")->visible = false;

	if (distance < 1000) actor->Find("Lod0")->visible = true;			// �Ÿ� 1000 ���ϴ� LOD0
	else if (distance < 2000) actor->Find("Lod1")->visible = true;		// �Ÿ� 2000 ���ϴ� LOD1
	else if (distance < 3000) actor->Find("Lod3")->visible = true;		// �Ÿ� 5000 ���ϴ� LOD3
	else return;
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

	// ���� �ı� ����Ʈ ���
	PARTICLE->PlayParticleEffect(EffectType::BEECHDROP, spawnPos);
	
	// ������Ʈ ���� (����)
	delete this;
}
