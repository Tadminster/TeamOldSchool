#include "stdafx.h"
#include "GameManager.h"
#include "ParticleManager.h"
#include "MonsterManager.h"

GameManager::GameManager()
{
	map = Terrain::Create("Terrain");
	map->LoadFile("Terrain.xml");
	map->PerlinNoiseHeightMap();
	map->CreateStructuredBuffer();

	ocean = Water::Create();
	ocean->LoadFile("Water.xml");

	objectManager	= new ObjectManager();
	uiManager		= new UserInterfaceManager();

	player			= new Player();
	elder			= new Elder();
	monster			= new MonsterManager();
	astar			= new AStar();

	recipe			= new Recipe();

}

GameManager::~GameManager()
{
}

void GameManager::Init()
{
	astar->CreateNode(MAP, MAP->rowSize * ASTARNODENUM, OBJ->GetColliders());
}

void GameManager::Release()
{
	map->Release();
	ocean->Release();
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
