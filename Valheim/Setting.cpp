#include "stdafx.h"
#include "Setting.h"

Setting::Setting()
{
	settingPanel = UI::Create("SettingPanel");
	settingPanel->LoadFile("UI_SettingPanel.xml");

	volumeUp.button = static_cast<UI*>(settingPanel->Find("volumeUp"));
	volumeDown.button = static_cast<UI*>(settingPanel->Find("volumeDown"));
	turnAndOffvolume.button = static_cast<UI*>(settingPanel->Find("turnAndOffvolume"));

}

Setting::~Setting()
{

}

void Setting::Init()
{
	settingPanel->visible = false;

	BtnInitalize(volumeUp);
	BtnInitalize(volumeDown);
	BtnInitalize(turnAndOffvolume);

}

void Setting::Release()
{
	settingPanel->Release();
}

void Setting::Update()
{
	ImGui::Begin("UI Hierarchy");
	{
		settingPanel->RenderHierarchy();
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
				settingPanel->visible = !settingPanel->visible;
			}
		}
	}

	settingPanel->Update();
}

void Setting::LateUpdate()
{
	//����â	�г����� ���콺�� �ö� ������ 
	//��ư���� ����üũ
	if (settingPanel->visible and settingPanel->MouseOver())
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
					App.soundScale += 0.1f;
					SOUND->SetMasterVolume();
					SOUND->Play(INVENTORY_ITEM_PICK);
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
					App.soundScale -= 0.1f;
					SOUND->SetMasterVolume();
					SOUND->Play(INVENTORY_ITEM_PICK);
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
					SOUND->Play(INVENTORY_ITEM_PICK);
				}
			}
		}
	}
}

void Setting::Render()
{

	settingPanel->Render();
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
	else
	{
		//�Ҹ��� ���������� �⺻�������� �ٲ��ݴϴ�
		App.soundScale = 0.5f;
		SOUND->SetMasterVolume();
	}
}
