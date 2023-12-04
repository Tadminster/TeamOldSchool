#pragma once
#define FADEOUT 3.0f
class InGame : public Scene
{
private:
    Scattering*                     scattering;
    GameManager*                    gameManager;
    
    class MonsterManager* monster;

    UI* mouseIcon;
    UI* mouseIcon2;
    class UI* fadeOut{ nullptr };	    // fadeout 효과를 위한 UI
    float       fadeout{ 0 };           // fadeout의 opacity
    bool isEnding{ false };
    class MonsterManager*           monster;
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

