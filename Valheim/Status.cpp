#include "stdafx.h"
#include "Status.h"

Status::Status()
{
	bgIMG = UI::Create("Status");
	bgIMG->name = "Status";
	bgIMG->LoadFile("Unit/Player_StatusBGIMG.xml");
	bgIMG->SetWorldPosX(App.GetWidth() * 0.5f / App.GetWidth());
	bgIMG->SetWorldPosY(App.GetHalfHeight() * 0.7f / App.GetHalfHeight());

}

Status::~Status()
{
}

void Status::Init()
{
	bgIMG->Find("Skill")->visible = false;
	bgIMG->Find("Skill_Pressed")->visible = false;
}

void Status::Release()
{
}

void Status::Update()
{
	ImGui::Begin("UI Hierarchy");
	{
		bgIMG->RenderHierarchy();
	}
	ImGui::End();
	
	if (isOpen) bgIMG->visible = true;
	else bgIMG->visible = false;

	if (INPUT->KeyDown('T'))
	{
		if (CRAFT->isOpen) CRAFT->isOpen = false;
		isOpen = !isOpen;
	}
	if (isOpen)
	{
		if (CRAFT->isOpen) isOpen = false;
	}

	bgIMG->Update();
}

void Status::Render()
{
	bgIMG->Render();
}
