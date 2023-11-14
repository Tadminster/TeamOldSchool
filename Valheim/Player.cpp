#include "stdafx.h"
#include "PlayerState.h"
#include "Item.h"

Player::Player()
{
	actor = Actor::Create();
	actor->LoadFile("Player_Male.xml");
	actor->name = "Player";
	actor->anim->aniScale = 0.65f;
	
	state = IdleState::GetInstance();
}

Player::~Player()
{
}

void Player::Init()
{
	actor->SetWorldPos(Vector3(0,20,0));
	Camera::main = static_cast<Camera*>(actor->Find("PlayerCam"));
}

void Player::Update()
{
	lastPos = actor->GetWorldPos();
	if (!DEBUGMODE) 
	{
		PlayerControl();
		PlayerMove();
	}
	else isPlayerCam = false;
	//�߷� ����
		actor->MoveWorldPos(-actor->GetUp() * gravity * DELTA);
		if (isLand) gravity = 0;
		else gravity += GRAVITYPOWER * DELTA;

	actor->Update();
}

void Player::LateUpdate()
{
	//Player - Terrain �浹����
    Ray playerTop;
	playerTop.position = actor->GetWorldPos() + Vector3(0, 1000, 0);
    playerTop.direction = Vector3(0, -1, 0);
    Vector3 hit;
    if (Utility::RayIntersectMap(playerTop, MAP, hit))
    {
		if (actor->GetWorldPos().y - hit.y < 0.1f) {
			actor->SetWorldPosY(hit.y);
			isLand = true;
		}
		else isLand = false;
    }

	//ImGui::Text("%f actor y", actor->GetWorldPos().y);
	//ImGui::Text("%f hit y", hit.y);
	
    actor->Update();

	//��� �浹(�ڿ������� �պ���)
	Vector3 dir = actor->GetWorldPos() - lastPos;
	Vector3 dir2 = dir;
	dir2.y = 0;
	dir.Normalize();
	dir2.Normalize();
	float dot = dir.Dot(dir2);
	if (state==WalkState::GetInstance())
	{
		if (dot < 0.7 and (actor->GetWorldPos().y > lastPos.y))
		{
			actor->SetWorldPos(lastPos);
			actor->Update();
		}
	}
}

void Player::Render()
{
	actor->Render();
}

void Player::Release()
{
}

void Player::RenderHierarchy()
{
	actor->RenderHierarchy();
}

bool Player::CleanHit(Collider* object)
{
	if (actor->Find("StoneAxe"))
	{
		return actor->Find("StoneAxe")->collider->Intersect(object);
	}
	else return false;
}

bool Player::CleanFrame()
{
	if (state == SwingState::GetInstance() && actor->anim->currentAnimator.currentFrame == 31)
	{
		actor->anim->currentAnimator.currentFrame++;
		return true;
	}
	else if (state == SwingState::GetInstance() && actor->anim->currentAnimator.currentFrame == 58)
	{
		actor->anim->currentAnimator.currentFrame++;
		return true;
	}
	else if (state == SwingState::GetInstance() && actor->anim->currentAnimator.currentFrame == 89)
	{
		actor->anim->currentAnimator.currentFrame++;
		return true;
	}
	else return false;
	//�浹 ������ 31 58 89
}

void Player::SetState(PlayerState* state)
{
	this->state = state;
}

void Player::AvtivatePlayerCam()
{
	//���콺��ǥ ȭ�� �߾� ���� & �÷��̾ ī�޶� ȸ���� �ޱ�1
	if (!DEBUGMODE && !isPlayerCam) 
	{
		Camera::main = static_cast<Camera*>(actor->Find("PlayerCam"));
		isPlayerCam = true;
	}
	//ī�޶� ��ȯ �� ȭ�� ©���� �κ� ����
	{
		Camera::main->viewport.x = 0.0f;
		Camera::main->viewport.y = 0.0f;
		Camera::main->viewport.width = App.GetWidth();
		Camera::main->viewport.height = App.GetHeight();

		Camera::main->width = App.GetWidth();
		Camera::main->height = App.GetHeight();
	}
	//���콺��ǥ ȭ�� �߾� ���� & �÷��̾ ī�޶� ȸ���� �ޱ�2
	POINT ptMouse;
	ptMouse.x = App.GetHalfWidth();
	ptMouse.y = App.GetHalfHeight();
	Vector3 Rot;
	Rot.x = (INPUT->position.y - ptMouse.y) * 0.001f;
	Rot.y = (INPUT->position.x - ptMouse.x) * 0.001f;
	actor->rotation.y += Rot.y;
	Camera::main->rotation.x += Rot.x;
	ClientToScreen(App.GetHandle(), &ptMouse);
	SetCursorPos(ptMouse.x, ptMouse.y);
	//�������� �ø��� ķ �����̼� �޾ƿ���
	actor->Find("FrustumCam")->rotation.x = actor->Find("PlayerCam")->rotation.x;
	actor->Find("FrustumCam")->rotation.y = actor->rotation.y;
	
	//ī�޶�-�ͷ��� ���� �浹
	Ray PlayerCamRay;
	PlayerCamRay.position = actor->Find("PlayerCam")->GetWorldPos();
	Vector3 CamtoPlayer = actor->GetWorldPos() - actor->Find("PlayerCam")->GetWorldPos();
	CamtoPlayer.Normalize();
	PlayerCamRay.direction = CamtoPlayer;
	Vector3 hit;
	Vector3 CamLastPos;
	if (Utility::RayIntersectMap(PlayerCamRay, MAP, hit))
	{
		ImGui::Text("%f camray x ", hit.x);
		ImGui::Text("%f camray y", hit.y);
		ImGui::Text("%f camray z ", hit.z);
		CamLastPos = actor->Find("PlayerCam")->GetWorldPos();
		actor->Find("PlayerCam")->SetWorldPos(hit+(-actor->Find("RootNode")->GetForward() + actor->Find("RootNode")->GetUp()));
		CamtoTerrain = true;
	}
	else
	{
		/*if(CamtoTerrain)
		{
			actor->Find("PlayerCam")->SetWorldPos(actor->Find("FrustumCam")->GetWorldPos());
			CamtoTerrain = false;
		}*/
	}
}

