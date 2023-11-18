#include "stdafx.h"
#include "ElderState.h"
#include "Elder.h"

Elder::Elder()
{
	actor = Actor::Create();
	actor->LoadFile("Monster_Elder.xml");
	actor->LoadFile("Monster_Elder_BossStone.xml");
	actor->name = "Monster_Elder";

	state = Elder_OpeningState::GetInstance();
}

Elder::~Elder()
{
}

void Elder::Init()
{
	actor->SetWorldPos(PLAYER->GetPlayer()->GetWorldPos()+Vector3(10,0,0));
}

void Elder::Update()
{
	//�߷� ����
	ApplyGravity();
	actor->Update();
}

void Elder::LateUpdate()
{
	//Elder - Terrain �浹
	SetonTerrain();

	//���� ��ȯ �ӽ�
	if (INPUT->KeyDown('9')) actor->LoadFile("Monster_Elder.xml");
	else if (INPUT->KeyDown('0')) actor->LoadFile("Monster_Elder_BossStone.xml");
	
	if (INPUT->KeyDown(VK_F3)) state->Idle(this);
	else if (INPUT->KeyDown(VK_F4)) state->Walk(this);

	//�����̵� ���� �ʱ���
	if (PLAYER->GetPlayer()->collider->Intersect(actor->collider))
	{
		PLAYER->istouch = true;
		PLAYER->MoveBack(actor);
	}
	else
	{
		PLAYER->istouch = false;
	}
}

void Elder::Render()
{
	actor->Render();
	
}

void Elder::Release()
{
}

void Elder::RenderHierarchy()
{
	actor->RenderHierarchy();
}

bool Elder::IsDestroyed()
{
	return false;
}

void Elder::DestructionEvent()
{
}

void Elder::SetState(ElderState* state)
{
	this->state = state;
}
