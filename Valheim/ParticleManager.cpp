#include "stdafx.h"

ParticleManager::ParticleManager()
{
	//너도밤나무 파괴될시에 나뭇잎부분에서 떨어지는 파티클 효과
	beechDrop = Pop::Create("beechDrop");
	beechDrop->LoadFile("BeechLeafDrop.xml");
	//너도밤나무 타격 이펙트 파티클효과
	hitBeech = Pop::Create("hitBeech");
	hitBeech->LoadFile("hitBeech.xml");

	woodHitDust = Rain::Create("woodHitDust");

	//플레이어 피격시 출혈 파티클 효과
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

//Vector3 ParticleManager::SetParticlePos(Particle* effect, Vector3 startPos)
//{
//	effect->SetWorldPos(startPos);
//}
