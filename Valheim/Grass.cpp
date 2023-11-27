#include "stdafx.h"
#include "Grass.h"

Grass::Grass(Vector3 spawnPos)
{
	static int index = 0;
	actor = Actor::Create("Grass" + index++);
	actor->LoadFile("Feature_GrassGreen.xml");
	actor->SetWorldPos(spawnPos);
}

Grass::~Grass()
{
}

void Grass::Init()
{
}

void Grass::Update()
{
	actor->Update();
}

void Grass::LateUpdate()
{
}

void Grass::Render()
{
	actor->Render();
}

void Grass::Release()
{
}

bool Grass::ReceivedDamageEvent(float damage, WeaponType wType)
{
	return false;
}

bool Grass::IsDestroyed()
{
	return false;
}

void Grass::DestructionEvent()
{
}