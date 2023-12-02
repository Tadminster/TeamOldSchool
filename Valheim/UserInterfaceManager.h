#pragma once
enum class NotificationType;

class UserInterfaceManager
{
private:
    list<class Notification*>   notifications;
    list<class DamageText*>     damageTexts;

public:
    class Inventory*    inventory;
    class Craft*        craft;
    class MiniMap*      minimap;
    class Status*       status;
    class Setting*      setting;

public:
    UserInterfaceManager();
    ~UserInterfaceManager();
    void Init();
    void Release();
    void Update();
    void LateUpdate();
    void PreRender();
    void Render();
    void ResizeScreen();

    void AddNotification(Item item, NotificationType type);
    void NotificationPositionSet();

    void AddDamageText(int value, Vector3 spawnPos);
};

