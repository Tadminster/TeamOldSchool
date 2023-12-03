#include "stdafx.h"

ParticleManager::ParticleManager()
{
	//���� �ı��� ���� ������ �������� ��ƼŬ ȿ��
	beechDrop = Pop::Create("Particle_WoodLeafDrop");
	beechDrop->LoadFile("Particle_WoodLeafDrop.xml");
	
	//���� Ÿ�� ����Ʈ ��ƼŬȿ��
	hitBeech = Pop::Create("Particle_HitWood");
	hitBeech->LoadFile("Particle_HitWood.xml");
	

	woodHitDust = Pop::Create("Particle_WoodHitDust");
	woodHitDust->LoadFile("Particle_WoodHitDust.xml");

	//�÷��̾� �ǰݽ� ���� ��ƼŬ ȿ��	
	hitBlood = Pop::Create("Particle_Blood");
	hitBlood->LoadFile("Particle_Blood.xml");
	

	//���� Ÿ�ݽ� ���� Ƣ�� ��ƼŬ ȿ��
	hitRock = Pop::Create("Particle_RockHit");
	hitRock->LoadFile("Particle_HitRock.xml");
	
	//�÷��̾� ������ ��ƼŬ ȿ��
	levelUp = Pop::Create("Praticle_LevelUp");
	levelUp->LoadFile("Particle_LevelUp.xml");

	levelUpOnHead = Pop::Create("Particle_LevelUpOnHead");
	levelUpOnHead->LoadFile("Particle_levelUpOnHead.xml");
	
	healEffect = Pop::Create("Particle_HealEffect");
	healEffect->LoadFile("Particle_HealEffect.xml");

	healEffect2 = Rain::Create("Particle_HealEffect2");
	healEffect2->LoadFile("Particle_HealEffect2.xml");

	waterSplash = Pop::Create("Particle_WaterSplash");
	waterSplash->LoadFile("Particle_WaterSplash.xml");
	waterSplash->waveRange = 0.5f;

	waterWave = Pop::Create("Particle_WaterWave");
	waterWave->LoadFile("Particle_WaterWave.xml");
}

ParticleManager::~ParticleManager()
{
}

void ParticleManager::Init()
{
	//levelUpOnHead->SetWorldPos(PLAYER->GetActor()->GetWorldPos() + Vector3(0, 1, 0));
}

void ParticleManager::Release()
{
}

void ParticleManager::Update()
{
	beechDrop->Update();
	hitBeech->Update();
	woodHitDust->Update();
	hitBlood->Update();
	hitRock->Update();
	levelUp->Update();
	levelUpOnHead->Update();
	healEffect->Update();
	healEffect2->Update();
	waterSplash->Update();
	waterWave->Update();
}

void ParticleManager::LateUpdate()
{
	
}

void ParticleManager::Render()
{
	beechDrop->Render();
	hitBeech->Render();
	woodHitDust->Render();
	hitBlood->Render();
	hitRock->Render();
	levelUp->Render();
	healEffect->Render();
	healEffect2->Render();
	waterSplash->Render();
	waterWave->Render();

	//���� ������ ������ ����Ʈ�� ���İ����� �������� ������
	/*BLEND->Set(true);
	levelUp->desc2.alpha += DELTA * 0.1f;
	if (levelUp->desc2.alpha >= 1.0f) levelUp->desc2.alpha = 0.0f;
	BLEND->Set(false);*/

	BLEND->Set(true);
	levelUpOnHead->Render();
	levelUpOnHead->desc2.alpha += DELTA * 0.3f;
	if (levelUpOnHead->desc2.alpha >= 1.0f) levelUpOnHead->desc2.alpha = 0.0f;
	levelUpOnHead->Render();
	BLEND->Set(false);

	//waterWave->scale += Vector3(0.2f, 0.2f, 0.2f) * DELTA;
}

void ParticleManager::RenderHierarchy()
{
	
	ImGui::Begin("Hierarchy");
	{
		beechDrop->RenderHierarchy();
		hitBeech->RenderHierarchy();
		woodHitDust->RenderHierarchy();
		hitBlood->RenderHierarchy();
		hitRock->RenderHierarchy();
		levelUp->RenderHierarchy();
		levelUpOnHead->RenderHierarchy();
		healEffect->RenderHierarchy();
		healEffect2->RenderHierarchy();
		waterSplash->RenderHierarchy();
		waterWave->RenderHierarchy();
	}
	ImGui::End();

}


void ParticleManager::PlayParticleEffect(EffectType type, Vector3 pos)
{
	if (type == EffectType::WOODDROP)
	{
		beechDrop->SetWorldPos(pos);
		beechDrop->Play();
		cout << "������ ������" << endl;
	}
	else if (type == EffectType::HITWOOD)
	{
		hitBeech->SetWorldPos(pos);
		hitBeech->Play();
		cout << "���� Ÿ��" << endl;
	}
	else if (type == EffectType::WOODHITDUST)
	{
		woodHitDust->SetWorldPos(pos);
		woodHitDust->Play();
		cout << "���� Ÿ�� �����߻�" << endl;
	}
	else if (type == EffectType::HITBLOOD)
	{
		hitBlood->SetWorldPos(pos);
		hitBlood->Play();
		cout << "�� ����" << endl;
	}
	else if (type == EffectType::HITROCK)
	{
		hitRock->SetWorldPos(pos);
		hitRock->Play();
		cout << "���� Ÿ��" << endl;
	}
	else if (type == EffectType::LEVELUP)
	{
		levelUp->SetWorldPos(pos);
		levelUp->Play();
		cout << "������ ������ȿ��" << endl;
	}
	else if (type == EffectType::LEVELUPONHEAD)
	{
		levelUpOnHead->SetWorldPos(pos);
		levelUpOnHead->Play();
		cout << "������ ĳ���� �Ӹ��� ����Ʈ" << endl;
	}
	else if (type == EffectType::HEALEFFECT)
	{
		healEffect->SetWorldPos(pos);
		healEffect->Play();
		cout << "ĳ���� ȸ�� ����Ʈ" << endl;
	}
	else if (type == EffectType::HEALEFFECT2)
	{
		healEffect2->SetWorldPos(pos);
		healEffect2->Play();
		cout << "ĳ���� ȸ�� ����Ʈ2" << endl;
	}
	else if (type == EffectType::WATERSPLASH)
	{
		waterSplash->SetWorldPos(pos);
		waterSplash->Play();
		cout << "�ĵ� ö����" << endl;
	}
	else if (type == EffectType::WATERWAVE)
	{
		waterWave->SetWorldPos(pos);
		waterWave->Play();
		cout << "�ĵ� ö����" << endl;
	}
}

void ParticleManager::SetWorldPos()
{
	levelUp->SetWorldPos(PLAYER->GetActor()->GetWorldPos());
	healEffect2->SetWorldPos(PLAYER->GetActor()->GetWorldPos());
}


