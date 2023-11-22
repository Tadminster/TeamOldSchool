#pragma once

class GameManager : public Singleton<GameManager>
{
public:
    class Terrain*          map;
    class Water*            sea;
    class Inventory*        inventory;
    class Craft*			craft;
    class Player*           player;
    class MiniMap*          minimap;
    class ObjectManager*    objectManager;

public:
    GameManager();
    ~GameManager();

    void    Init();
    void    Release();
    void    Update();
    void    LateUpdate();
    void    Render();
    void    ResizeScreen();
};
