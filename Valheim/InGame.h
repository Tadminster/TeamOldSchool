#pragma once
class InGame : public Scene
{
private:
    Camera*                         tempCamera;
    bool                            isDebugCam{ false };
    bool                            isDebugCamControl{ true };

    Grid*                           grid;

    class SoundDB*                  soundDB;
	
    Scattering*                     scattering;
   
    GameManager*                    gameManager;
    
   
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

