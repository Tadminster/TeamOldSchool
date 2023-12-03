#include "stdafx.h"
#include "FeatureProto.h"
#include "Birch.h"


Birch::Birch()
{
	actor = Actor::Create();
	actor->LoadFile("Feature_Birch.xml");

	static int index = 0;
	actor->name = "Birch" + to_string(index++);

	float x = RANDOM->Float(0.8f, 1.0f);
	float y = RANDOM->Float(1.0f, 1.2f);
	float z = RANDOM->Float(0.8f, 1.0f);
	actor->scale = Vector3(x, y, z);
	actor->rotation.y = RANDOM->Float(0.0f, 360.0f) * ToRadian;

	rotation = &actor->Find("RootNode")->rotation;

	//==================================================
	type = FeatureArmorType::Tree;
	hitPoint = 80;
}

Birch::~Birch()
{
}

void Birch::Init()
{
}

void Birch::Update()
{
	// ������Ʈ�� ī�޶��� �Ÿ� ���
	playerDistance = Vector3::DistanceSquared(PLAYER->GetActor()->GetWorldPos(), actor->GetWorldPos());

	// �Ÿ��� 2000.0f �̻��̸� ����(������Ʈ ���� ����)
	if (playerDistance > MAXMUM_UPDATE_DISTANCE) return;
	// 2000.0f �̸��̸� Lod ����
	else LodUpdate(playerDistance);

	FeatureProto::Update();
}

void Birch::LateUpdate()
{
}

void Birch::Render()
{
	actor->Render();
}

void Birch::RenderHierarchy()
{
	actor->RenderHierarchy();
}

void Birch::LodUpdate(float distance)
{
	actor->Find("Lod0")->visible = false;
	actor->Find("Lod1")->visible = false;

	if (distance < 1000)
	{
		lod = BirchLod::LOD0;
		actor->Find("Lod0")->visible = true;
	}
	else if (distance < 2000)
	{
		lod = BirchLod::LOD1;
		 actor->Find("Lod1")->visible = true;
	}
	else return;
}

void Birch::UpdateLight()
{
	float lightRatio = clamp(LIGHT->GetTimeRatio(), 0.0f, 1.0f);
	Color color(lightRatio, lightRatio, lightRatio, 1.0f);

	if (lod == BirchLod::LOD0)
	{
		actor->Find("Lod0")->material->diffuse = color;
		actor->Find("Lod0.001MeshObject1")->material->diffuse = color;
		actor->Find("Lod0")->material->ambient = color;
		actor->Find("Lod0.001MeshObject1")->material->ambient = color;
	}
	else if (lod == BirchLod::LOD1)
	{
		actor->Find("Lod1")->material->diffuse = color;
		actor->Find("Lod1.001MeshObject1")->material->diffuse = color;
		actor->Find("Lod1")->material->ambient = color;
		actor->Find("Lod1.001MeshObject1")->material->ambient = color;
	}
}


void Birch::Release()
{
	delete this;
}

bool Birch::ReceivedDamageEvent(float damage, WeaponType wType)
{
	// ������ ���
	if (wType == WeaponType::Axe)
	{
		if (type == FeatureArmorType::Tree) damage *= 2.0f;
	}
	else if (wType == WeaponType::Pickaxe)
	{
		if (type == FeatureArmorType::Rock) damage *= 2.0f;
	}

	// Birch�� 20������ ����
	damage = max(0.0f, damage - 20.0f);

	// ������ ����
	hitPoint = max(0.0f, hitPoint - damage);

	UIM->AddDamageText((int)damage, PLAYER->GetCollisionPoint());

	// Ÿ�� �ִϸ��̼�(��鸲) ����ð� ����
	hitAnimDuration = 0.3f;

	// ���� Ÿ�� ����Ʈ
	PARTICLE->PlayParticleEffect(EffectType::HITWOOD, PLAYER->GetCollisionPoint());

	// ���� Ÿ�� ����
	SoundName randomPlay = static_cast<SoundName>(RANDOM->Int(TREE_HIT_01, TREE_HIT_07));
	SOUND->Play(randomPlay);
	
	return true;
}

void Birch::DestructionEvent()
{
	// ������ ����(������ ����)
	for (int i = 0; i < RANDOM->Int(2, 3); i++)
	{
		ItemProto* item = ItemProto::Create(Item::FineWood);
		Vector3 randomPos = Vector3(RANDOM->Float(-1.0f, 1.0f), RANDOM->Float(1.0f, 3.0f), RANDOM->Float(-1.0f, 1.0f));
		item->GetActor()->SetWorldPos(actor->GetWorldPos() + randomPos);
		OBJ->AddItem(item);
	}

	// ���� �ı� ����Ʈ
	Vector3 effectPos = this->actor->GetWorldPos() + this->actor->GetUp() * 8.0f;
	PARTICLE->PlayParticleEffect(EffectType::WOODDROP, effectPos);

	// ���� �ı� ����
	SoundName randomPlay = static_cast<SoundName>(RANDOM->Int(TREE_FALL_01, TREE_FALL_05));
	SOUND->Play(randomPlay);

	//�÷��̾ �ı��� ���� ī��Ʈ++
	PLAYER->SetTreeCount();

	// ������Ʈ ���� (����)
	delete this;
}
