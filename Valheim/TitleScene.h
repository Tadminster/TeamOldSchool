#pragma once
class TitleScene : public Scene
{
private:
    Camera*         titleCamera;

    UI*             btnStart;
    UI*             btnOption;
    UI*             btnExit;

public:
    TitleScene();
    ~TitleScene();
    virtual void Init() override;
    virtual void Release() override;
    virtual void Update() override;
    virtual void LateUpdate() override;
    virtual void PreRender() override;
    virtual void Render() override;
    virtual void ResizeScreen() override;
};

