#include "stdafx.h"
#include "ItemProto.h"
#include "Woodpile.h"

Woodpile::Woodpile()
{
	static int index = 0;
	actor = Actor::Create("Woodpile");
	actor->LoadFile("Woodpile.xml");
	actor->name = "Woodpile" + index++;
	actor->SetWorldPos(Vector3(5, 50, 5));

	icon = UI::Create("WoodpileIcon");
	icon->LoadFile("Icon_Woodpile.xml");
	tooltipBoxScaleY = 0.55f;

	ItemProto::Init();

	//=========================
	enumName		= Item::Woodpile;
	type			= ItemType::Material;
	state			= ItemState::OnGround;
	//=========================
	stringName		= "Woodpile";
	weight			= 1;

	currentStack	= RANDOM->Int(2, 10);
	maxStack		= 100;
}

Woodpile::~Woodpile()
{

}

void Woodpile::Init()
{

}

void Woodpile::Release()
{
}

void Woodpile::Update()
{
	ImGui::Begin("ItemHierarchy");
	{
		actor->RenderHierarchy();
		icon->RenderHierarchy();
	}
	ImGui::End();


	ItemProto::Update();
}

void Woodpile::LateUpdate()
{
	//ItemProto::LateUpdate();
}

void Woodpile::Render()
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

void Woodpile::RenderHierarchy()
{

}

wstring Woodpile::GetExplain()
{
	wstring exp = L"건설에 사용할 수 있는 튼튼하고 \n좋은 나무입니다.\n";
	wstring exp_sub1 = L"\n무게: " + to_wstring(weight * currentStack);

	return exp + exp_sub1;
}

//bool Woodpile::IsDestroyed()
//{
//	return false;
//}
//
//void Woodpile::DestructionEvent()
//{
//}

void Woodpile::Use()
{
}

