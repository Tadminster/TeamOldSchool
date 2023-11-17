#pragma once
#include "../2DFrameWork/framework.h"
#pragma comment (lib,"../Build/2DFrameWork/2DFrameWork.lib")

//싱글턴화를 위한 헤더, 매크로
#include "GameManager.h"
#include "Inventory.h"

#include "Prototype.h"
#include "Player.h"
#include "MiniMap.h"
#include "ObjectManager.h"

#define GM			GameManager::GetInstance()
#define INVEN		GM->inventory
#define OBJ			GM->objectManager
#define DEBUGMODE	GM->debugMode
#define MAP			GM->map
#define SEA			GM->sea
#define PLAYER		GM->player
#define MINIMAP    GM->minimap