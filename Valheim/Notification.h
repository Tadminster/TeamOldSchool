#pragma once
class Notification
{
private:
	UI* notificationUI;		// �˸� UI
	UI* panel;				// �˸� ����� ����ų ������
	UI* icon;				// ������ �������� ����ų ������
	RECT subject;			// ���� �ڽ�(����)
	RECT itemName;			// ���� �ڽ�(������ �̸�)
	//==================================================================================================
	Item	item;				// �˸��� ǥ���� ������
	float	duration{ 0.0f };	// �˸��� ǥ�õǴ� �ð�

public:
	explicit Notification(Item item);
	~Notification();

	void Init();
	void Release();
	void Update();
	void LateUpdate();
	void PreRender();
	void Render();
	void ResizeScreen();
};

