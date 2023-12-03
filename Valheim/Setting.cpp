#include "stdafx.h"
#include "Setting.h"

Setting::Setting()
{
	settingPanel = UI::Create("SettingPanel");
	settingPanel->LoadFile("UI_SettingPanel.xml");
	
}

Setting::~Setting()
{

}

void Setting::Init()
{
	settingPanel->visible = false;
	

	/*float appHalfWidth = App.GetHalfWidth();
	float appHalfHeight = App.GetHalfHeight();

	float panelSizeX = 378.0f;
	float panelSizeY = 250.0f;

	settingPanel->SetWorldPosX(App.GetHalfWidth() - panelSizeX * 0.5f / App.GetWidth());
	settingPanel->SetWorldPosY(App.GetHalfHeight() + panelSizeY * 0.5f / App.GetHeight());

	settingPanel->scale.x = panelSizeX / appHalfWidth;
	settingPanel->scale.y = panelSizeY / appHalfHeight;*/

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
