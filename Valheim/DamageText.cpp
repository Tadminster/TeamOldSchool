#include "stdafx.h"
#include "DamageText.h"


DamageText::DamageText(int value, Vector3 spawnPos)
{
	static int index = 0;
	damageText = Billboard::Create("DamageDisplay");
	damageText->LoadFile("DamageDisplay.xml");
	damageText->name = "DamageText" + to_string(index++);
	damageText->SetWorldPos(spawnPos);
}

DamageText::~DamageText()
{
	damageText->Release();
}

void DamageText::Update()
{
	lifeTime += DELTA;

	damageText->Update();
}

void DamageText::Render()
{
	damageText->Render();
}
