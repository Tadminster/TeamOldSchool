#pragma once
#include "../2DFrameWork/framework.h"
#pragma comment (lib,"../Build/2DFrameWork/2DFrameWork.lib")

//싱글턴화를 위한 헤더, 매크로
#include "GameManager.h"

#include "Prototype.h"
#include "Unit.h"
#include "Player.h"
#include "Elder.h"
#include "MiniMap.h"
#include "ObjectManager.h"
#include "ParticleManager.h"
#include "Setting.h"

#include "UserInterfaceManager.h"
#include "Inventory.h"
#include "Craft.h"
#include "Recipe.h"
#include "Status.h"



#define PARTICLE    ParticleManager::GetInstance()
#define SETTING     Setting::GetInstance()
#define GM			GameManager::GetInstance()
#define RECIPE		GM->recipe
#define OBJ			GM->objectManager
#define MAP			GM->map
#define SEA			GM->ocean
#define PLAYER		GM->player
#define ELDER		GM->elder
#define MONSTER		GM->monster
#define UIM			GM->uiManager
#define ASTAR		GM->astar
#define INVEN		UIM->inventory
#define CRAFT		UIM->craft
#define STATUS		UIM->status
#define MINIMAP		UIM->minimap