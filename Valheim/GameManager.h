#pragma once

class GameManager : public Singleton<GameManager>
{
public:
    class Terrain*          map;
    class Water*            sea;
    class Player*           player;
    class Inventory*        inventory;
    class ObjectManager*    objectManager;

    bool 			    debugMode{ true };

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
