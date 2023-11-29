#include "stdafx.h"
#include <list>

//#include "Prototype.h"
// 지형지물(나무, 돌) ===============================================
#include "FeatureProto.h"
#include "Birch.h"
#include "Beech.h"
#include "BeechLog.h"
#include "BeechHalfLog.h"
#include "Grass.h"
// 아이템 =============================================================
#include "ItemProto.h"
//#include "Woodpile.h"
//#include "Stone.h"
//#include "StoneAxe.h"

// 건축구조물 ========================================================
#include "StructureProto.h"
// 유닛 ===============================================================
#include "Elder.h"

#include "ObjectManager.h"

ObjectManager::ObjectManager()
{
	// 테스트용 임시 아이템 생성
	{
		for (auto& item : stoneAxe)
		{
			item = ItemProto::Create(Item::StoneAxe);
			item->GetActor()->SetWorldPos(Vector3(RANDOM->Int(0, 10), 50, RANDOM->Int(0, 10)));
			AddItem(item);
		}

		for (auto& item : woodpile)
		{
			item = ItemProto::Create(Item::Woodpile);
			item->GetActor()->SetWorldPos(Vector3(RANDOM->Int(0, 10), 50, RANDOM->Int(0, 10)));
			AddItem(item);
		}

		for (auto& item : stone)
		{
			item = ItemProto::Create(Item::Stone);
			item->GetActor()->SetWorldPos(Vector3(RANDOM->Int(0, 10), 50, RANDOM->Int(0, 10)));
			AddItem(item);
		}

		for (auto& item : woodShield)
		{
			item = ItemProto::Create(Item::WoodShield);
			item->GetActor()->SetWorldPos(Vector3(RANDOM->Int(0, 10), 50, RANDOM->Int(0, 10)));
			AddItem(item);
		}

		for (auto& item : leather)
		{
			item = ItemProto::Create(Item::Leather);
			item->GetActor()->SetWorldPos(Vector3(RANDOM->Int(0, 10), 50, RANDOM->Int(0, 10)));
			AddItem(item);
		}
	}
}

ObjectManager::~ObjectManager()
{

}

void ObjectManager::Init()
{
}

void ObjectManager::Release()
{
	if (objects.empty()) return;

	for (auto& obj : objects)
	{
		obj->Release();
	}
	objects.clear();
}

void ObjectManager::Update()
{
	if (ImGui::Button("Generate PerinNoiseMap"))
	{
		Release();
		MAP->PerlinNoiseHeightMap();
	}
	if (ImGui::Button("Generate Tree"))
	{
		Release();
		GenerateTree();
	}
	if (ImGui::Button("Generate Instancing Tree"))
	{
		GenerateInstanceTree();
	}
	if (ImGui::Button("Generate Instance Grass"))
	{
		GenerateInstanceGrass();
	}

	ListEraser(objects);
	ListEraser(items);
	ListEraser(structures);

	// 오브젝트 업데이트
	{
		for (auto& obj : objects)
		{
			obj->Update();
		}
	}

	// 인스턴싱 오브젝트 업데이트
	for (auto& instance : instancingObjects)
	{
		instance->Update();
	}

	// 아이템 업데이트
	for (auto& item : items)
		item->Update();
}

void ObjectManager::LateUpdate()
{
	for (auto& item : items)
		item->LateUpdate();

	// 아이템 줍기(임시)
	for (auto& item : items)
	{
		if (PLAYER->GetItem(item)) break;
	}
}

