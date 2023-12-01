#include "stdafx.h"

ParticleManager::ParticleManager()
{
	//나무 파괴될 때에 나뭇잎 떨어지는 파티클 효과
	beechDrop = Pop::Create("Particle_WoodLeafDrop");
	beechDrop->LoadFile("Particle_WoodLeafDrop.xml");
	
	
	//나무 타격 이펙트 파티클효과
	hitBeech = Pop::Create("Particle_HitWood");
	hitBeech->LoadFile("Particle_HitWood.xml");
	

	woodHitDust = Pop::Create("Particle_WoodHitDust");
	woodHitDust->LoadFile("Particle_WoodHitDust.xml");

	//플레이어 피격시 출혈 파티클 효과	
	hitBlood = Pop::Create("Particle_Blood");
	hitBlood->LoadFile("Particle_Blood.xml");
	

	//바위 타격시 돌이 튀는 파티클 효과
	hitRock = Pop::Create("Particle_RockHit");
	hitRock->LoadFile("Particle_HitRock.xml");
	
	//플레이어 레벨업 파티클 효과
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

	//현재 레벨업 빛무리 이펙트에 알파값조절 투명도조절 시험중
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
		cout << "나뭇잎 떨어짐" << endl;
	}
	else if (type == EffectType::HITWOOD)
	{
		hitBeech->SetWorldPos(pos);
		hitBeech->Play();
		cout << "나무 타격" << endl;
	}
	else if (type == EffectType::WOODHITDUST)
	{
		woodHitDust->SetWorldPos(pos);
		woodHitDust->Play();
		cout << "나무 타격 먼지발생" << endl;
	}
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
	else if (type == EffectType::LEVELUP)
	{
		levelUp->SetWorldPos(pos);
		levelUp->Play();
		cout << "레벨업 빛무리효과" << endl;
	}
	else if (type == EffectType::LEVELUPONHEAD)
	{
		levelUpOnHead->SetWorldPos(pos);
		levelUpOnHead->Play();
		cout << "레벨업 캐릭터 머리위 이펙트" << endl;
	}
}


