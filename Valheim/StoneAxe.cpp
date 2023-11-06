#include "stdafx.h"
#include "Item.h"
#include "BattleItem.h"
#include "StoneAxe.h"

StoneAxe::StoneAxe()
	: BattleItem()
{
	itemName = "StoneAxe";
	itemDurability = 100;
	itemWeight = 2;

	itemDamage = 10;
	woodAdditionalDamage = 5;

}

StoneAxe::~StoneAxe()
{
}
