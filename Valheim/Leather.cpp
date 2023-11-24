#include "stdafx.h"
#include "ItemProto.h"
#include "Leather.h"

Leather::Leather()
{
	static int index = 0;
	actor = Actor::Create("Leather");
	actor->LoadFile("Leather.xml");
	actor->name = "Leather" + index++;
	actor->SetWorldPos(Vector3(5, 50, 5));

	icon = UI::Create("LeatherIcon");
	icon->LoadFile("Icon_Leather.xml");
	tooltipBoxScaleY = 0.55f;

	ItemProto::Init();

	//=========================
	enumName = Item::Leather;
	type = ItemType::Material;
	state = ItemState::OnGround;
	//=========================
	stringName = "Leather";
	weight = 1;

	currentStack = RANDOM->Int(2, 3);
	maxStack = 50;
}

Leather::~Leather()
{

}

void Leather::Init()
{

}

void Leather::Release()
{
}

void Leather::Update()
{
	ImGui::Begin("ItemHierarchy");
	{
		actor->RenderHierarchy();
		icon->RenderHierarchy();
	}
	ImGui::End();


	ItemProto::Update();
}

void Leather::LateUpdate()
{
	//ItemProto::LateUpdate();
}

void Leather::Render()
{
	ItemProto::Render();

	if (INVEN->isOpen && state == ItemState::OnInventory)
	{
		text_stack.left = App.GetWidth() * ((icon->GetWorldPos().x + 1) / 2) - 10;
		text_stack.right = text_stack.left + 1000;
		text_stack.top = App.GetHeight() * ((1 - icon->GetWorldPos().y) / 2) + 15;
		text_stack.bottom = text_stack.top + 200;

		DWRITE->RenderText(
			to_wstring(currentStack) + L"/" + to_wstring(maxStack),
			text_stack,
			13.0f,
			L"Arial",
			Color(1, 1, 1, 0),
			DWRITE_FONT_WEIGHT_REGULAR,
			DWRITE_FONT_STYLE_ITALIC,
			DWRITE_FONT_STRETCH_EXPANDED);
	}
}

void Leather::RenderHierarchy()
{

}

wstring Leather::GetExplain()
{
	wstring exp = L"건설에 사용할 수 있는 튼튼하고 \n좋은 나무입니다.\n";
	wstring exp_sub1 = L"\n무게: " + to_wstring(weight * currentStack);

	return exp + exp_sub1;
}

//bool Leather::IsDestroyed()
//{
//	return false;
//}
//
//void Leather::DestructionEvent()
//{
//}

void Leather::Use()
{
}

