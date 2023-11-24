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

//Vector3 ParticleManager::SetParticlePos(Particle* effect, Vector3 startPos)
//{
//	effect->SetWorldPos(startPos);
//}
