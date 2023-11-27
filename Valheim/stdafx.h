#pragma once
#include "../2DFrameWork/framework.h"
#pragma comment (lib,"../Build/2DFrameWork/2DFrameWork.lib")

//싱글턴화를 위한 헤더, 매크로
#include "GameManager.h"

#include "Prototype.h"
#include "Unit.h"
#include "Player.h"
#include "MiniMap.h"
#include "ObjectManager.h"
#include "ParticleManager.h"

#include "UserInterfaceManager.h"
#include "Inventory.h"
#include "Craft.h"
#include "Recipe.h"



#define GM			GameManager::GetInstance()
#define RECIPE		GM->recipe
#define OBJ			GM->objectManager
#define PARTICLE    GM->particleManager
#define MAP			GM->map
#define SEA			GM->sea
#define PLAYER		GM->player
#define UIM			GM->uiManager
#define INVEN		UIM->inventory
#define CRAFT		UIM->craft
#define MINIMAP		UIM->minimap