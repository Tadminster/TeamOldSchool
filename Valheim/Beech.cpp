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

	float x = RANDOM->Float(1.0f, 1.2f);
	float y = RANDOM->Float(0.8f, 1.0f);
	float z = RANDOM->Float(1.0f, 1.2f);
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
	playerDistance = Vector3::DistanceSquared(PLAYER->GetActor()->GetWorldPos(), actor->GetWorldPos());
	
	// �Ÿ��� 2000.0f �̻��̸� ����(������Ʈ ���� ����)
	if (playerDistance > MAXMUM_UPDATE_DISTANCE) return;

	LodUpdate(playerDistance);

	FeatureProto::Update();
}

void Beech::LateUpdate()
{
	groundRay.position = actor->GetWorldPos();

}

void Beech::Render()
{
	actor->Render();
}

void Beech::Release()
{
	delete this;
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
	
	// �Ÿ� 500 ���ϴ� LOD0
	if (distance < 500)
	{
		lod = BeechLod::LOD0;
		actor->Find("Lod0")->visible = true;		
	}
	// �Ÿ� 1000 ���ϴ� LOD1
	else if (distance < 1000)
	{
		lod = BeechLod::LOD1;
		actor->Find("Lod1")->visible = true;		
	}
	// �Ÿ� 2000 ���ϴ� LOD3
	else if (distance < 2000)
	{
		lod = BeechLod::LOD3;
		actor->Find("Lod3")->visible = true;		
	}
	else return;
}

void Beech::UpdateLight()
{
	float lightRatio = max(0.1f, LIGHT->GetTimeRatio());
	Color color(lightRatio, lightRatio, lightRatio, 1.0f);

	if (lod == BeechLod::LOD0)
	{
		actor->Find("Lod0")->material->diffuse = color;
		actor->Find("Lod0MeshObject1")->material->diffuse = color;
		actor->Find("Lod0")->material->ambient = color;
		actor->Find("Lod0MeshObject1")->material->ambient = color;
	}
	else if (lod == BeechLod::LOD1)
	{
		actor->Find("Lod1")->material->diffuse = color;
		actor->Find("Lod1MeshObject1")->material->diffuse = color;
		actor->Find("Lod1")->material->ambient = color;
		actor->Find("Lod1MeshObject1")->material->ambient = color;
	}
	else if (lod == BeechLod::LOD3)
	{
		actor->Find("Lod3")->material->diffuse = color;
		actor->Find("Lod3MeshObject1")->material->diffuse = color;
		actor->Find("Lod3")->material->ambient = color;
		actor->Find("Lod3MeshObject1")->material->ambient = color;
	}
}

bool Beech::ReceivedDamageEvent(float damage, WeaponType wType)
{
	FeatureProto::ReceivedDamageEvent(damage, wType);

	// ���� Ÿ�� ����Ʈ
	PARTICLE->PlayParticleEffect(EffectType::HITWOOD, PLAYER->GetCollisionPoint());

	// ���� Ÿ�� ����
	SoundName randomPlay = static_cast<SoundName>(RANDOM->Int(TREE_HIT_01, TREE_HIT_07));
	SOUND->Play(randomPlay);

	return true;
}

void Beech::DestructionEvent()
{
	// ���� ������ ����
	for (int i = 0; i < RANDOM->Int(3, 5); i++)
	{
		ItemProto* item = ItemProto::Create(Item::Woodpile);
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
