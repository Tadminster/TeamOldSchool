#include "stdafx.h"
#include "Notification.h"

Notification::Notification(Item item, NotificationType type)
{
	notificationUI = UI::Create("UI_Notification");
	notificationUI->LoadFile("UI_Notification.xml");
	//notificationUI->SetWorldPos();

	panel = static_cast<UI*>(notificationUI->Find("0_BackGround"));
	icon = static_cast<UI*>(notificationUI->Find("1_Icon"));

	// 텍스트 설정
	textSubject = SetTextSubject(type);
	textItemName = SetTextItemName(item);

	// 습득/해금한 아이템 아이콘 설정
	string iconFileName = CRAFT->GetIconFileName(item);
	CRAFT->IconChanger(icon, iconFileName);
}

Notification::~Notification()
{

}

void Notification::Update()
{
	ImGui::Begin("UI Hierarchy");
	{
		notificationUI->RenderHierarchy();
	}
	ImGui::End();
	
	lifeTime += DELTA;

	notificationUI->Update();
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
	rectSubject.left = Baseline.x - notiSize.x * 0.74f;
	rectSubject.right = rectSubject.left + 1000;
	rectSubject.top = Baseline.y - notiSize.y * 0.85f;
	rectSubject.bottom = rectSubject.top + 200;

	// 설명
	rectItemName.left = Baseline.x - notiSize.x * 0.1f;
	rectItemName.right = rectItemName.left + 1000;
	rectItemName.top = Baseline.y;
	rectItemName.bottom = rectItemName.top + 1000;

	DWRITE->RenderText(
		textSubject,
		rectSubject,
		20.0f,
		L"Arial",
		Color(1.0f, 0.7f, 0.0f, 0.0f),
		DWRITE_FONT_WEIGHT_SEMI_BOLD,
		DWRITE_FONT_STYLE_ITALIC,
		DWRITE_FONT_STRETCH_EXPANDED);

	DWRITE->RenderText(
		textItemName,
		rectItemName,
		20.0f,
		L"Arial",
		Color(1.0f, 1.0f, 1.0f, 0.0f),
		DWRITE_FONT_WEIGHT_SEMI_BOLD,
		DWRITE_FONT_STYLE_ITALIC,
		DWRITE_FONT_STRETCH_EXPANDED);
}

void Notification::Release()
{
	panel = nullptr;
	icon = nullptr;

	notificationUI->Release();

	delete this;
}

wstring Notification::SetTextSubject(NotificationType type)
{
	switch (type)
	{
		case NotificationType::Discovery:	return textSubject = L"새로운 아이템 발견";
		case NotificationType::Unlock:		return textSubject = L"새로운 레시피 해금";
	}
}

wstring Notification::SetTextItemName(Item item)
{
	switch (item)
	{
		case Item::Club:			return textItemName = L"몽둥이"; 
		case Item::StoneAxe:		return textItemName = L"돌 도끼";  
		case Item::StonePickaxe:	return textItemName = L"돌 곡괭이";
		case Item::FineAxe:			return textItemName = L"고급 도끼";
		case Item::WoodShield:		return textItemName = L"나무 방패";
		case Item::Woodpile:		return textItemName = L"나무";
		case Item::FineWood:		return textItemName = L"고급 나무";
		case Item::Stone:			return textItemName = L"돌";
		case Item::Leather:			return textItemName = L"가죽";
		case Item::ElderTrophy:		return textItemName = L"엘더 트로피";
		default:					return textItemName = L"null";
	}
}
