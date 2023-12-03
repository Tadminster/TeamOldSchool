#include "stdafx.h"
#include "SoundDB.h"
#include "TitleUI.h"

TitleUI::TitleUI()
{
	titleUI = UI::Create("TitleUI");
	titleUI->LoadFile("UI_Title.xml");

	panel = static_cast<UI*>(titleUI->Find("0_Panel"));
	infoStart.btn = static_cast<UI*>(titleUI->Find("1_Btn_Start"));
	infoOption.btn = static_cast<UI*>(titleUI->Find("1_Btn_Option"));
	infoExit.btn = static_cast<UI*>(titleUI->Find("1_Btn_Exit"));

	fadeOut = UI::Create();
	fadeOut->name = "fade";
	fadeOut->LoadFile("UI_FadeOut.xml");

	soundDB = new SoundDB();
}

TitleUI::~TitleUI()
{
}

void TitleUI::Init()
{
	soundDB->Init();
}

void TitleUI::Release()
{
	titleUI->Release();
	fadeOut->Release();
	delete soundDB;
}

void TitleUI::Update()
{
	if (isPostStart)
	{
		fadeout += DELTA;
		fadeOut->material->opacity = fadeout * (1.0f / FADEOUT);
	}

	fadeOut->Update();
	titleUI->Update();
}

void TitleUI::LateUpdate()
{
	// 패널 위에 마우스가 올라가 있으면
	// 버튼들의 마우스오버 상태를 체크
	if (!SETTING->isOpen && panel->MouseOver())
	{
		// 시작 버튼 마우스오버
		if (infoStart.btn->MouseOver())
		{
			// 다른 버튼 상태 초기화 ================
			BtnInitalize(infoOption);
			BtnInitalize(infoExit);
			// =====================================
			// 시작 버튼 상태가 NONE 일 때
			if (infoStart.state == TitleBtnState::NONE)
			{
				BtnMouseOver(infoStart);
			}
			// 시작 버튼 상태가 마우스오버 일 때
			else if (infoStart.state == TitleBtnState::MOUSE_OVER)
			{
				BtnMouseClick(infoStart);
			}
			// 시작 버튼 상태가 마우스클릭 일 때
			else if (infoStart.state == TitleBtnState::MOUSE_CLICK)
			{
				// 마우스 왼쪽 버튼을 떼면
				if (INPUT->KeyUp(VK_LBUTTON))
				{
					isPostStart = true;

					// 다음 씬으로 이동 (로딩 씬)
					SCENE->ChangeScene(SceneName::Loading, FADEOUT);
				}
			}
		}
		// 옵션 버튼 마우스오버
		else if (infoOption.btn->MouseOver())
		{
			// 다른 버튼 상태 초기화 ================
			BtnInitalize(infoStart);
			BtnInitalize(infoExit);
			// =====================================
			// 옵션 버튼 상태가 NONE 일 때
			if (infoOption.state == TitleBtnState::NONE)
			{
				BtnMouseOver(infoOption);
			}
			else if (infoOption.state == TitleBtnState::MOUSE_OVER)
			{
				BtnMouseClick(infoOption);
			}
			else if (infoOption.state == TitleBtnState::MOUSE_CLICK)
			{
				if (INPUT->KeyUp(VK_LBUTTON))
				{
					// 옵션창 활성화
					SETTING->OpenSetting();
					infoOption.state == TitleBtnState::MOUSE_OVER;
				}
			}
		}
		// 종료 버튼 마우스오버
		else if (infoExit.btn->MouseOver())
		{
			// 다른 버튼 상태 초기화 ================
			BtnInitalize(infoStart);
			BtnInitalize(infoOption);
			// =====================================
			// 종료 버튼 상태가 NONE 일 때
			if (infoExit.state == TitleBtnState::NONE)
			{
				BtnMouseOver(infoExit);
			}
			else if (infoExit.state == TitleBtnState::MOUSE_OVER)
			{
				BtnMouseClick(infoExit);
			}
			else if (infoExit.state == TitleBtnState::MOUSE_CLICK)
			{
				// 마우스 왼쪽 버튼을 떼면
				if (INPUT->KeyUp(VK_LBUTTON))
				{
					PostQuitMessage(0);
				}
			}
		}
	}
	// 패널 위에 마우스가 없으면
	else
	{
		// 버튼들의 상태를 초기화
		BtnInitalize(infoStart);
		BtnInitalize(infoOption);
		BtnInitalize(infoExit);
	}
}

void TitleUI::Render()
{
	titleUI->Render();
	fadeOut->Render();
}

void TitleUI::ResizeScreen()
{
}

void TitleUI::RenderHierarchy()
{
	titleUI->RenderHierarchy();
}

void TitleUI::BtnInitalize(BtnInfo& btnInfo)
{
	// 버튼의 상태가 NONE 이 아니면
	if (btnInfo.state != TitleBtnState::NONE)
	{
		// 버튼의 스케일을 기본 스케일로 변경
		btnInfo.btn->scale = btnBaseScale;

		// 버튼의 상태를 NONE 으로 변경
		btnInfo.state = TitleBtnState::NONE;
	}
}

void TitleUI::BtnMouseOver(BtnInfo& btnInfo)
{
	// 버튼 스케일을 마우스오버 스케일로 변경
	btnInfo.btn->scale = btnMouseOverScale;

	// 버튼 상태를 마우스오버로 변경
	btnInfo.state = TitleBtnState::MOUSE_OVER;
}

void TitleUI::BtnMouseClick(BtnInfo& btnInfo)
{
	// 마우스 왼쪽 버튼을 누르면
	if (INPUT->KeyDown(VK_LBUTTON))
	{
		// 클릭음 재생
		SOUND->Play(UI_CLICK);

		// 스타트버튼 상태를 마우스 클릭으로 변경
		btnInfo.state = TitleBtnState::MOUSE_CLICK;
	}
}
