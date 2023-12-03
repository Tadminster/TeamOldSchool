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
	bool	mouseOnPanel = false;	//����â �¿��� �Ǻ�
	//=======================================================
	bool	volumeOn	= true;	//��ü���� ������ �������Ǻ�

private:
	UI*			settingPanel;
	//=======================================================
	SettingBtn	volumeUp;			//���� ��
	SettingBtn	volumeDown;			//���� �ٿ�
	SettingBtn	turnAndOffvolume;	//��ü ���� �¿���
	//=======================================================
	Vector3		btnScale{ 0.28f, 0.12f, 0.0f }; //��ư������
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

