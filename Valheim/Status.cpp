#include "stdafx.h"
#include "Status.h"

Status::Status()
{
	bgIMG = UI::Create("Status");
	bgIMG->name = "Status";
	bgIMG->LoadFile("Unit/Player_StatusBGIMG.xml");
	bgIMG->SetWorldPosX(App.GetWidth() * 0.5f / App.GetWidth());
	bgIMG->SetWorldPosY(App.GetHalfHeight() * 0.7f / App.GetHalfHeight());

	btnCreate = static_cast<UI*>(bgIMG->Find("SKill"));
}

Status::~Status()
{
}

void Status::Init()
{
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

	if (INPUT->KeyDown('T')) isOpen = !isOpen;

	string path = "Player_Male/";
	
	if (isOpen)
	{
		//if (static_cast<UI*>(bgIMG->Find("SKill"))->MouseOver())
		//if (btnCreate->MouseOver()){}
		//{
		//	if (INPUT->KeyPress(VK_LBUTTON))
		//	{
		//		static_cast<UI*>(bgIMG->Find("SKill"))->visible = false;
		//		static_cast<UI*>(bgIMG->Find("SKill_Highlight"))->visible = false;
		//		static_cast<UI*>(bgIMG->Find("SKill_Pressed"))->visible = true;
		//	}
		//	else
		//	{
		//		bgIMG->Find("SKill")->visible = false;
		//		bgIMG->Find("SKill_Highlight")->visible = true;
		//		bgIMG->Find("SKill_Pressed")->visible = false;
		//	}
		//}
		////else
		//{
		//	bgIMG->Find("SKill")->visible = true;
		//	bgIMG->Find("SKill_Highlight")->visible = false;
		//	bgIMG->Find("SKill_Pressed")->visible = false;
		//}
	}
	


	bgIMG->Update();
}

void Status::Render()
{
	bgIMG->Render();
}
