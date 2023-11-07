#include "stdafx.h"
#include "GameOption.h"

GameOption::GameOption()
{
	gameOption = UI::Create("gameOption");


	//gameOption->Find("PlayerGameOption")->visible = false;
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
