#pragma once
#include "../2DFrameWork/framework.h"
#pragma comment (lib,"../Build/2DFrameWork/2DFrameWork.lib")

//�̱���ȭ�� ���� ���, ��ũ��
#include "GameManager.h"

#include "Prototype.h"
#include "Unit.h"
#include "Player.h"
#include "Elder.h"
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
#define ELDER		GM->elder
#define MONSTER		GM->monster
#define UIM			GM->uiManager
#define ASTAR		GM->astar
#define INVEN		UIM->inventory
#define CRAFT		UIM->craft
#define MINIMAP		UIM->minimap