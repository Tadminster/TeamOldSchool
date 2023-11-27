#include "stdafx.h"

ParticleManager::ParticleManager()
{
	//���� �ı��� ���� ������ �������� ��ƼŬ ȿ��
	beechDrop = Pop::Create("Particle_WoodLeafDrop");
	beechDrop->LoadFile("Particle_WoodLeafDrop.xml");
	
	//���� Ÿ�� ����Ʈ ��ƼŬȿ��
	hitBeech = Pop::Create("Particle_HitWood");
	hitBeech->LoadFile("Particle_HitWood.xml");
	hitBeech->scale = { 0.1f, 0.1f };

	woodHitDust = Rain::Create("Particle_WoodHitDust");

	//�÷��̾� �ǰݽ� ���� ��ƼŬ ȿ��
	hitBlood = Pop::Create("Particle_Blood");
	hitBlood->LoadFile("Particle_Blood.xml");
	hitBlood->scale = { 0.5f, 0.5f };
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
}

void ParticleManager::RenderHierarchy()
{
	
	ImGui::Begin("Hierarchy");
	{
		beechDrop->RenderHierarchy();
		hitBeech->RenderHierarchy();
		woodHitDust->RenderHierarchy();
		hitBlood->RenderHierarchy();
	}
	ImGui::End();
}


void ParticleManager::PlayParticleEffect(EffectType type, Vector3 pos)
{
	if (type == EffectType::BEECHDROP)
	{
		beechDrop->SetWorldPos(pos);
		beechDrop->Play();
		cout << "������ ������" << endl;
	}
	if (type == EffectType::HITBEECH)
	{
		hitBeech->SetWorldPos(pos);
		hitBeech->Play();
		cout << "���� Ÿ��" << endl;
	}
	if (type == EffectType::WOODHITDUST)
	{
		woodHitDust->SetWorldPos(pos);
		woodHitDust->Play();
		cout << "���� Ÿ�� �����߻�" << endl;
	}
	if (type == EffectType::HITBLOOD)
	{
		hitBlood->SetWorldPos(pos);
		hitBlood->Play();
		cout << "�� ����" << endl;
	}
}


