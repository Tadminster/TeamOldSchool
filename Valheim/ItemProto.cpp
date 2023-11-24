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
		// forwardForce �� 0 �̻��̸�
		if (forwardForce > 0.0f)
		{
			// �̵����⿡ Forward ������ ����
			actor->MoveWorldPos(forwardDir * veclocity * DELTA);

			// forwardForce ����
			forwardForce -= 10.0f * DELTA;
		}
		
		// ���� �浹�ϴ� ������ ���
		groundRay.position = actor->GetWorldPos();
		if (Utility::RayIntersectMap(groundRay, MAP, rayCollisionPoint))
		{
			// �浹�������� ���� ������
			if (actor->GetWorldPos().y > rayCollisionPoint.y + 0.5f)
			{
				// �̵�
				actor->MoveWorldPos(actor->GetUp() * gravity * DELTA);

				// gravity ����
				gravity -= 20.0f * DELTA;
			}
			// �浹�������� ���� ������
			else
			{
				// �̵����� �ʰ� �ʱ�ȭ
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
				Utility::ToWString(stringName) + L"\n[E] �ݱ�" ,
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
	// ���� ������ ���ð� ��� ������ ������ ���� �ִ� ���ú��� ������
	if (this->currentStack + material->currentStack < maxStack)
	{
		// ��� �����ۿ� ���� �����۽����� ����
		material->currentStack += this->currentStack;

		// ���� �����۽����� 0���� �ʱ�ȭ
		this->currentStack = 0;
	}
	// ������ ���� �ִ� ���� �̻��̸�
	else
	{
		// ���ϰ� ���� ������ ���
		int remainStack = (this->currentStack + material->currentStack) - maxStack;
		
		// ���� �������� ���� �������� �ʱ�ȭ
		this->currentStack = remainStack;

		// ��� �������� �ִ� �������� �ʱ�ȭ
		material->currentStack = maxStack;
	}
}

void MaterialProto::DestructionEvent()
{
	cout << "stack: " << currentStack << endl;
	cout << "stack ���� 0�����̹Ƿ� ������ �ı�" << endl;
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
