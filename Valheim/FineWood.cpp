#include "stdafx.h"
#include "ItemProto.h"
#include "FineWood.h"

FineWood::FineWood()
{
	static int index = 0;
	actor = Actor::Create("FineWood");
	actor->LoadFile("Item_FineWood.xml");
	actor->name = "Item_FineWood" + to_string(index);
	actor->SetWorldPos(Vector3(5, 50, 5));

	icon = UI::Create("FineWoodIcon");
	icon->LoadFile("Icon_FineWood.xml");
	icon->name = "FineWoodIcon" + to_string(index++);
	tooltipBoxScaleY = 0.55f;

	ItemProto::Init();

	//=========================
	enumName = Item::FineWood;
	type = ItemType::Material;
	state = ItemState::OnGround;
	//=========================
	stringName = "FineWood";
	weight = 2;

	currentStack = RANDOM->Int(3, 5);
	maxStack = 50;
}

FineWood::~FineWood()
{

}

void FineWood::Init()
{

}

void FineWood::Release()
{
}

void FineWood::Update()
{
	//ImGui::Begin("ItemHierarchy");
	//{
	//	actor->RenderHierarchy();
	//	icon->RenderHierarchy();
	//}
	//ImGui::End();


	ItemProto::Update();
}

void FineWood::LateUpdate()
{
	//ItemProto::LateUpdate();
}

void FineWood::Render()
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

void FineWood::RenderHierarchy()
{

}

wstring FineWood::GetExplain()
{
	wstring exp = L"좋은 장비를 만드는데에 사용 \n할 수 있는 고품질 목재입니다.\n";
	wstring exp_sub1 = L"\n무게: " + to_wstring(weight * currentStack);

	return exp + exp_sub1;
}

//bool FineWood::IsDestroyed()
//{
//	return false;
//}
//
//void FineWood::DestructionEvent()
//{
//}

void FineWood::Use()
{
}

