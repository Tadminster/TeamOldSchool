#include "stdafx.h"
#include "Item.h"
#include "ConsumeItem.h"

ConsumeItem::ConsumeItem()
	: Item()
{
	itemDurationTime = 0;
	itemHealthPoint = 0;
	itemStaminaPoint = 0;
}

ConsumeItem::~ConsumeItem()
{
}

void ConsumeItem::CreateItem()
{
}

void ConsumeItem::EquipItem()
{
}

void ConsumeItem::DestroyItem()
{
}

void ConsumeItem::FixItem()
{
}
