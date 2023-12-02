#include "stdafx.h"
#include "Setting.h"

Setting::Setting()
{
	settingPanel = UI::Create("SettingPanel");
	//settingPanel->LoadFile("UI_SettingPanel");
}

Setting::~Setting()
{

}

void Setting::Init()
{

}

void Setting::Release()
{

}

void Setting::Update()
{
	ImGui::Begin("UI Hierarchy");
	{
		settingPanel->RenderHierarchy();
	}
	ImGui::End();

	if (INPUT->KeyDown(VK_F8))
	{
		settingPanel->visible = !settingPanel->visible;
	}

	settingPanel->Update();
}

void Setting::LateUpdate()
{
	
}

void Setting::Render()
{
	settingPanel->Render();
}
