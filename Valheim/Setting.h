#pragma once
enum class SettingBtnState { NONE, MOUSE_OVER, MOUSE_CLICK };
struct SettingBtn
{
	UI* button;
	SettingBtnState state{ SettingBtnState::NONE };
};
class Setting : public Singleton<Setting>
{
public:

	//=======================================================
	bool	isOpen		{ false }; //�г��� ���� �ִ��� �Ǻ�
private:
	UI*			settingPanel;
	UI*			volumeIcon;
	//=======================================================
	SettingBtn	volumeUp;			//���� ��
	SettingBtn	volumeDown;			//���� �ٿ�
	SettingBtn	turnAndOffvolume;	//��ü ���� �¿���
	//=======================================================
	Vector3		btnScale{ 0.28f, 0.12f, 0.0f }; //��ư������
	//=======================================================
	string btn1 = "volumeUp";
	string btn2 = "volumeDown";
	string btn3 = "turnAndOffvolume";

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
	void OnOffMasterVolume();
	//========================================
	//
	void OpenSetting();
	void CreatBtnUpdate(SettingBtn& settingBtn, string name);
};

