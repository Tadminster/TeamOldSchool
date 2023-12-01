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
	//levelUpOnHead->LoadFile("Particle_levelUpOnHead.xml");
	//levelUp->desc2.alpha = 1.0f;
}

ParticleManager::~ParticleManager()
{
}

void ParticleManager::Init()
{
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

	//���� ������ ������ ����Ʈ�� ���İ����� �������� ������
	/*BLEND->Set(true);
	levelUp->desc2.alpha += DELTA * 0.1f;
	if (levelUp->desc2.alpha >= 1.0f) levelUp->desc2.alpha = 0.0f;
	BLEND->Set(false);*/

	BLEND->Set(true);
	levelUpOnHead->Render();
	levelUpOnHead->desc2.alpha += DELTA * 0.1f;
	if (levelUpOnHead->desc2.alpha >= 1.0f) levelUpOnHead->desc2.alpha = 0.0f;
	levelUpOnHead->Render();
	BLEND->Set(false);
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
}


