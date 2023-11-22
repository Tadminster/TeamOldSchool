#include "stdafx.h"
#include "Prototype.h"

#include "StoneAxe.h"
#include "Stone.h"
#include "Woodpile.h"
#include "ItemProto.h"

ItemProto* ItemProto::Create(Item name)
{
	switch (name)
	{
	case Item::StoneAxe:
		return new StoneAxe();
	case Item::Woodpile:
		return new Woodpile();
	case Item::Stone:
		return new Stone();
	default:
		throw std::invalid_argument("error");
	}
}

void ItemProto::Init()
{
	text_interaction.left	= App.GetHalfWidth() * 1.05f;
	text_interaction.top	= App.GetHalfHeight();
	text_interaction.right	= text_interaction.left + 1000;
	text_interaction.bottom = text_interaction.top + 1000;
	groundRay.direction = Vector3(0.0f, -1.0f, 0.0f);
}

void ItemProto::Update()
{
	if (state == ItemState::OnGround)
	{
		// forwardForce 가 0 이상이면
		if (forwardForce > 0.0f)
		{
			// 이동방향에 Forward 방향을 더함
			actor->MoveWorldPos(forwardDir * veclocity * DELTA);

			// forwardForce 감소
			forwardForce -= 10.0f * DELTA;
		}
		
		// 땅과 충돌하는 지점을 계산
		groundRay.position = actor->GetWorldPos();
		if (Utility::RayIntersectMap(groundRay, MAP, rayCollisionPoint))
		{
			// 충돌지점보다 높이 있으면
			if (actor->GetWorldPos().y > rayCollisionPoint.y + 0.5f)
			{
				// 이동
				actor->MoveWorldPos(actor->GetUp() * gravity * DELTA);

				// gravity 감소
				gravity -= 20.0f * DELTA;
			}
			// 충돌지점보다 낮게 있으면
			else
			{
				// 이동하지 않게 초기화
				gravity = 0.0f;
				forwardForce = 0.0f;
			}
		}

		actor->Update();
	}
}

void ItemProto::LateUpdate()
{

}

void ItemProto::Render()
{
	if (state == ItemState::OnGround)
	{
		actor->Render();

		if (isInteraction)
		{
			DWRITE->RenderText(
				Utility::ToWString(stringName) + L"\n[E] 줍기" ,
				text_interaction,
				20.0f,
				L"Arial",
				Color(1.0f, 1.0f, 1.0f, 0.0f),
				DWRITE_FONT_WEIGHT_MEDIUM,
				DWRITE_FONT_STYLE_NORMAL,
				DWRITE_FONT_STRETCH_EXPANDED);
		}
	}
	else if (state == ItemState::OnInventory)
	{
		//icon->Render();
	}
	else if (state == ItemState::Equipped)
	{
		if (DEBUGMODE) actor->Render();
	}
}

void ItemProto::Drop()
{
	actor->scale	= Vector3(1, 1, 1);
	actor->rotation = Vector3(0, PLAYER->GetActor()->rotation.y, 0);
	actor->SetWorldPos(PLAYER->GetActor()->GetWorldPos() + Vector3(0.0f, 1.0f, 0.0f));
	forwardDir		= PLAYER->GetActor()->GetForward();

	forwardForce	= 5.0f;
	gravity			= 5.0f;

	state			= ItemState::OnGround;
}

//bool ItemProto::IsDestroyed()
//{
//	return false;
//}
//====================================================================================================
void MaterialProto::StackMerge(MaterialProto* material)
{
	// 현재 아이템 스택과 대상 아이템 스택의 합이 최대 스택보다 작으면
	if (this->currentStack + material->currentStack < maxStack)
	{
		// 대상 아이템에 현재 아이템스택을 더함
		material->currentStack += this->currentStack;

		// 현재 아이템스택은 0개로 초기화
		this->currentStack = 0;
	}
	// 스택의 합이 최대 스택 이상이면
	else
	{
		// 더하고 남은 스택을 계산
		int remainStack = (this->currentStack + material->currentStack) - maxStack;
		
		// 현재 아이템은 남은 스택으로 초기화
		this->currentStack = remainStack;

		// 대상 아이템은 최대 스택으로 초기화
		material->currentStack = maxStack;
	}
}

void MaterialProto::DestructionEvent()
{
	cout << "stack: " << currentStack << endl;
	cout << "stack 수가 0이하이므로 아이템 파괴" << endl;
	MaterialProto::~MaterialProto();
}

bool MaterialProto::IsDestroyed()
{
	if (currentStack <= 0)
	{
		return true;
	}
	return false;
}
