#pragma once
enum class SettingBtnState { NONE, MOUSE_OVER, MOUSE_CLICK };
struct SettingBtn
{
	UI* button;
	SettingBtnState state{ SettingBtnState::NONE };
};
class Setting
{
public:
	bool	mouseOnPanel = false;	//설정창 온오프 판별
	//=======================================================
	bool	volumeOn	= true;	//전체볼륨 켜진지 꺼진지판별

private:
	UI*			settingPanel;
	//=======================================================
	SettingBtn	volumeUp;			//볼륨 업
	SettingBtn	volumeDown;			//볼륨 다운
	SettingBtn	turnAndOffvolume;	//전체 볼륨 온오프
	//=======================================================
	Vector3		btnScale{ 0.28f, 0.12f, 0.0f }; //버튼사이즈
	//=======================================================
public:
	Setting();
	~Setting();

	void Init();
	void Release();
	void Update();
	void LateUpdate();
	void Render();
	
	void BtnInitalize(SettingBtn& settingBtn);
	void BtnMouseOver(SettingBtn& settingBtn);
	void BtnMouseClick(SettingBtn& settingBtn);
	void OnOffMasterVolume(bool OnAndOff);
};

