#include "stdafx.h"
#include "GameManager.h"

GameManager::GameManager()
{
	map = Terrain::Create("Terrain");
	map->LoadFile("TerrainPerlin.xml");
	map->PerlinNoiseHeightMap();
	map->CreateStructuredBuffer();

	sea = Water::Create();
	sea->LoadFile("Water.xml");

	inventory = new Inventory();

	objectManager = new ObjectManager();

	player = new Player();
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
	if (INPUT->KeyDown(VK_F1))
	{
		debugMode = !debugMode;
		ResizeScreen();
	}
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
