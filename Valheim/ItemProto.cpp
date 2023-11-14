#include "stdafx.h"
#include "Prototype.h"

#include "StoneAxe.h"
#include "ItemProto.h"

ItemProto* ItemProto::Create(ItemName name)
{
	switch (name)
	{
	case ItemName::StoneAxe:
		return new StoneAxe();
	default:
		throw std::invalid_argument("error");
	}
}