void ObjectManager::Render()
{
	// 인스턴싱 오브젝트 렌더링
	for (auto& instance : instancingObjects)
	{
		instance->Render();
	}

	// 디버그 모드일 때
	if (DEBUGMODE)
	{
		// 모든 오브젝트 렌더링
		for (auto& obj : objects)
		{
			obj->Render();
		}
	}
	// 디버그 모드가 아닐 때
	else
	{
		Vector3 CameraPos = Camera::main->GetWorldPos();
		for (auto& obj : objects)
		{
			float distance = Vector3::DistanceSquared(CameraPos, obj->GetActor()->GetWorldPos());
			if (distance > 2500) continue;

			// 카메라와 충돌하는 오브젝트만 렌더링
			if (PLAYER->GetFrustumCam()->Intersect(obj->GetActor()->GetWorldPos()))
			{
				obj->Render();
			}
		}
	}

	// 아이템 렌더링
	for (auto& item : items)
		item->Render();
}

void ObjectManager::RefractionRender()
{
	Vector3 CameraPos = Camera::main->GetWorldPos();
	for (auto& obj : objects)
	{
		float distance = Vector3::DistanceSquared(CameraPos, obj->GetActor()->GetWorldPos());
		if (distance < 2000) obj->GetActor()->Render(RESOURCE->shaders.Load("4.Instance_Water.hlsl"));
	}
}

void ObjectManager::RenderHierarchy()
{
	// 오브젝트 매니저 전용 하이어라이키
	ImGui::Begin("TerrainHierarchy");
	{
		for (auto& obj : objects)
		{
			obj->GetActor()->RenderHierarchy();
		}
		for (auto& objInstancing : instancingObjects)
		{
			objInstancing->GetActor()->RenderHierarchy();
		}
	}
	ImGui::End();
}

void ObjectManager::GenerateTree()
{
	int rowSize = MAP->rowSize;
	double frequencyScale = 1.0 / rowSize * 2;			// 맵 크기에 따른 주파수 스케일 조정
	siv::PerlinNoise perlin(RANDOM->Int(0, 10000));		// 난수 시드로 펄린노이즈 생성

	VertexTerrain* vertices = (VertexTerrain*)MAP->mesh->vertices;		// 맵의 버텍스 받아오기
	Ray ray; Vector3 Hit;					// 레이와 레이가 맞은 지점을 저장할 변수
	ray.position = Vector3();				// 레이 포지션 초기화(임시)
	ray.direction = Vector3(0, -1, 0);		// 레이 방향(위에서 수직으로 내리꽂는 레이)

	// 맵의 rowSize * rowSize 만큼 반복
	for (int i = 0; i < rowSize; i++)
	{
		for (int j = 0; j < rowSize; j++)
		{
			int index = i * rowSize + j;					// 인덱스 계산
			float positionY = vertices[index].position.y;	// 높이값 받아오기

			// 높이체크
			// 높이가 -1 이하 인곳에서는 생성하지 않음
			if (positionY < -1.0f)
			{
				continue;
			}
			// 높이가 -1 ~ 1 이면, 100분의 1 확률로 생성
			else if (positionY < 0.0f)
			{
				if (RANDOM->Int(1, 100) != 1)
				{
					continue;
				}
			}
			// 높이가 1 ~ 3 이면, 80분의 1 확률로 생성
			else if (positionY < 3.0f)
			{
				if (RANDOM->Int(1, 80) != 1)
				{
					continue;
				}
			}
			// 높이가 3 ~ 5 이면, 70분의 1 확률로 생성
			else if (positionY < 5.0f)
			{
				if (RANDOM->Int(1, 70) != 1)
				{
					continue;
				}
			}
			// 높이가 5 ~ 7 이면, 60분의 1 확률로 생성
			else if (positionY < 7.0f)
			{
				if (RANDOM->Int(1, 60) != 1)
				{
					continue;
				}
			}
			// 높이가 7 ~ 10 이면, 50분의 1 확률로 생성
			else if (positionY < 10.0f)
			{
				if (RANDOM->Int(1, 50) != 1)
				{
					continue;
				}
			}
			else // 높이가 10 이상이면, 40분의 1 확률로 생성
			{
				if (RANDOM->Int(1, 40) != 1)
				{
					continue;
				}
			}
			double x = (double)i * frequencyScale;
			double y = (double)j * frequencyScale;
			double z = 0.5;
			double noiseValue = perlin.noise3D(x, y, z);

			// 펄린노이즈 값이 0.2 이상이거나, 50분의 1 확률로 생성
			if (noiseValue > -0.2f/* || RANDOM->Int(1, 50) == 1*/)
			{
				// 레이의 위치 설정
				ray.position = vertices[index].position; + Vector3(0, 1000, 0);	

				// Compute Picking으로 레이와 맞은 지점을 Hit에 저장
				if (MAP->ComputePicking(ray, Hit))
				{
					FeatureProto* feature;
					
					if (RANDOM->Int(1, 10) == 1)
					{
						feature = FeatureProto::Create(FeatureType::Rock);
					}
					else
					{
						if (RANDOM->Int(1, 10) == 1)
							feature = FeatureProto::Create(FeatureType::Birch);
						else
							feature = FeatureProto::Create(FeatureType::Beech);
					}

					// 오브젝트 위치 설정
					feature->GetActor()->SetWorldPos(Hit);

					// 생성된 오브젝트 리스트에 추가
					objects.emplace_back(feature);
				}
			}
		}
	}

	// 생성된 오브젝트들 업데이트
	for (auto& obj : objects)
	{
		obj->Update();
	}
}


