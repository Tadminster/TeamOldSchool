#include "stdafx.h"
#include "ItemProto.h"
#include "Leather.h"

Leather::Leather()
{
	static int index = 0;
	actor = Actor::Create("Leather");
	actor->LoadFile("Item_Leather.xml");
	actor->name = "Item_Leather" + to_string(index);
	actor->SetWorldPos(Vector3(5, 50, 5));

	icon = UI::Create("LeatherIcon");
	icon->LoadFile("Icon_Leather.xml");
	icon->name = "LeatherIcon" + to_string(index++);
	tooltipBoxScaleY = 0.55f;

	ItemProto::Init();

	//=========================
	enumName = Item::Leather;
	type = ItemType::Material;
	state = ItemState::OnGround;
	//=========================
	stringName = "Goblin Leather";
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
	wstring exp = L"고블린에게서 벗겨낸 \n가죽입니다.\n";
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

