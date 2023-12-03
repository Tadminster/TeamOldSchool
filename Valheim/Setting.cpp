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

	//패널 열기 닫기
	// 인벤토리, 스탯창 제작창이 열려있지 않고 인게임 씬일때만 ESC 로 설정창 불러오기
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
	//타이틀 씬에서 설정창 켜고 끄기
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

	//설정창	패널위에 마우스가 올라가 있으면 
	//버튼들의 상태체크
	if (isOpen and settingPanel->MouseOver())
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
					App.soundScale = clamp(App.soundScale + 0.1f, 0.0f, 1.0f);
					SOUND->SetMasterVolume();
					SOUND->Play(UI_CLICK);
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
					App.soundScale = clamp(App.soundScale - 0.1f, 0.0f, 1.0f);
					SOUND->SetMasterVolume();
					SOUND->Play(UI_CLICK);
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
		//사운드 아이콘 볼륨바 조절
		{
			//초기사운드 또는 소리가 클때 3개다보임
			if (App.soundScale > 0.6)
			{
				volumeIcon->Find("volumeStick0")->visible = true;
				volumeIcon->Find("volumeStick1")->visible = true;
				volumeIcon->Find("volumeStick2")->visible = true;
				volumeIcon->Update();
			}
			// 1개만 보이기 소리가 조금이라도 켜져있을때
			else if (App.soundScale > 0.0f and App.soundScale < 0.3f)
			{
				volumeIcon->Find("volumeStick0")->visible = true;
				volumeIcon->Find("volumeStick1")->visible = false;
				volumeIcon->Find("volumeStick2")->visible = false;
				volumeIcon->Update();
			}
			//2개만 보일때 중간정도 소리
			else if (App.soundScale > 0.3f and App.soundScale < 0.6f)
			{
				volumeIcon->Find("volumeStick0")->visible = true;
				volumeIcon->Find("volumeStick1")->visible = true;
				volumeIcon->Find("volumeStick2")->visible = false;
				volumeIcon->Update();
			}
			// 소리가 음소거 상태일때 다안보임
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
	else if (!OnAndOff)
	{
		//소리가 꺼져있을땐 기본볼륨으로 바꿔줍니다
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
