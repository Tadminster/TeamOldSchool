#pragma once

class GameManager : public Singleton<GameManager>
{
public:
    class Terrain*      map;
    class Player*       player;

    bool 			    debugMode{ false };

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
