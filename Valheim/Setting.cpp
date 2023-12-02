#include "stdafx.h"
#include "Setting.h"

Setting::Setting()
{
	settingPanel = UI::Create("SettingPanel");
	settingPanel->LoadFile("UI_SettingPanel.xml");
	settingPanel->SetWorldPosX(App.GetWidth() * 0.5f / App.GetWidth());
	settingPanel->SetWorldPosY(App.GetHeight() * 0.5f / App.GetHeight());
}

Setting::~Setting()
{

}

void Setting::Init()
{
	settingPanel->visible = false;

	float appWidth = App.GetWidth();
	float appHeight = App.GetHeight();

	float panelSizeX = 300.0f;
	float panelSizeY = 500.0f;

	settingPanel->scale.x = panelSizeX / appWidth;
	settingPanel->scale.y = panelSizeY / appHeight;

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
