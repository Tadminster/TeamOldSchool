#pragma once

class GameManager : public Singleton<GameManager>
{
public:
    class Terrain*          map;
    class Water*            sea;
    class Inventory*        inventory;
    class Craft*			craft;
    class Recipe*			recipe;
    class Player*           player;
    class MiniMap*          minimap;
    class ObjectManager*    objectManager;
    class ParticleManager*  particleManager;

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
