#pragma once
#define FADEOUT 2.0f
enum class TitleBtnState { NONE, MOUSE_OVER, MOUSE_CLICK };
struct BtnInfo
{
	UI*             btn;
	TitleBtnState   state{ TitleBtnState::NONE };
};

class TitleUI
{
private:
    UI*         titleUI;
    // ==============================================================
    UI*         panel;
    BtnInfo     infoStart;
    BtnInfo     infoOption;
    BtnInfo     infoExit;
    // ==============================================================
    Vector3     btnBaseScale{ 0.14f, 0.06f, 0.0f };
    Vector3     btnMouseOverScale{ 0.16f, 0.08f, 0.0f };
    // ==============================================================
    class UI*   fadeOut = nullptr;
    float       fadeout = 5;
    bool        isPostQuit = false;
public:
    TitleUI();
    ~TitleUI();
    void Init();
    void Release();
    void Update();
    void LateUpdate();
    void Render();
    void ResizeScreen();
    void RenderHierarchy();

    void BtnInitalize(BtnInfo& btnInfo);
    void BtnMouseOver(BtnInfo& btnInfo);
    void BtnMouseClick(BtnInfo& btnInfo);
};

