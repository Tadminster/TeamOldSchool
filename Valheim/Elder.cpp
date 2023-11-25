#include "stdafx.h"
#include "ElderState.h"
#include "ElderPatern.h"
#include "Elder.h"

Elder::Elder()
{
	actor = Actor::Create();
	actor->LoadFile("Monster_Elder.xml");
	actor->name = "Monster_Elder";
	actor->anim->aniScale = 0.4f;

	patern = new ElderPatern(this);

	hitPoint = 5;
}

Elder::~Elder()
{
}

void Elder::Init()
{
	moveSpeed = 2.0f;
	state = Elder_OpeningState::GetInstance();
	actor->SetWorldPos(PLAYER->GetPlayer()->GetWorldPos()+Vector3(10,0,0));
}

void Elder::Update()
{
	//�׽�Ʈ��------------------------------------
	//if (INPUT->KeyDown('-')) actor->LoadFile("Monster_Elder.xml");
	//else if (INPUT->KeyDown('=')) actor->LoadFile("Monster_Elder_BossStone.xml");

	if (state == Elder_OpeningState::GetInstance())
	{
		ImGui::Text("opening");
	}
	else if (state == Elder_IdleState::GetInstance())
	{
		ImGui::Text("idle");
	}
	else if (state == Elder_WalkState::GetInstance())
	{
		ImGui::Text("walk");
	}
	else if (state == Elder_StompState::GetInstance())
	{
		ImGui::Text("stomp");
	}
	else if (state == Elder_JumpAttackState::GetInstance())
	{
		ImGui::Text("JumpAttack");
	}
	else if (state == Elder_SummonState::GetInstance())
	{
		ImGui::Text("summon");
	}
	//�ൿ����(astar ��� ���� -> Ʈ�� ����(������ astar������ �ð��� ������))
	//����� �� ��� ��� �����۵��� Ȯ��
	if (ImGui::Button("astar"))
	{
		if (astar != nullptr) delete astar;
		astar = new AStar();
		astar->CreateNode(MAP, MAP->rowSize*1.5f, OBJ->GetColliders());
	}

	BehaviorPatern();
	DoFSM();

	//�߷� ����
	ApplyGravity();
	actor->Update();
	patern->Update();

}

void Elder::LateUpdate()
{
	//Elder - Terrain �浹
	SetOnTerrain();

	//Elder_BossStone - Player �浹
	if (PLAYER->GetCollider()->Intersect(actor->collider))
	{
		PLAYER->istouch = true;
		PLAYER->MoveBack(actor);
	}
	else
	{
		PLAYER->istouch = false;
	}

	//Elder - Player �浹
	if (PLAYER->GetCollider()->Intersect(actor->Find("mixamorig:RightLeg")->collider)
		&& state == E_STOMP)
	{
		PLAYER->PlayerHit();
	}
	

	if (PLAYER->CleanHit(actor->collider) && PLAYER->CleanFrame())
	{
		cout << "elder hit!" << endl;
		cout << PLAYER->GetPlayer()->anim->currentAnimator.currentFrame << endl;
		
	}
	
}

void Elder::Render()
{
	actor->Render();
	patern->Render();
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
	if (hitPoint <= 0) return true;
	return false;
}

void Elder::DestructionEvent()
{
	//��� ���� �ֱ�
}

void Elder::SetState(ElderState* state)
{
	this->state = state;
}

void Elder::BehaviorPatern()
{
	ImGui::Text("paterntype %d",paternType%2);
	ImGui::Text("stompPatern %d",stompPatern);
	//���� �ѹ� �� 2.5�� ��
	if (paternTime >= 0 && state == E_IDLE)
	{
		paternTime -= DELTA;
		paternType = RANDOM->Int(0, 99);
	}
	//���� �ѹ� - ����� �ѹ� �ݺ�
	if (stompPatern )
	{
		patern->StompPatern(this);
	}
	else
	{
		switch (paternType % 2)
		{
		case 0:
			patern->JumpAttackPatern(this);
			break;
		case 1:
			patern->SummonPatern(this);
			break;
		}
	}
	

}

void Elder::DoFSM()
{
	if (state == E_OPENING)
	{
		state->Opening(this);
	}
	else if (state == E_IDLE)
	{
		state->Idle(this);
	}
	else if (state == E_WALK)
	{
		state->Walk(this);
	}
	else if (state == E_STOMP)
	{
		state->Stomp(this);
	}
	else if (state == E_JumpAttack)
	{
		state->JumpAttack(this);
	}
	else if (state == E_SUMMON)
	{
		state->Summon(this);
	}
}