void Player::PlayerControl()
{
	//Idle�� ����--------------------------------------------------------------------------------------------
	if (state == WalkState::GetInstance() || state == RunState::GetInstance()) 
	{
		if (INPUT->KeyUp('W') || INPUT->KeyUp('A') || INPUT->KeyUp('S') || INPUT->KeyUp('D'))
		{
			state->Idle();
		}
	}
	else if (state == JumpState::GetInstance())
	{
		if (isLand) 
		{
			isJump = false;
			state->Idle();
		}
	}
	else if (state == SwingState::GetInstance())
	{
		if (INPUT->KeyUp(VK_LBUTTON))
		{
			state->Idle();
		}
	}
	//Walk & Run--------------------------------------------------------------------------------------------
	if (INPUT->KeyPress('W') || INPUT->KeyPress('A') || INPUT->KeyPress('S') || INPUT->KeyPress('D'))
	{
		if (INPUT->KeyPress(VK_SHIFT))
		{
			state->Run();
		}
		else 
		{
			state->Walk();
		}
	}
	//Jump--------------------------------------------------------------------------------------------
	if (INPUT->KeyDown(VK_SPACE) && !isJump) 
	{
		state = JumpState::GetInstance();
		state->Jump();
	}
	//Swing--------------------------------------------------------------------------------------------
	if (INPUT->KeyPress(VK_LBUTTON)) 
	{
		state->Swing();
	}

	//if (state == SwingState::GetInstance()) ImGui::Text("%d state", 1);
	//else if (state == WalkState::GetInstance()) ImGui::Text("%d state", 2);
	//else if (state == RunState::GetInstance()) ImGui::Text("%d state", 3);
}

void Player::PlayerMove()
{
	if (state == WalkState::GetInstance()) moveSpeed = WALKSPEED;
	else if (state == RunState::GetInstance()) moveSpeed = RUNSPEED;
	else if (state == SwingState::GetInstance()) moveSpeed = 0;

	if (INPUT->KeyPress('W')) 
	{
		actor->MoveWorldPos(actor->GetForward() * moveSpeed * DELTA);
	}
	else if (INPUT->KeyPress('S'))
	{
		actor->MoveWorldPos(-actor->GetForward() * moveSpeed * DELTA);
	}
	if (INPUT->KeyPress('A'))
	{
		actor->MoveWorldPos(-actor->GetRight() * moveSpeed * DELTA);
	}
	else if (INPUT->KeyPress('D'))
	{
		actor->MoveWorldPos(actor->GetRight() * moveSpeed * DELTA);
	}
}
//���߿� �κ��丮 Ŭ������ �Ű����� �ٲٱ�
void Player::EquipToHand(Prototype* item)
{
	actor->Find("mixamorig:RightHandIndex1")->AddChild(item->GetActor());
	actor->Find(item->GetActor()->name)->scale = Vector3(1, 1, 1);

	isEquip = true;
}

void Player::ReleaseToHand()
{
	//
}

bool Player::IsDestroyed()
{
	return false;
}

void Player::DestructionEvent()
{
}

void Player::TreeAttack(Prototype* tree)
{
	if (isEquip == 1)
	{
		if (state == SwingState::GetInstance())
		{
			if (PLAYER->GetPlayer()->anim->currentAnimator.currentFrame == 31)
			{
				
			}

		}
	}
	
}