void ObjectManager::GenerateInstanceTree()
{
	int rowSize = MAP->rowSize;
	double frequencyScale = 1.0 / rowSize * 2;			// 맵 크기에 따른 주파수 스케일 조정
	siv::PerlinNoise perlin(RANDOM->Int(0, 10000));		// 난수 시드로 펄린노이즈 생성

	vector<Vector3> treePos;							// 인스턴스 나무 위치 저장할 벡터

	VertexTerrain* vertices = (VertexTerrain*)MAP->mesh->vertices;
	Ray ray; Vector3 Hit;
	ray.position = Vector3();
	ray.direction = Vector3(0, -1, 0);

	for (int i = 0; i < rowSize; i++)
	{
		for (int j = 0; j < rowSize; j++)
		{
			float positionY = vertices[i * rowSize + j].position.y;

			// 높이체크
			// 높이가 -1 이하 인곳에서는 생성하지 않음
			if (positionY < -1.0f) continue;
			// 높이가 -1 ~ 1 이면, 50분의 1 확률로 생성
			else if (positionY < 1.0f)
			{
				if (RANDOM->Int(1, 50) != 1) continue;
			}
			// 높이가 1 ~ 10 이면, 30분의 1 확률로 생성
			else if (positionY < 10.0f)
			{
				if (RANDOM->Int(1, 30) != 1) continue;
			}
			else // 높이가 10 이상이면, 20분의 1 확률로 생성
			{
				if (RANDOM->Int(1, 20) != 1) continue;
			}

			double x = (double)i * frequencyScale;
			double y = (double)j * frequencyScale;
			double z = 0.5;
			double noiseValue = perlin.noise3D(x, y, z);

			// 펄린노이즈 값 체크
			if (noiseValue > -0.2f)
			{
				ray.position = vertices[i * rowSize + j].position; + Vector3(0, 1000, 0);

				if (MAP->ComputePicking(ray, Hit))
				{
					treePos.emplace_back(Hit);
				}
			}
		}
	}

	FeatureProto* beech = FeatureProto::Create(FeatureType::BeechInstancing);
	beech->GetActor()->SetWorldPos(Vector3(0.0f, -50.0f, 0.0f));
	beech->Update();
	float baseline = fabs(beech->GetActor()->GetWorldPos().y);

	UINT count = treePos.size();
	Matrix* ins = new Matrix[count];
	for (int i = 0; i < count; i++)
	{
		Vector3 insPos = Vector3(treePos[i].x, treePos[i].y + baseline, treePos[i].z);
		ins[i] = Matrix::CreateTranslation(insPos);
		ins[i] = ins[i].Transpose();
	}

	beech->GetActor()->Find("Lod0")->mesh->CreateInstanceBuffer(ins, count);
	beech->GetActor()->Find("Lod0MeshObject1")->mesh->CreateInstanceBuffer(ins, count);
	//beech->GetActor()->Find("Lod1")->mesh->CreateInstanceBuffer(ins, count);
	//beech->GetActor()->Find("Lod1MeshObject1")->mesh->CreateInstanceBuffer(ins, count);
	//beech->GetActor()->Find("Lod3")->mesh->CreateInstanceBuffer(ins, count);
	//beech->GetActor()->Find("Lod3MeshObject1")->mesh->CreateInstanceBuffer(ins, count);

	instancingObjects.emplace_back(beech);
}


