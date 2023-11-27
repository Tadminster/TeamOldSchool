#pragma once

class GameManager : public Singleton<GameManager>
{
public:
    class Terrain*              map;
    class Water*                sea;

    class Recipe*			    recipe;
    class Player*               player;

    class ObjectManager*        objectManager;
    class ParticleManager*      particleManager;
    class UserInterfaceManager* uiManager;

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
