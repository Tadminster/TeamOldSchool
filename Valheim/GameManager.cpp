#include "stdafx.h"
#include "GameManager.h"

GameManager::GameManager()
{
	map = Terrain::Create("Terrain");
	player = new Player();
	objectManager = new ObjectManager();


	map->LoadFile("TerrainPerlin.xml");
	map->PerlinNoiseHeightMap();
	map->CreateStructuredBuffer();
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
}
