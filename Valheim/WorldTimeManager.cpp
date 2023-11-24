#include "stdafx.h"

WorldTimeManager::WorldTimeManager()
{
	worldTime = new Timer();
}

WorldTimeManager::~WorldTimeManager()
{
	delete worldTime;
}


