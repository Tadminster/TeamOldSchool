#include "stdafx.h"
#include "TitleScene.h"

TitleScene::TitleScene()
{
	titleCamera = Camera::Create("titleCamera");
	titleCamera->LoadFile("Cam.xml");
	Camera::main = titleCamera;
}

TitleScene::~TitleScene()
{
	titleCamera->Release();
}

void TitleScene::Init()
{

}

void TitleScene::Release()
{
}

void TitleScene::Update()
{

}

void TitleScene::LateUpdate()
{

}

void TitleScene::PreRender()
{
	
}

void TitleScene::Render()
{
	
}

void TitleScene::ResizeScreen()
{
	Camera::main->viewport.x = 0.0f;
	Camera::main->viewport.y = 0.0f;
	Camera::main->viewport.width = App.GetWidth();
	Camera::main->viewport.height = App.GetHeight();

	Camera::main->width = App.GetWidth();
	Camera::main->height = App.GetHeight();
}
