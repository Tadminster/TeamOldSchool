#include "stdafx.h"
#include "PlayerState.h"
#include "ItemProto.h"


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

	
	

	slidingVector.direction = actor->GetForward();
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
	if (equippedHand)
	{
		return equippedHand->GetActor()->collider->Intersect(object);
	}
	else return false;
}

bool Player::CleanFrame()
{
	//�浹 ������ 31 58 89
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
	ptMouse.x = App.GetHalfWidth();
	ptMouse.y = App.GetHalfHeight();
	Rot.x = (INPUT->position.y - ptMouse.y) * 0.001f;
	Rot.y = (INPUT->position.x - ptMouse.x) * 0.001f;
	actor->rotation.y += Rot.y;
	Camera::main->rotation.x += Rot.x;
	ClientToScreen(App.GetHandle(), &ptMouse);
	SetCursorPos(ptMouse.x, ptMouse.y);

	//�������� �ø��� ķ �����̼� �޾ƿ���
	actor->Find("FrustumCam")->rotation.x = actor->Find("PlayerCam")->rotation.x;
	actor->Find("FrustumCam")->rotation.y = actor->rotation.y;
	
	//ī�޶�-�ͷ��� �浹 ����
	playerCamRay.position = actor->Find("PlayerCam")->GetWorldPos();
	playerCamRay.direction = (actor->GetWorldPos()+Vector3(0,2.0f,0)) - actor->Find("PlayerCam")->GetWorldPos();
	playerCamRay.direction.Normalize();
	
	playerReverseCamRay.position = actor->Find("PlayerOriginCam")->GetWorldPos();
	playerReverseCamRay.direction = -(actor->Find("PlayerOriginCam")->GetForward()+ actor->Find("PlayerOriginCam")->GetUp()*2.0f);
	playerReverseCamRay.direction.Normalize();

	//��ǻƮ��ŷ ���� ������ 40���� ������ O_O
	//������ ���� �� ���� + ī�޶� ȸ���� ���� �ϸ� ���������� ������ �ȵǴ� ���� ����
	if (Utility::RayIntersectMap(playerCamRay, MAP, playerCamHit))
	{
		actor->Find("PlayerCam")->SetWorldPos(playerCamHit + (-actor->Find("RootNode")->GetForward() + actor->Find("RootNode")->GetUp()));
	}
	else
	{
		if (Utility::RayIntersectMap(playerReverseCamRay, MAP, playerReverseCamRayHit))
		{
			if ((actor->Find("PlayerOriginCam")->GetWorldPos() - playerReverseCamRayHit).Length() >= 0.1f)
			{
				actor->Find("PlayerCam")->SetWorldPos(actor->Find("PlayerOriginCam")->GetWorldPos());
			}
		}
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
}

void Player::PlayerMove()
{
	//���°��� ���� �̵��ӵ�(FSM�Ϸ��� �ٵ��� ����)
	if (state == WalkState::GetInstance()) moveSpeed = WALKSPEED;
	else if (state == RunState::GetInstance()) moveSpeed = RUNSPEED;
	else if (state == IdleState::GetInstance()) moveSpeed = 0;
	else if (state == SwingState::GetInstance()) moveSpeed = 0;

	//Ÿ �ݶ��̴��� �浹������ ��, �̵������� �����̵� ���ͷ� �ޱ� ���� ���ǹ�
	if (!istouch)
	{
		if (INPUT->KeyPress('W')) moveDir = actor->GetForward();
		else if (INPUT->KeyPress('S')) moveDir = -actor->GetForward();
		if (INPUT->KeyPress('A')) moveDir = -actor->GetRight();
		else if (INPUT->KeyPress('D')) moveDir = actor->GetRight();
		moveDir.Normalize();
		actor->MoveWorldPos(moveDir * moveSpeed * DELTA);
	}
}

void Player::EquipToHand(Prototype* item)
{
	if (!equippedHand)
	{
		//������ �ϼ��ܰ迡�� ������, ���� �����ϱ�
		equippedHand = item;
		actor->Find("mixamorig:RightHandIndex1")->AddChild(item->GetActor());
		actor->Find(item->GetActor()->name)->scale = Vector3(50, 50, 50);
		actor->Find(item->GetActor()->name)->SetLocalPos(Vector3(-0.1f, 0, -0.05f));
		actor->Find(item->GetActor()->name)->rotation = Vector3(0, 90.0f, 0) * ToRadian;
	}
}

void Player::ReleaseToHand()
{
	if (equippedHand)
	{
		if (INPUT->KeyDown('1'))
		{
			actor->Find("mixamorig:RightHandIndex1")->children.clear();
			INVEN->AddItem((ItemProto*)equippedHand);
			equippedHand = nullptr;
		}
		
	}
}

void Player::MoveBack(Actor* col)
{
	Vector3 slidingDir =  col->GetWorldPos() - actor->GetWorldPos();
	slidingDir.y = 0;
	slidingDir.Normalize();
	Vector3 normal = col->collider->GetNormalVector(slidingDir);

	moveDir = slidingDir - normal * (slidingDir.Dot(normal));
	moveDir.Normalize();
	moveDir = -moveDir;

	actor->MoveWorldPos(moveDir * moveSpeed * DELTA);
}

bool Player::GetItem(ItemProto* item)
{	
	//�浹�� Ʈ���� ��, ������ �������� ui����
	Ray GetItem = Utility::MouseToRay((Camera*)(actor->Find("PlayerCam")));
	Vector3 hit = {};
		if (Utility::RayIntersectTri(GetItem, item->GetActor()->Find("Mesh"), hit))
		{
			if (INPUT->KeyDown('E'))
			{
				INVEN->AddItem(item);
				return true;
			}
		}
	return false;
}

bool Player::IsDestroyed()
{
	return false;
}

void Player::DestructionEvent()
{
}
