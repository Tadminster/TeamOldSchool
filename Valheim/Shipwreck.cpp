#include "stdafx.h"
#include "FeatureProto.h"
#include "Shipwreck.h"

Shipwreck::Shipwreck()
{
	actor = Actor::Create();
	actor->LoadFile("Feature_Shipwreck.xml");
	actor->name = "Shipwreck";

	rotation = &actor->Find("RootNode")->rotation;
	//==================================================
	type = FeatureArmorType::Tree;
	hitPoint = 100;
}

Shipwreck::~Shipwreck()
{
}

void Shipwreck::Init()
{
	// ���ļ� ��ġ ����
	actor->SetWorldPos(OBJ->GetStartingPosition());
	actor->Update();
}

void Shipwreck::Update()
{
	//������Ʈ�� ī�޶��� �Ÿ� ���
	playerDistance = Vector3::DistanceSquared(PLAYER->GetActor()->GetWorldPos(), actor->GetWorldPos());

	// �Ÿ��� 2000.0f �̻��̸� ����(������Ʈ ���� ����)
	if (playerDistance > MAXMUM_UPDATE_DISTANCE) return;

	LodUpdate(playerDistance);

	FeatureProto::Update();
}

void Shipwreck::LateUpdate()
{
}

void Shipwreck::Render()
{
	actor->Render();
}

void Shipwreck::Release()
{
	delete this;
}

void Shipwreck::RenderHierarchy()
{
	actor->RenderHierarchy();
}

void Shipwreck::UpdateLight()
{
	float lightRatio = max(0.1f, LIGHT->GetTimeRatio());
	Color color(lightRatio, lightRatio, lightRatio, 1.0f);

	actor->Find("FrontHull")->material->diffuse = color;
	actor->Find("RearHull")->material->diffuse = color;
	actor->Find("FrontHull")->material->ambient = color;
	actor->Find("RearHull")->material->ambient = color;
}

bool Shipwreck::ReceivedDamageEvent(float damage, WeaponType wType)
{
	FeatureProto::ReceivedDamageEvent(damage, wType);

	// ���� Ÿ�� ����Ʈ
	PARTICLE->PlayParticleEffect(EffectType::HITWOOD, PLAYER->GetCollisionPoint());

	// ���� Ÿ�� ����
	SoundName randomPlay = static_cast<SoundName>(RANDOM->Int(WOOD_BREAK_01, WOOD_BREAK_04));
	SOUND->Play(randomPlay);

	return true;
}

void Shipwreck::DestructionEvent()
{
	// ���� ������ ����
	for (int i = 0; i < RANDOM->Int(8, 10); i++)
	{
		ItemProto* item = ItemProto::Create(Item::Woodpile);
		Vector3 randomPos = Vector3(RANDOM->Float(-1.0f, 1.0f), RANDOM->Float(1.0f, 3.0f), RANDOM->Float(-1.0f, 1.0f));
		item->GetActor()->SetWorldPos(actor->GetWorldPos() + randomPos);
		OBJ->AddItem(item);
	}

	// ������Ʈ ����
	Release();
}
