#include "stdafx.h"
#include "ItemProto.h"
#include "ElderTrophy.h"

ElderTrophy::ElderTrophy()
{
	static int index = 0;
	actor = Actor::Create("ElderTrophy");
	actor->LoadFile("Item_ElderTrophy.xml");
	actor->name = "Item_ElderTrophy" + to_string(index);

	icon = UI::Create("ElderTrophyIcon");
	icon->LoadFile("Icon_ElderTrophy.xml");
	icon->name = "ElderTrophyIcon" + to_string(index++);
	tooltipBoxScaleY = 0.95f;

	ItemProto::Init();

	//=========================
	enumName = Item::ElderTrophy;
	type = ItemType::Material;
	state = ItemState::OnGround;
	//=========================
	stringName = "Elder Trophy";
	weight = 5;

	currentStack = 1;
	maxStack = 1;
}

ElderTrophy::~ElderTrophy()
{

}

void ElderTrophy::Init()
{

}

void ElderTrophy::Release()
{
}

void ElderTrophy::Update()
{
	ImGui::Begin("ItemHierarchy");
	{
		actor->RenderHierarchy();
		icon->RenderHierarchy();
	}
	ImGui::End();


	ItemProto::Update();
}

void ElderTrophy::LateUpdate()
{
	//ItemProto::LateUpdate();
}

void ElderTrophy::Render()
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

void ElderTrophy::RenderHierarchy()
{

}

wstring ElderTrophy::GetExplain()
{
	wstring exp = L"피와 뼈로 이루어진 이 작은 \n것아, 널 나뭇가지처럼 \n부러뜨렸어야 했는데! \n이제 나는 시들고 죽으니, \n빛이 가장 먼저 닿는곳으로 \n나를 인도하라... \n-Elder\n" ;
	wstring exp_sub1 = L"\n무게: " + to_wstring(weight * currentStack);

	return exp + exp_sub1;
}

//bool ElderTrophy::IsDestroyed()
//{
//	return false;
//}
//
//void ElderTrophy::DestructionEvent()
//{
//}

void ElderTrophy::Use()
{
}

