#include "stdafx.h"
#include "GameOption.h"

GameOption::GameOption()
{
	gameOption = UI::Create("gameOption");
	gameOption->LoadFile("inGameOption.xml");

	gameOption->visible = false;
	gameOption->Find("continue")->visible = true;
	gameOption->Find("save")->visible = true;
	gameOption->Find("lastsavetime")->visible = true;
	gameOption->Find("setting")->visible = true;
	gameOption->Find("logout")->visible = true;
	gameOption->Find("exit")->visible = true;

	

}

GameOption::~GameOption()
{
}

void GameOption::Init()
{
}

void GameOption::Release()
{
}

void GameOption::Update()
{

	ImGui::Begin("Hierarchy");
	{
		gameOption->RenderHierarchy();
	}
	ImGui::End();
	gameOption->Update();



}

void GameOption::LateUpdate()
{
	//옵션창 열기닫기 기능입니다
	if (INPUT->KeyDown(VK_F10))
	{
		gameOption->visible = !gameOption->visible;
	}

}

void GameOption::PreRender()
{
}

void GameOption::Render()
{
	gameOption->Render();
}

void GameOption::ResizeScreen()
{
}
