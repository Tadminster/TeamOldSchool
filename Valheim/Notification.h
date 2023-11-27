#pragma once
#define TIME_LIMIT 5.0f 	// 알림이 사라질 시간

enum class NotificationType
{
	Discovery, Unlock,
};

class Notification
{
private:
	UI*			notificationUI;		// 알림 UI
	UI*			panel;				// 알림 배경을 가리킬 포인터
	UI*			icon;				// 아이템 아이콘을 가리킬 포인터
	//==================================================================================================
	wstring		textSubject;		// 알림 주제(제목)
	wstring		textItemName;		// 아이템 이름
	RECT		rectSubject;		// textSubject 영역
	RECT		rectItemName;		// textItemName 영역
	//==================================================================================================
	float		lifeTime{ 0.0f };	// 알림이 표시된 시간

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

