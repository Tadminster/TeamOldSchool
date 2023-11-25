#pragma once
class Notification
{
private:
	UI* notificationUI;		// 알림 UI
	UI* panel;				// 알림 배경을 가리킬 포인터
	UI* icon;				// 아이템 아이콘을 가리킬 포인터
	RECT subject;			// 툴팁 박스(제목)
	RECT itemName;			// 툴팁 박스(아이템 이름)
	//==================================================================================================
	Item	item;				// 알림에 표시할 아이템
	float	duration{ 0.0f };	// 알림이 표시되는 시간

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