void ObjectManager::GenerateInstanceGrass()
{
	int rowSize = MAP->rowSize;
	double frequencyScale = 1.0 / rowSize * 2;			// 맵 크기에 따른 주파수 스케일 조정
	siv::PerlinNoise perlin(RANDOM->Int(0, 10000));		// 난수 시드로 펄린노이즈 생성

	vector<Vector3> grassPos;							// 인스턴스 나무 위치 저장할 벡터

	VertexTerrain* vertices = (VertexTerrain*)MAP->mesh->vertices;
	Ray ray; Vector3 Hit;
	ray.position = Vector3();
	ray.direction = Vector3(0, -1, 0);

	for (int i = 0; i < rowSize; i++)
	{
		for (int j = 0; j < rowSize; j++)
		{
			float positionY = vertices[i * rowSize + j].position.y;

			// 높이체크
			// 높이가 -1 이하 인곳에서는 생성하지 않음
			if (positionY < -1.0f) continue;
			// 높이가 -1 ~ 1 이면, 20분의 1 확률로 생성
			else if (positionY < 1.0f)
			{
				if (RANDOM->Int(1, 20) != 1) continue;
			}
			else // 높이가 1 이상 이면, 20분의 1 확률로 생성
			{
				if (RANDOM->Int(1, 5) != 1) continue;
			}

			double x = (double)i * frequencyScale;
			double y = (double)j * frequencyScale;
			double z = 0.5;
			double noiseValue = perlin.noise3D(x, y, z);

			// 펄린노이즈 값 체크
			if (noiseValue > -0.2f)
			{
				ray.position = vertices[i * rowSize + j].position; +Vector3(0, 1000, 0);

				if (MAP->ComputePicking(ray, Hit))
				{
					grassPos.emplace_back(Hit);
				}
			}
		}
	}

	Grass* grass = new Grass(Vector3(0, 0, 0));

	UINT count = grassPos.size();
	cout << "Grass " << count << "개 생성!" << endl;
	Matrix* ins = new Matrix[count];
	int idx = 0;
	for (int i = 1; i < count; i++)
	{
		Vector3 insPos = Vector3(grassPos[i].x, grassPos[i].y, grassPos[i].z);
		ins[idx] = Matrix::CreateTranslation(insPos);
		ins[idx] = ins[idx].Transpose();
		idx++;
	}
	grass->GetActor()->Find("grasscross__1_")->mesh->CreateInstanceBuffer(ins, count);
	grass->Update();

	objects.emplace_back(grass);
}

void ObjectManager::AddObject(Prototype* object)
{
	objects.emplace_back(object);
}

void ObjectManager::AddInstancingObject(Prototype* object)
{
	instancingObjects.emplace_back(object);
}

void ObjectManager::AddItem(ItemProto* item)
{
	items.emplace_back(item);
}

list<Collider*> ObjectManager::GetColliders()
{
	
	list<Collider*> colliders;

	for (auto& obj : objects)
	{
		if (obj->GetActor()->collider)
		{
			obj->Update();
			colliders.emplace_back(obj->GetActor()->collider);
		}
	}
	return colliders;
	
}
