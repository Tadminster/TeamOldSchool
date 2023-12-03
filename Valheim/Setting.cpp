#include "stdafx.h"
#include "Setting.h"

Setting::Setting()
{
	settingPanel = UI::Create("SettingPanel");
	settingPanel->LoadFile("UI_SettingPanel.xml");

	volumeUp.button = static_cast<UI*>(settingPanel->Find("volumeUp"));
	volumeDown.button = static_cast<UI*>(settingPanel->Find("volumeDown"));
	turnAndOffvolume.button = static_cast<UI*>(settingPanel->Find("turnAndOffvolume"));

	volumeIcon = UI::Create("VolumeIcon");
	volumeIcon->LoadFile("UI_Volume_Icon.xml");

}

Setting::~Setting()
{

}

void Setting::Init()
{
	settingPanel->visible = false;
	volumeIcon->visible = false;

	BtnInitalize(volumeUp);
	BtnInitalize(volumeDown);
	BtnInitalize(turnAndOffvolume);

}

void Setting::Release()
{
	settingPanel->Release();
	volumeIcon->Release();
}

void Setting::Update()
{

	ImGui::Begin("UI Hierarchy");
	{
		settingPanel->RenderHierarchy();
		volumeIcon->RenderHierarchy();
	}
	ImGui::End();

	//�г� ���� �ݱ�
	// �κ��丮, ����â ����â�� �������� �ʰ� �ΰ��� ���϶��� ESC �� ����â �ҷ�����
	if (SCENE->IsMacthScene(SceneName::InGame))
	{
		if ((not INVEN->isOpen) and (not STATUS->isOpen) and (not CRAFT->isOpen))
		{
			if (INPUT->KeyDown(VK_ESCAPE))
			{
				volumeIcon->visible = !volumeIcon->visible;
				settingPanel->visible = !settingPanel->visible;
				isOpen = !isOpen;
			}
		}
	}
	//Ÿ��Ʋ ������ ����â �Ѱ� ����
	else if (SCENE->IsMacthScene(SceneName::Title))
	{
		if (INPUT->KeyDown(VK_ESCAPE))
		{
			volumeIcon->visible = !volumeIcon->visible;
			settingPanel->visible = !settingPanel->visible;
			isOpen = !isOpen;
		}
	}

	if (isOpen)
	{
		settingPanel->Update();
		volumeIcon->Update();
	}

}

void Setting::LateUpdate()
{

	//����â	�г����� ���콺�� �ö� ������ 
	//��ư���� ����üũ
	if (isOpen and settingPanel->MouseOver())
	{
		//���� Ű��� ��ư ���콺 �����϶�
		if (volumeUp.button->MouseOver())
		{
			if (volumeUp.state == SettingBtnState::NONE)
			{
				BtnMouseOver(volumeUp);
			}
			else if (volumeUp.state == SettingBtnState::MOUSE_OVER)
			{
				BtnMouseClick(volumeUp);
			}
			else if (volumeUp.state == SettingBtnState::MOUSE_CLICK)
			{
				// ���콺 ���� ��ư�� ����
				if (INPUT->KeyUp(VK_LBUTTON))
				{
					// ��ü������ �÷��ݴϴ�
					App.soundScale = clamp(App.soundScale + 0.1f, 0.0f, 1.0f);
					SOUND->SetMasterVolume();
					SOUND->Play(UI_CLICK);
				}
			}
		}
		//���� ���̱� ��ư ���콺 �����϶�
		if (volumeDown.button->MouseOver())
		{
			if (volumeDown.state == SettingBtnState::NONE)
			{
				BtnMouseOver(volumeDown);
			}
			else if (volumeDown.state == SettingBtnState::MOUSE_OVER)
			{
				BtnMouseClick(volumeDown);
			}
			else if (volumeDown.state == SettingBtnState::MOUSE_CLICK)
			{
				// ���콺 ���� ��ư�� ����
				if (INPUT->KeyUp(VK_LBUTTON))
				{
					// ��ü������ �ٿ��ݴϴ�
					App.soundScale = clamp(App.soundScale - 0.1f, 0.0f, 1.0f);
					SOUND->SetMasterVolume();
					SOUND->Play(UI_CLICK);
				}
			}
		}

		//���� ��ü �ѱ� ����
		if (turnAndOffvolume.button->MouseOver())
		{
			if (turnAndOffvolume.state == SettingBtnState::NONE)
			{
				BtnMouseOver(turnAndOffvolume);
			}
			else if (turnAndOffvolume.state == SettingBtnState::MOUSE_OVER)
			{
				BtnMouseClick(turnAndOffvolume);
			}
			else if (turnAndOffvolume.state == SettingBtnState::MOUSE_CLICK)
			{
				// ���콺 ���� ��ư�� ����
				if (INPUT->KeyUp(VK_LBUTTON))
				{
					//������ Ű�� ���ϴ�
					volumeOn = !volumeOn;
					OnOffMasterVolume(volumeOn);
					SOUND->Play(UI_CLICK);
				}
			}
		}
	}

}

