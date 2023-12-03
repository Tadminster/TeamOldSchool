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

	//엘더 발찍기
	elderStomp = Pop::Create("ElderStomp");
	elderStomp->LoadFile("Unit/Particle_ElderStomp.xml");
	elderStomp->name = "elderStomp";

	//엘더 점프공격
	elderJumpAttack = Pop::Create("ElderJumpAttack");
	elderJumpAttack->LoadFile("Particle_ElderJumpAttack.xml");
	elderJumpAttack->name = "elderJumpAttack";
	
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
	waterSplash->waveRange = 0.45f;

	waterWave = Pop::Create("Particle_WaterWave");
	waterWave->LoadFile("Particle_WaterWave.xml");
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
	healEffect->Update();
	healEffect2->Update();
	waterSplash->Update();
	waterWave->Update();
	elderStomp->Update();
	elderJumpAttack->Update();

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
	elderStomp->Render();
	elderJumpAttack->Render();
}

void ParticleManager::RenderHierarchy()
{
	
	ImGui::Begin("Hierarchy");
	{
		/*beechDrop->RenderHierarchy();
		hitBeech->RenderHierarchy();
		woodHitDust->RenderHierarchy();
		hitBlood->RenderHierarchy();
		hitRock->RenderHierarchy();
		levelUp->RenderHierarchy();
		levelUpOnHead->RenderHierarchy();
		healEffect->RenderHierarchy();
		healEffect2->RenderHierarchy();
		waterSplash->RenderHierarchy();
		waterWave->RenderHierarchy();*/
		elderStomp->RenderHierarchy();
		elderJumpAttack->RenderHierarchy();
	}
	ImGui::End();

}


void ParticleManager::PlayParticleEffect(EffectType type, Vector3 pos)
{
	if (type == EffectType::WOODDROP)
	{
		beechDrop->SetWorldPos(pos);
		beechDrop->Play();
	}
	else if (type == EffectType::HITWOOD)
	{
		hitBeech->SetWorldPos(pos);
		hitBeech->Play();
	}
	else if (type == EffectType::WOODHITDUST)
	{
		woodHitDust->SetWorldPos(pos);
		woodHitDust->Play();
	}
	else if (type == EffectType::HITBLOOD)
	{
		hitBlood->SetWorldPos(pos);
		hitBlood->Play();
	}
	else if (type == EffectType::HITROCK)
	{
		hitRock->SetWorldPos(pos);
		hitRock->Play();
	}
	else if (type == EffectType::ELDERSTOMP)
	{
		elderStomp->SetWorldPos(pos);
		elderStomp->Play();
	}
	else if (type == EffectType::ELDERATTACK)
	{
		elderJumpAttack->SetWorldPos(pos);
		elderJumpAttack->Play();
	}
	else if (type == EffectType::LEVELUP)
	{
		levelUp->SetWorldPos(pos);
		levelUp->Play();
	}
	else if (type == EffectType::LEVELUPONHEAD)
	{
		levelUpOnHead->SetWorldPos(pos);
		levelUpOnHead->Play();
	}
	else if (type == EffectType::HEALEFFECT)
	{
		healEffect->SetWorldPos(pos);
		healEffect->Play();
	}
	else if (type == EffectType::HEALEFFECT2)
	{
		healEffect2->SetWorldPos(pos);
		healEffect2->Play();
	}
	else if (type == EffectType::WATERSPLASH)
	{
		waterSplash->SetWorldPos(pos);
		waterSplash->Play();
	}
	else if (type == EffectType::WATERWAVE)
	{
		waterWave->SetWorldPos(pos);
		waterWave->Play();
	}
}

void ParticleManager::SetWorldPos()
{
	levelUp->SetWorldPos(PLAYER->GetActor()->GetWorldPos());
	healEffect2->SetWorldPos(PLAYER->GetActor()->GetWorldPos());
}


