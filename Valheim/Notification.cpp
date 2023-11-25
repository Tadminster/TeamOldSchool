#include "stdafx.h"
#include "Notification.h"

Notification::Notification(Item item)
{
	notificationUI = UI::Create("UI_Notification");
	notificationUI->LoadFile("UI_Notification.xml");

	panel = static_cast<UI*>(notificationUI->Find("0_BackGround"));
	icon = static_cast<UI*>(notificationUI->Find("1_Icon"));

	this->item = item;

	Init();
}

Notification::~Notification()
{
	panel = nullptr;
	icon = nullptr;

	notificationUI->Release();
}

void Notification::Init()
{
	string iconFileName = CRAFT->GetIconFileName(item);
	CRAFT->IconChanger(icon, iconFileName);
}

void Notification::Release()
{
}

void Notification::Update()
{
	duration += DELTA;

	if (duration >= 3.0f)
	{
		Notification::~Notification();
	}

	notificationUI->Update();
}

void Notification::LateUpdate()
{
}

void Notification::PreRender()
{
}

void Notification::Render()
{
	notificationUI->Render();

	float appHalfWidth = App.GetHalfWidth();
	float appHalfHeight = App.GetHalfHeight();

	// 알림 창 크기 계산 (가로세로 절반크기, Pivot이 중앙이므로)
	Vector2 notiSize{
		appHalfWidth * panel->S._11,
		appHalfHeight* panel->S._22 };

	// 디테일 창 위치 계산
	Vector2 Baseline{
		appHalfWidth * (panel->GetWorldPos().x + 1.0f),
		appHalfHeight * (1.0f - panel->GetWorldPos().y) };

	// 텍스트 위치 설정
	subject.left = Baseline.x - notiSize.x * 0.8f;
	subject.right = subject.left + 1000;
	subject.top = Baseline.y - notiSize.y * 0.85f;
	subject.bottom = subject.top + 200;

	// 설명
	itemName.left = Baseline.x - notiSize.x * 0.8f;
	itemName.right = itemName.left + 1000;
	itemName.top = Baseline.y - notiSize.y * 0.85f;
	itemName.bottom = itemName.top + 1000;

	DWRITE->RenderText(
		L"ㅁㅁㅁㅁ",
		subject,
		20.0f,
		L"Arial",
		Color(0.0f, 0.7f, 1.0f, 0.0f),
		DWRITE_FONT_WEIGHT_SEMI_BOLD,
		DWRITE_FONT_STYLE_ITALIC,
		DWRITE_FONT_STRETCH_EXPANDED);

	DWRITE->RenderText(
		L"ㅇㅇㅇㅇㅇ",
		itemName,
		20.0f,
		L"Arial",
		Color(0.0f, 0.7f, 1.0f, 0.0f),
		DWRITE_FONT_WEIGHT_SEMI_BOLD,
		DWRITE_FONT_STYLE_ITALIC,
		DWRITE_FONT_STRETCH_EXPANDED);
}

void Notification::ResizeScreen()
{
}