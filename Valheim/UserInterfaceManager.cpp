#include "stdafx.h"
#include "Notification.h"
#include "DamageText.h"
#include "UserInterfaceManager.h"

UserInterfaceManager::UserInterfaceManager()
{
	inventory = new Inventory();
	craft = new Craft();
	minimap = new MiniMap();
}

UserInterfaceManager::~UserInterfaceManager()
{
}

void UserInterfaceManager::Init()
{
}

void UserInterfaceManager::Release()
{
}

void UserInterfaceManager::Update()
{
	inventory->Update();
	craft->Update();
	minimap->Update();

	for (auto iter = notifications.begin(); iter != notifications.end();)
	{
		if ((*iter)->IsTimeOver())
		{
			(*iter)->Release();
			iter = notifications.erase(iter);
		}
		else iter++;
	}

	for (auto iter = damageTexts.begin(); iter != damageTexts.end();)
	{
		if ((*iter)->IsTimeOver())
		{
			(*iter)->Release();
			iter = damageTexts.erase(iter);
		}
		else iter++;
	}

	for (auto& notice : notifications)
		notice->Update();

	for (auto& damageText : damageTexts)
		damageText->Update();
}

void UserInterfaceManager::LateUpdate()
{
	inventory->LateUpdate();
	craft->LateUpdate();
	minimap->LateUpdate();

	/*for (auto& notice : notifications)
		notice->LateUpdate();*/
}

void UserInterfaceManager::PreRender()
{
}

void UserInterfaceManager::Render()
{
	for (auto& notice : notifications)
		notice->Render();

	for (auto& damageText : damageTexts)
		damageText->Render();

	minimap->Render();
	craft->Render();
	inventory->Render();
}

void UserInterfaceManager::ResizeScreen()
{
}

void UserInterfaceManager::AddNotification(Item item, NotificationType type)
{
	Notification* notice = new Notification(item, type);
	notifications.emplace_back(notice);

	NotificationPositionSet();
}

void UserInterfaceManager::NotificationPositionSet()
{
	float baselinePositionY = -0.86f;
	float interval = 0.24f;

	int i = 0;
	for (auto& notice : notifications)
	{
		notice->GetNotificationUI()->SetWorldPosY(baselinePositionY + interval * i++);
	}
}

void UserInterfaceManager::AddDamageText(int value, Vector3 spawnPos)
{
	string valueStr = to_string(value);
	
	spawnPos = spawnPos + Vector3(RANDOM->Float(-0.5f, 0.5f), RANDOM->Float(-0.5f, 0.5f), RANDOM->Float(-0.5f, 0.5f));
	Vector3 interval = PLAYER->GetActor()->GetRight() * 0.2f;

	for (int i = 0; i < valueStr.size(); i++)
	{
		value = valueStr[i] - '0';
		DamageText* damageText = new DamageText(value, spawnPos + interval * i);
		damageTexts.emplace_back(damageText);
	}
}