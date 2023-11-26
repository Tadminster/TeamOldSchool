#include "stdafx.h"
#include "GameManager.h"
#include "ParticleManager.h"

GameManager::GameManager()
{
	map = Terrain::Create("Terrain");
	map->LoadFile("Terrain.xml");
	map->PerlinNoiseHeightMap();
	map->CreateStructuredBuffer();

	sea = Water::Create();
	sea->LoadFile("Water.xml");

	objectManager = new ObjectManager();
	particleManager = new ParticleManager();
	worldtimeManager = new WorldTimeManager();\
	uiManager = new UserInterfaceManager();

	player = new Player();

	recipe = new Recipe();

}

GameManager::~GameManager()
{
}

void GameManager::Init()
{
}

void GameManager::Release()
{
}

void GameManager::Update()
{

}

void GameManager::LateUpdate()
{
}

void GameManager::Render()
{
}

void GameManager::ResizeScreen()
{
	Camera::main->viewport.x = 0.0f;
	Camera::main->viewport.y = 0.0f;
	Camera::main->viewport.width = App.GetWidth();
	Camera::main->viewport.height = App.GetHeight();

	Camera::main->width = App.GetWidth();
	Camera::main->height = App.GetHeight();
}
