#include "stdafx.h"
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
}

TitleUI::~TitleUI()
{
}

void TitleUI::Init()
{
}

void TitleUI::Release()
{
	titleUI->Release();
	fadeOut->Release();
}

void TitleUI::Update()
{
	if (fadeout < FADEOUT)
	{
		fadeout += DELTA;
		fadeOut->material->opacity = fadeout * (1.0f / FADEOUT);
	}
	else
	{
		if(isPostQuit) PostQuitMessage(0);
	}
	

	fadeOut->Update();
	titleUI->Update();
}

void TitleUI::LateUpdate()
{
	// �г� ���� ���콺�� �ö� ������
	// ��ư���� ���콺���� ���¸� üũ
	if (panel->MouseOver())
	{
		// ���� ��ư ���콺����
		if (infoStart.btn->MouseOver())
		{
			// �ٸ� ��ư ���� �ʱ�ȭ ================
			BtnInitalize(infoOption);
			BtnInitalize(infoExit);
			// =====================================
			// ���� ��ư ���°� NONE �� ��
			if (infoStart.state == TitleBtnState::NONE)
			{
				BtnMouseOver(infoStart);
			}
			// ���� ��ư ���°� ���콺���� �� ��
			else if (infoStart.state == TitleBtnState::MOUSE_OVER)
			{
				BtnMouseClick(infoStart);
			}
			// ���� ��ư ���°� ���콺Ŭ�� �� ��
			else if (infoStart.state == TitleBtnState::MOUSE_CLICK)
			{
				// ���콺 ���� ��ư�� ����
				if (INPUT->KeyUp(VK_LBUTTON))
				{
					// ���� ������ �̵� (�ε� ��)
					SCENE->ChangeScene("Loading", FADEOUT);
					fadeout = 0;
				}
			}
		}
		// �ɼ� ��ư ���콺����
		else if (infoOption.btn->MouseOver())
		{
			// �ٸ� ��ư ���� �ʱ�ȭ ================
			BtnInitalize(infoStart);
			BtnInitalize(infoExit);
			// =====================================
			// �ɼ� ��ư ���°� NONE �� ��
			if (infoOption.state == TitleBtnState::NONE)
			{
				BtnMouseOver(infoOption);
			}
			else if (infoStart.state == TitleBtnState::MOUSE_OVER)
			{
				BtnMouseClick(infoOption);
			}
			else if (infoStart.state == TitleBtnState::MOUSE_CLICK)
			{
				// �ɼ�â Ȱ��ȭ
			}
		}
		// ���� ��ư ���콺����
		else if (infoExit.btn->MouseOver())
		{
			// �ٸ� ��ư ���� �ʱ�ȭ ================
			BtnInitalize(infoStart);
			BtnInitalize(infoOption);
			// =====================================
			// ���� ��ư ���°� NONE �� ��
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
				// ���콺 ���� ��ư�� ����
				if (INPUT->KeyUp(VK_LBUTTON))
				{
					fadeout = 0;
					isPostQuit = true;
				}
			}
		}
	}
	// �г� ���� ���콺�� ������
	else
	{
		// ��ư���� ���¸� �ʱ�ȭ
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
	// ��ư�� ���°� NONE �� �ƴϸ�
	if (btnInfo.state != TitleBtnState::NONE)
	{
		// ��ư�� �������� �⺻ �����Ϸ� ����
		btnInfo.btn->scale = btnBaseScale;

		// ��ư�� ���¸� NONE ���� ����
		btnInfo.state = TitleBtnState::NONE;
	}
}

void TitleUI::BtnMouseOver(BtnInfo& btnInfo)
{
	// ��ư �������� ���콺���� �����Ϸ� ����
	btnInfo.btn->scale = btnMouseOverScale;

	// ��ư ���¸� ���콺������ ����
	btnInfo.state = TitleBtnState::MOUSE_OVER;
}

void TitleUI::BtnMouseClick(BtnInfo& btnInfo)
{
	// ���콺 ���� ��ư�� ������
	if (INPUT->KeyDown(VK_LBUTTON))
	{
		// ��ŸƮ��ư ���¸� ���콺 Ŭ������ ����
		btnInfo.state = TitleBtnState::MOUSE_CLICK;
	}
}