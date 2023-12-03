#include "stdafx.h"
#include "Notification.h"

Notification::Notification(Item item, NotificationType type)
{
	notificationUI = UI::Create("UI_Notification");
	notificationUI->LoadFile("UI_Notification.xml");
	//notificationUI->SetWorldPos();

	panel = static_cast<UI*>(notificationUI->Find("0_BackGround"));
	icon = static_cast<UI*>(notificationUI->Find("1_Icon"));

	// �ؽ�Ʈ ����
	textSubject = SetTextSubject(type);
	textItemName = SetTextItemName(item);

	// ����/�ر��� ������ ������ ����
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

	// �˸� â ũ�� ��� (���μ��� ����ũ��, Pivot�� �߾��̹Ƿ�)
	Vector2 notiSize{
		appHalfWidth * panel->S._11,
		appHalfHeight* panel->S._22 };

	// ������ â ��ġ ���
	Vector2 Baseline{
		appHalfWidth * (panel->GetWorldPos().x + 1.0f),
		appHalfHeight * (1.0f - panel->GetWorldPos().y) };

	// �ؽ�Ʈ ��ġ ����
	rectSubject.left = Baseline.x - notiSize.x * 0.74f;
	rectSubject.right = rectSubject.left + 1000;
	rectSubject.top = Baseline.y - notiSize.y * 0.85f;
	rectSubject.bottom = rectSubject.top + 200;

	// ����
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
		case NotificationType::Discovery:	return textSubject = L"���ο� ������ �߰�";
		case NotificationType::Unlock:		return textSubject = L"���ο� ������ �ر�";
	}
}

wstring Notification::SetTextItemName(Item item)
{
	switch (item)
	{
		case Item::Club:			return textItemName = L"������"; 
		case Item::StoneAxe:		return textItemName = L"�� ����";  
		case Item::StonePickaxe:	return textItemName = L"�� ���";
		case Item::FineAxe:			return textItemName = L"��� ����";
		case Item::WoodShield:		return textItemName = L"���� ����";
		case Item::Woodpile:		return textItemName = L"����";
		case Item::FineWood:		return textItemName = L"��� ����";
		case Item::Stone:			return textItemName = L"��";
		case Item::Leather:			return textItemName = L"����";
		case Item::ElderTrophy:		return textItemName = L"���� Ʈ����";
		default:					return textItemName = L"null";
	}
}
