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

	//패널 열기 닫기
	if (INPUT->KeyDown(VK_F8))
	{
		settingPanel->visible = !settingPanel->visible;

	}




	settingPanel->Update();
}

void Setting::LateUpdate()
{
	//설정창	패널위에 마우스가 올라가 있으면 
	//버튼들의 상태체크
	if (settingPanel->visible and settingPanel->MouseOver())
	{
		//볼륨 키우기 버튼 마우스 오버일때
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
				// 마우스 왼쪽 버튼을 떼면
				if (INPUT->KeyUp(VK_LBUTTON))
				{
					// 전체볼륨을 올려줍니다
					App.soundScale += 0.1f;
					SOUND->SetMasterVolume();
				}
			}
		}

		//볼륨 줄이기 버튼 마우스 오버일때
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
				// 마우스 왼쪽 버튼을 떼면
				if (INPUT->KeyUp(VK_LBUTTON))
				{
					// 전체볼륨을 줄여줍니다
					App.soundScale -= 0.1f;
					SOUND->SetMasterVolume();
				}
			}
		}

		//볼륨 전체 켜기 끄기
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
				// 마우스 왼쪽 버튼을 떼면
				if (INPUT->KeyUp(VK_LBUTTON))
				{
					//볼륨을 키고 끕니다
					volumeOn = !volumeOn;
					OnOffMasterVolume(volumeOn);
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
	//버튼 상태를 마우스오버로 변경
	settingBtn.state = SettingBtnState::MOUSE_OVER;
}

void Setting::BtnMouseClick(SettingBtn& settingBtn)
{
	// 마우스 왼쪽 버튼을 누르면
	if (INPUT->KeyDown(VK_LBUTTON))
	{
		// 스타트버튼 상태를 마우스 클릭으로 변경
		settingBtn.state = SettingBtnState::MOUSE_CLICK;
	}
}

void Setting::OnOffMasterVolume(bool OnAndOff)
{
	if (OnAndOff)
	{
		//소리가 켜져있을땐 꺼줍니다
		App.soundScale = 0.0f;
		SOUND->SetMasterVolume();
	}
	else
	{
		//소리가 꺼져있을땐 기본볼륨으로 바꿔줍니다
		App.soundScale = 0.5f;
		SOUND->SetMasterVolume();
	}
}
