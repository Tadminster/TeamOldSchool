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
    UI*         panel;                  // �г��� ����ų ������
    BtnInfo     infoStart;              // ���� ��ư�� ����Ű�� �����Ϳ� ���¸� ������ ����ü
    BtnInfo     infoOption;			    // �ɼ� ��ư�� ����Ű�� �����Ϳ� ���¸� ������ ����ü
    BtnInfo     infoExit;				// ���� ��ư�� ����Ű�� �����Ϳ� ���¸� ������ ����ü
    // ==============================================================
    Vector3     btnBaseScale{ 0.14f, 0.06f, 0.0f };         // ��ư�� �⺻ ũ��
    Vector3     btnMouseOverScale{ 0.16f, 0.08f, 0.0f };	// ��ư�� ���콺���� ũ��
    // ==============================================================
    class UI*   fadeOut = nullptr;	    // fadeout ȿ���� ���� UI
    float       fadeout = 5;            // fadeout�� opacity
    bool        isPostQuit = false;	    // PostQuitMessage�� �ѹ��� ȣ���ϱ� ���� ����
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
