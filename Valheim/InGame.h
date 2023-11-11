#pragma once
class InGame : public Scene
{
private:
    Camera*     tempCamera;

    Grid*       grid;
	Sky*        skyBox;

    GameManager* gameManager;
   
    class InventoryUiPannel*     playerInventoryUI;
    class GameOption*            playerOptionUI;
    class Wood*                     wood;
    class StoneAxe*                 stoneAxe;

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

