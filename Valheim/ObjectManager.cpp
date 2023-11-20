#include "stdafx.h"

#include <list>

//#include "Prototype.h"
#include "FeatureProto.h"
#include "Birch.h"
#include "Beech.h"
#include "BeechLog.h"
#include "BeechHalfLog.h"
#include "Grass.h"

#include "ItemProto.h"
#include "StoneAxe.h"

#include "Elder.h"

#include "ObjectManager.h"

ObjectManager::ObjectManager()
{
	// 테스트용 임시 아이템 생성
	{
		for (auto& item : stoneAxe)
		{
			item = ItemProto::Create(ItemName::StoneAxe);
			item->GetActor()->SetWorldPos(Vector3(RANDOM->Int(0, 10), 50, RANDOM->Int(0, 10)));
			AddItem(item);
		}

		for (auto& item : woodpile)
		{
			item = ItemProto::Create(ItemName::Woodpile);
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


	if (ImGui::Button("GeneratePerinNoiseMap"))
	{
		Release();
		MAP->PerlinNoiseHeightMap();
	}
	if (ImGui::Button("GenerateTree"))
	{
		Release();
		GenerateTree();
	}
	//if (ImGui::Button("GenerateInstance"))
	//{
	//	GenerateInstanceTree();
	//}
	if (ImGui::Button("GenerateInstanceGrass"))
	{
		GenerateInstanceGrass();
	}

	// 리스트에서 요소 제거
	objects.erase(
		std::remove_if
		(
			objects.begin(),
			objects.end(),
			[](Prototype* object)
			{
				// 오브젝트의 파괴 조건 검사
				if (object->IsDestroyed())
				{
					// 파괴 이벤트 호출
					object->DestructionEvent();
					// 리턴값 반환해서 리스트에서 제거
					return true;
				}
				// 파괴 조건이 아니면 리스트에서 제거하지 않음
				else false;
			}
		),
		objects.end()
	);

	// 리스트에서 요소 제거
	items.erase(
		std::remove_if
		(
			items.begin(),
			items.end(),
			[](ItemProto* item)
			{
				// 오브젝트의 파괴 조건 검사
				if (item->IsDestroyed())
				{
					// 파괴 이벤트 호출
					item->DestructionEvent();
					// 리턴값 반환해서 리스트에서 제거
					return true;
				}
				// 파괴 조건이 아니면 리스트에서 제거하지 않음
				else false;
			}
		),
		items.end()
	);


	static float distanceCalCycle = 0;
	// 최적화를 위해 일정 주기로 거리 계산
	if (TIMER->GetTick(distanceCalCycle, 0.1f))
	{
		Vector3 CameraPos = Camera::main->GetWorldPos();
		for (auto& obj : objects)
		{
			// Down Casting
			Beech* beech = dynamic_cast<Beech*>(obj);
			if (beech)
			{
				// 거리에 따라 LOD 적용
				float distance = Vector3::DistanceSquared(CameraPos, beech->GetActor()->GetWorldPos());
				if (distance < 1000) beech->LodUpdate(LodLevel::LOD0);			// 거리 1000 이하는 LOD0
				else if (distance < 2000) beech->LodUpdate(LodLevel::LOD1);		// 거리 2000 이하는 LOD1
				else if (distance < 4000) beech->LodUpdate(LodLevel::LOD3);		// 거리 5000 이하는 LOD3
				else continue;													// 거리 5000 이상은 continue로 업데이트 생략

				obj->Update();
			}

			// Down Casting
			Birch* birch = dynamic_cast<Birch*>(obj);
			if (birch)
			{
				// 거리에 따라 LOD 적용
				float distance = Vector3::DistanceSquared(CameraPos, birch->GetActor()->GetWorldPos());
				if (distance < 1000) birch->LodUpdate(LodLevel::LOD0);			// 거리 1000 이하는 LOD0
				else if (distance < 2000) birch->LodUpdate(LodLevel::LOD1);		// 거리 2000 이하는 LOD1
				else if (distance < 4000) birch->LodUpdate(LodLevel::LOD3);		// 거리 5000 이하는 LOD3
				else continue;													// 거리 5000 이상은 continue로 업데이트 생략

				obj->Update();
			}
			// beech가 아니면 업데이트만
			else
				obj->Update();

		}
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

	for (auto& obj : objects)
	{
		if (PLAYER->CleanHit(obj->GetActor()->collider) && PLAYER->CleanFrame())
		{
			obj->ReceivedDamageEvent(10);
			continue;
		}
	}
}

void ObjectManager::Render()
{
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
					// 오브젝트를 생성하고 위치, 회전, 크기	
					FeatureProto* treeBeech;
					
					if (RANDOM->Int(1, 10) == 1)
						treeBeech = (FeatureProto*)FeatureProto::Create(FeatureType::Birch);
					else
						treeBeech = (FeatureProto*)FeatureProto::Create(FeatureType::Beech);


					treeBeech->GetActor()->SetWorldPos(Hit);
					treeBeech->GetActor()->rotation.y = RANDOM->Float(0, 360) * ToRadian;
					treeBeech->GetActor()->scale = Vector3(RANDOM->Float(0.8f, 1.2f), RANDOM->Float(0.4f, 0.6f), RANDOM->Float(0.8f, 1.2f));

					// 생성된 오브젝트 리스트에 추가
					objects.emplace_back(treeBeech);
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

/*
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

				if (MAP->ComPutePicking(ray, Hit))
				{
					treePos.emplace_back(Hit);
				}
			}
		}
	}

	Beech* treeBeech = new Beech(Vector3(0, 0, 0), RenderType::INSTANCING);

	UINT count = treePos.size();
	Matrix* ins = new Matrix[count];
	int idx = 0;
	for (int i = 1; i < count; i++)
	{
		Vector3 insPos = Vector3(treePos[i].x, treePos[i].y, treePos[i].z);
		ins[idx] = Matrix::CreateTranslation(treePos[i]);
		ins[idx] = ins[idx].Transpose();
		idx++;
	}

	treeBeech->GetActor()->Find("Lod0")->mesh->CreateInstanceBuffer(ins, count);
	treeBeech->GetActor()->Find("Lod0MeshObject1")->mesh->CreateInstanceBuffer(ins, count);
	treeBeech->GetActor()->Find("Lod1")->mesh->CreateInstanceBuffer(ins, count);
	treeBeech->GetActor()->Find("Lod1MeshObject1")->mesh->CreateInstanceBuffer(ins, count);
	treeBeech->GetActor()->Find("Lod3")->mesh->CreateInstanceBuffer(ins, count);
	treeBeech->GetActor()->Find("Lod3MeshObject1")->mesh->CreateInstanceBuffer(ins, count);

	objects.emplace_back(treeBeech);
}
*/

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
