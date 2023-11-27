#pragma once
#define TIME_LIMIT 5.0f 	// �˸��� ����� �ð�

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
	float		lifeTime{ 0.0f };	// �˸��� ǥ�õ� �ð�

public:
	explicit Notification(Item item, NotificationType type);
	~Notification();

	void Update();
	void Render();
	void Release();

	UI* GetNotificationUI() { return notificationUI; }

	wstring SetTextSubject(NotificationType type);
	wstring SetTextItemName(Item item);

	bool IsTimeOver() { return lifeTime >= TIME_LIMIT; }
};

