#include "stdafx.h"

ParticleManager::ParticleManager()
{
	//나무 파괴될 때에 나뭇잎 떨어지는 파티클 효과
	beechDrop = Pop::Create("Particle_WoodLeafDrop");
	beechDrop->LoadFile("Particle_WoodLeafDrop.xml");
	
	
	//나무 타격 이펙트 파티클효과
	hitBeech = Pop::Create("Particle_HitWood");
	hitBeech->LoadFile("Particle_HitWood.xml");
	

	woodHitDust = Rain::Create("Particle_WoodHitDust");
	woodHitDust->LoadFile("Particle_WoodHitDust.xml");

	//플레이어 피격시 출혈 파티클 효과
	hitBlood = Pop::Create("Particle_Blood");
	hitBlood->LoadFile("Particle_Blood.xml");
	

	//바위 타격시 돌이 튀는 파티클 효과
	hitRock = Pop::Create("Particle_RockHit");
	hitRock->LoadFile("Particle_HitRock.xml");
	
	
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
}

void ParticleManager::LateUpdate()
{
	
}

void ParticleManager::Render()
{
	beechDrop->Render();
	hitBeech->Render();
	//woodHitDust->Render();
	hitBlood->Render();
	hitRock->Render();
}

void ParticleManager::RenderHierarchy()
{
	
	ImGui::Begin("Hierarchy");
	{
		beechDrop->RenderHierarchy();
		hitBeech->RenderHierarchy();
		//woodHitDust->RenderHierarchy();
		hitBlood->RenderHierarchy();
		hitRock->RenderHierarchy();
	}
	ImGui::End();
}


void ParticleManager::PlayParticleEffect(EffectType type, Vector3 pos)
{
	if (type == EffectType::BEECHDROP)
	{
		beechDrop->SetWorldPos(pos);
		beechDrop->Play();
		cout << "나뭇잎 떨어짐" << endl;
	}
	else if (type == EffectType::HITBEECH)
	{
		hitBeech->SetWorldPos(pos);
		hitBeech->Play();
		cout << "나무 타격" << endl;
	}
	//else if (type == EffectType::WOODHITDUST)
	//{
	//	woodHitDust->SetWorldPos(pos);
	//	woodHitDust->Play();
	//	cout << "나무 타격 먼지발생" << endl;
	//}
	else if (type == EffectType::HITBLOOD)
	{
		hitBlood->SetWorldPos(pos);
		hitBlood->Play();
		cout << "피 터짐" << endl;
	}
	else if (type == EffectType::HITROCK)
	{
		hitRock->SetWorldPos(pos);
		hitRock->Play();
		cout << "바위 타격" << endl;
	}
}


