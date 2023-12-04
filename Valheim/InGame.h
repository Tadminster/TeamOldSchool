#pragma once
class InGame : public Scene
{
private:
    Scattering*                     scattering;
    GameManager*                    gameManager;
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