void Setting::Render()
{
	if (isOpen)
	{
		settingPanel->Render();
		//======================================
		//���� ������ ������ ����
		{
			//�ʱ���� �Ǵ� �Ҹ��� Ŭ�� 3���ٺ���
			if (App.soundScale > 0.6)
			{
				volumeIcon->Find("volumeStick0")->visible = true;
				volumeIcon->Find("volumeStick1")->visible = true;
				volumeIcon->Find("volumeStick2")->visible = true;
				volumeIcon->Update();
			}
			// 1���� ���̱� �Ҹ��� �����̶� ����������
			else if (App.soundScale > 0.0f and App.soundScale < 0.3f)
			{
				volumeIcon->Find("volumeStick0")->visible = true;
				volumeIcon->Find("volumeStick1")->visible = false;
				volumeIcon->Find("volumeStick2")->visible = false;
				volumeIcon->Update();
			}
			//2���� ���϶� �߰����� �Ҹ�
			else if (App.soundScale > 0.3f and App.soundScale < 0.6f)
			{
				volumeIcon->Find("volumeStick0")->visible = true;
				volumeIcon->Find("volumeStick1")->visible = true;
				volumeIcon->Find("volumeStick2")->visible = false;
				volumeIcon->Update();
			}
			// �Ҹ��� ���Ұ� �����϶� �پȺ���
			else if (App.soundScale == 0.0f)
			{
				volumeIcon->Find("volumeStick0")->visible = false;
				volumeIcon->Find("volumeStick1")->visible = false;
				volumeIcon->Find("volumeStick2")->visible = false;
				volumeIcon->Update();
			}
		}
		volumeIcon->Render();
	}



}

void Setting::BtnInitalize(SettingBtn& settingBtn)
{
	settingBtn.button->scale = btnScale;
}

void Setting::BtnMouseOver(SettingBtn& settingBtn)
{
	//��ư ���¸� ���콺������ ����
	settingBtn.state = SettingBtnState::MOUSE_OVER;
}

void Setting::BtnMouseClick(SettingBtn& settingBtn)
{
	// ���콺 ���� ��ư�� ������
	if (INPUT->KeyDown(VK_LBUTTON))
	{
		// ��ŸƮ��ư ���¸� ���콺 Ŭ������ ����
		settingBtn.state = SettingBtnState::MOUSE_CLICK;
	}
}

void Setting::OnOffMasterVolume(bool OnAndOff)
{
	if (OnAndOff)
	{
		//�Ҹ��� ���������� ���ݴϴ�
		App.soundScale = 0.0f;
		SOUND->SetMasterVolume();
	}
	else if (!OnAndOff)
	{
		//�Ҹ��� ���������� �⺻�������� �ٲ��ݴϴ�
		App.soundScale = 1.0f;
		SOUND->SetMasterVolume();
	}
}

void Setting::OpenSetting()
{
	isOpen = true;
	settingPanel->visible = true;
	volumeIcon->visible = true;
}
