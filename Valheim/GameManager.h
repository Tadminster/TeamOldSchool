#pragma once
#define ASTARNODENUM 2.5f
class GameManager : public Singleton<GameManager>
{
public:
    class Terrain*              map;
    class Water*                sea;

    class Recipe*			    recipe;
    class Player*               player;
    class MonsterManager*       monster;

    class ObjectManager*        objectManager;
    class ParticleManager*      particleManager;
    class UserInterfaceManager* uiManager;

    class AStar*                astar;
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
