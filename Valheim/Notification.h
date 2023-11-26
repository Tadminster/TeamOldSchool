#pragma once
#define DURATION_LIMIT 5.0f 	// �˸��� ����� �ð�

enum class NotificationType
{
	Discovery, Unlock,
};

class Notification
{
private:
	UI*			notificationUI;		// �˸� UI
	UI*			panel;				// �˸� ����� ����ų ������
	UI*			icon;				// ������ �������� ����ų ������
	//==================================================================================================
	wstring		textSubject;		// �˸� ����(����)
	wstring		textItemName;		// ������ �̸�
	RECT		rectSubject;		// textSubject ����
	RECT		rectItemName;		// textItemName ����
	//==================================================================================================
	float		duration{ 0.0f };	// �˸��� ǥ�õ� �ð�

public:
	explicit Notification(Item item, NotificationType type);
	~Notification();

	void Init();
	void Release();
	void Update();
	void LateUpdate();
	void PreRender();
	void Render();
	void ResizeScreen();

	UI* GetNotificationUI() { return notificationUI; }

	wstring SetTextSubject(NotificationType type);
	wstring SetTextItemName(Item item);

	bool IsTimeOver() { return duration >= DURATION_LIMIT; }
};

