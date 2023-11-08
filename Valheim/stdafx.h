#pragma once
#include "../2DFrameWork/framework.h"
#pragma comment (lib,"../Build/2DFrameWork/2DFrameWork.lib")

//싱글턴화를 위한 헤더, 매크로
#include "GameManager.h"
#include "Prototype.h"
#include "Player.h"

#include "ObjectManager.h"

#define GM		GameManager::GetInstance()
#define OBJ		GM->objectManager
#define DEBUG	GM->debugMode
#define MAP		GM->map
#define PLAYER	GM->player