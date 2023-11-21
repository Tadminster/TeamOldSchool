#include "stdafx.h"
#include "Craft.h"

Craft::Craft()
{
	craftUI = UI::Create("Craft");
	craftUI->LoadFile("UI_Craft.xml");
	craftUI->SetWorldPosX(App.GetWidth() * 0.5f / App.GetWidth());
	craftUI->SetWorldPosY(-App.GetHalfHeight() * 0.1f / App.GetHalfHeight());
}

Craft::~Craft()
{
}

void Craft::Init()
{
}

void Craft::Release()
{
}

void Craft::Update()
{
	ImGui::Begin("Hierarchy");
	{
		craftUI->RenderHierarchy();
	}
	ImGui::End();

	if (INVEN->isOpen)
		craftUI->Update();
}

void Craft::LateUpdate()
{
}

void Craft::PreRender()
{
}

void Craft::Render()
{
	if (INVEN->isOpen)
		craftUI->Render();
}

void Craft::ResizeScreen()
{
}
