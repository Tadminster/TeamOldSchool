#pragma once
#define FADEOUT 3.0f
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
    UI*         panel;                  // 패널을 가리킬 포인터
    UI*         arrow;                  // 화살표를 가리킬 포인터
    BtnInfo     infoStart;              // 시작 버튼을 가리키는 포인터와 상태를 저장한 구조체
    BtnInfo     infoOption;			    // 옵션 버튼을 가리키는 포인터와 상태를 저장한 구조체
    BtnInfo     infoExit;				// 종료 버튼을 가리키는 포인터와 상태를 저장한 구조체
    // ==============================================================
    Vector3     btnBaseScale{ 0.14f, 0.06f, 0.0f };         // 버튼의 기본 크기
    Vector3     btnMouseOverScale{ 0.16f, 0.08f, 0.0f };	// 버튼의 마우스오버 크기
    // ==============================================================
    class UI*   fadeOut{ nullptr };	    // fadeout 효과를 위한 UI
    float       fadeout{ 0 };           // fadeout의 opacity
    //==============================================================
    class       SoundDB* soundDB;

public:
    bool        isPostStart{false};	    // 시작 버튼을 눌렀는지 판별

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

