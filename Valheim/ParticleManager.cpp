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

	//현재 레벨업 빛무리 이펙트에 알파값조절 투명도조절 시험중
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
	else if (type == EffectType::HEALEFFECT)
	{
		healEffect->SetWorldPos(pos);
		healEffect->Play();
		cout << "캐릭터 회복 이펙트" << endl;
	}
	else if (type == EffectType::HEALEFFECT2)
	{
		healEffect2->SetWorldPos(pos);
		healEffect2->Play();
		cout << "캐릭터 회복 이펙트2" << endl;
	}
	else if (type == EffectType::WATERSPLASH)
	{
		waterSplash->SetWorldPos(pos);
		waterSplash->Play();
		cout << "파도 철썩임" << endl;
	}
	else if (type == EffectType::WATERWAVE)
	{
		waterWave->SetWorldPos(pos);
		waterWave->Play();
		cout << "파도 철썩임" << endl;
	}
}

void ParticleManager::SetWorldPos()
{
	levelUp->SetWorldPos(PLAYER->GetActor()->GetWorldPos());
	healEffect2->SetWorldPos(PLAYER->GetActor()->GetWorldPos());
}


