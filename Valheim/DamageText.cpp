#include "stdafx.h"
#include "DamageText.h"


DamageText::DamageText(int value, Vector3 spawnPos)
{
	static int index = 0;
	damageText = Billboard::Create("DamageText");
	damageText->LoadFile("DamageText.xml");
	damageText->name = "DamageText" + to_string(index++);
	damageText->SetWorldPos(spawnPos);

	string path = "Font/";
	switch (value)
	{
		case 0: path += "number_white_0.png"; break;
		case 1: path += "number_white_1.png"; break;
		case 2: path += "number_white_2.png"; break;
		case 3: path += "number_white_3.png"; break;
		case 4: path += "number_white_4.png"; break;
		case 5: path += "number_white_5.png"; break;
		case 6: path += "number_white_6.png"; break;
		case 7: path += "number_white_7.png"; break;
		case 8: path += "number_white_8.png"; break;
		case 9: path += "number_white_9.png"; break;
	}
	SafeReset(damageText->material->diffuseMap);
	damageText->material->diffuseMap = RESOURCE->textures.Load(path);
	damageText->shader->LoadGeometry();
}

DamageText::~DamageText()
{
	damageText->Release();
}

void DamageText::Update()
{
	ImGui::Begin("UI Hierarchy");
	{
		damageText->RenderHierarchy();
	}
	ImGui::End();

	lifeTime += DELTA;

	damageText->MoveWorldPos(damageText->GetUp() * DELTA);

	damageText->Update();
}

void DamageText::Render()
{
	damageText->Render();
}

void DamageText::Release()
{
	damageText->Release();

	delete this;
}
