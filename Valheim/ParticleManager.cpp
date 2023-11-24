#include "stdafx.h"

ParticleManager::ParticleManager()
{
	//�ʵ��㳪�� �ı��ɽÿ� �����ٺκп��� �������� ��ƼŬ ȿ��
	beechDrop = Pop::Create("beechDrop");
	beechDrop->LoadFile("BeechLeafDrop.xml");
	
	//�ʵ��㳪�� Ÿ�� ����Ʈ ��ƼŬȿ��
	hitBeech = Pop::Create("hitBeech");
	hitBeech->LoadFile("hitBeech.xml");

	woodHitDust = Rain::Create("woodHitDust");

	//�÷��̾� �ǰݽ� ���� ��ƼŬ ȿ��
	hitBlood = Pop::Create("hitBlood");
	hitBlood->LoadFile("hitBlood.xml");
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
		cout << "��ƼŬ �۵���" << endl;
	}
	if (type == EffectType::HITBEECH)
	{
		hitBeech->SetWorldPos(pos);
		hitBeech->Play();
		cout << "��ƼŬ �۵���" << endl;
	}
	if (type == EffectType::WOODHITDUST)
	{
		woodHitDust->SetWorldPos(pos);
		woodHitDust->Play();
		cout << "��ƼŬ �۵���" << endl;
	}
	if (type == EffectType::HITBLOOD)
	{
		hitBlood->SetWorldPos(pos);
		hitBlood->Play();
		cout << "��ƼŬ �۵���" << endl;
	}
}


