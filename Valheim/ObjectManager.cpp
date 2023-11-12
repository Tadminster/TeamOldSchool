#include "stdafx.h"

#include <list>

#include "Prototype.h"
#include "FeatureProto.h"
#include "Beech.h"
#include "BeechLog.h"
#include "BeechHalfLog.h"
#include "Grass.h"

#include "ObjectManager.h"

ObjectManager::ObjectManager()
{
}

ObjectManager::~ObjectManager()
{

}

void ObjectManager::Init()
{
}

void ObjectManager::Release()
{
}

void ObjectManager::Update()
{
	//ImGui::Text("Object Count: %d", objects.size());

	if (ImGui::Button("GenerateTree"))
	{
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


	objects.erase(
		std::remove_if
		(
			objects.begin(),
			objects.end(),
			[](Prototype* object)
			{
				Beech* beech = dynamic_cast<Beech*>(object);
				if (beech && beech->isDestroyed())
				{
					beech->DestructionEvent();
					return true;
				}
				else return false;
			}
		),
		objects.end()
	);


	static float distanceCalCycle = 0;
	if (TIMER->GetTick(distanceCalCycle, 1.0f))
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
				if (distance < 1000) beech->LodUpdate(LodLevel::LOD0);
				else if (distance < 2000) beech->LodUpdate(LodLevel::LOD1);
				else if (distance < 5000) beech->LodUpdate(LodLevel::LOD3);
				else continue;

				obj->Update();
			}
			else
				obj->Update();

		}
	}
}

void ObjectManager::LateUpdate()
{
	//for (auto& obj : objects)
	//{
	//	obj->LateUpdate();
	//}

	for (auto& obj : objects)
	{
		if (PLAYER->GetActor()->Find("StoneAxe"))
		{
			if (PLAYER->GetActor()->Find("StoneAxe")->collider->Intersect(obj->GetActor()->Find("Collider")->collider))
			{
				Beech* beech = dynamic_cast<Beech*>(obj);
				if (beech)
				{
					cout << "Beech Hit" << endl;
					beech->ReceivedDamageEvent(1);
				}
			}
		}
	}
}

void ObjectManager::Render()
{
	if (DEBUGMODE)
	{
		for (auto& obj : objects)
		{
			obj->Render();
		}
	}
	else
	{
		for (auto& obj : objects)
		{
			if (PLAYER->GetPlayerCam()->Intersect(obj->GetActor()->GetWorldPos()))
			{
				obj->Render();
			}
		}
	}
}

void ObjectManager::RenderHierarchy()
{
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
			// 높이가 -1 ~ 1 이면, 100분의 1 확률로 생성
			else if (positionY < 1.0f)
			{
				if (RANDOM->Int(1, 100) != 1) continue;
			}
			// 높이가 1 ~ 10 이면, 50분의 1 확률로 생성
			else if (positionY < 10.0f)
			{
				if (RANDOM->Int(1, 50) != 1) continue;
			}
			else // 높이가 10 이상이면, 30분의 1 확률로 생성
			{
				if (RANDOM->Int(1, 40) != 1) continue;
			}

			double x = (double)i * frequencyScale;
			double y = (double)j * frequencyScale;
			double z = 0.5;
			double noiseValue = perlin.noise3D(x, y, z);

			// 펄린노이즈 값이 0.2 이상이거나, 50분의 1 확률로 생성
			if (noiseValue > -0.2f || RANDOM->Int(1, 50) == 1)
			{
				ray.position = vertices[i * rowSize + j].position; + Vector3(0, 1000, 0);

				if (MAP->ComPutePicking(ray, Hit))
				{
					FeatureProto* treeBeech = FeatureProto::Create(FeatureType::Beech);
					treeBeech->GetActor()->SetWorldPos(Hit);
					treeBeech->GetActor()->rotation.y = RANDOM->Float(0, 360) * ToRadian;
					treeBeech->GetActor()->scale = Vector3(RANDOM->Float(0.8f, 1.2f), RANDOM->Float(0.4f, 0.6f), RANDOM->Float(0.8f, 1.2f));
					objects.emplace_back(move(treeBeech));
				}
			}
		}
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

				if (MAP->ComPutePicking(ray, Hit))
				{
					grassPos.emplace_back(Hit);
				}
			}
		}
	}

	Grass* grass = new Grass(Vector3(0, 0, 0));
	//Grass* grass = new Grass(Vector3(0, grassPos[0].y, 0));

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
