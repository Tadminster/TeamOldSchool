#pragma once
class InGame : public Scene
{
private:
    Camera*                         tempCamera;
    Camera*                         tempCamera2;

    Grid*                           grid;
	Sky*                            skyBox;
        
    GameManager*                    gameManager;
   
    class InventoryUiPannel*        playerInventoryUI;
    class GameOption*               playerOptionUI;
    class StoneAxe*                 stoneAxe;

    class Troll*                    troll;
public:
    InGame();
    ~InGame();
    virtual void Init() override;
    virtual void Release() override;
    virtual void Update() override;
    virtual void LateUpdate() override;
    virtual void PreRender() override;
    virtual void Render() override;
    virtual void ResizeScreen() override;
};

