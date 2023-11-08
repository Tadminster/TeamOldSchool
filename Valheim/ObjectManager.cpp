	#include "stdafx.h"

	#include <list>

	#include "Prototype.h"
	#include "TreeBeech.h"

	#include "ObjectManager.h"

ObjectManager::ObjectManager()
{
}

ObjectManager::~ObjectManager()
{

}

void ObjectManager::Init()
{
	//mPrototypes.emplace_back(new TreeBeech());
}

void ObjectManager::Release()
{
}

void ObjectManager::Update()
{
	//ImGui::Text("Object Count: %d", objects.size());

	if (ImGui::Button("GenerateFeatures"))
	{
		GenerateFeatures();
	}

	static float time = 0;
	if (TIMER->GetTick(time, 1.0f))
	{
		for (auto& obj : objects)
		{
			if (Camera::main->Intersect(obj->GetActor()->GetWorldPos()))
			{
				obj->Update();
			}
		}
	}
}

void ObjectManager::LateUpdate()
{
	//for (auto& obj : objects)
	//{
	//	obj->LateUpdate();
	//}
}

void ObjectManager::Render()
{
	for (auto& obj : objects)
	{
		if (Camera::main->Intersect(obj->GetActor()->GetWorldPos()))
		{
			obj->Render();
		}
	}
}

void ObjectManager::RenderHierarchy()
{
	ImGui::Begin("TerrainHierarchy");
	{
		//for (auto& obj : objects)
		//{
		//	obj->GetActor()->RenderHierarchy();
		//}
	}
	ImGui::End();
}

void ObjectManager::GenerateFeatures()
{
	int rowSize = MAP->rowSize;
	double frequencyScale = 1.0 / rowSize * 2;    // 맵 크기에 따른 주파수 스케일 조정
	double centerPeak = 2.0;                      // 중앙 높이 증가
	double edgeSteepness = 10.0;                  // 가장자리 경사의 가파름 조절

	int randomSeed = RANDOM->Int(0, 10000);       // 난수 시드
	siv::PerlinNoise perlin(randomSeed);

	VertexTerrain* vertices = (VertexTerrain*)MAP->mesh->vertices;
	static int count = 0;
	for (int i = 0; i < rowSize; i++)
	{
		for (int j = 0; j < rowSize; j++)
		{
			double x = (double)i * frequencyScale;
			double y = (double)j * frequencyScale;
			double z = 0.5;
			double noiseValue = perlin.noise3D(x, y, z);

			// 중앙에서의 거리에 따라 가중치 적용
			double maxDistance = sqrt(2) * (rowSize / 2.0);

			// 각 꼭짓점에서 가장 가까운 가장자리까지의 최소 거리 계산
			double minEdgeDistance = min(min(i, rowSize - 1 - i), min(j, rowSize - 1 - j));
			double edgeFactor = pow((maxDistance - minEdgeDistance) / maxDistance, edgeSteepness) - 1;

			// 최종 높이 계산
			float result = noiseValue - edgeFactor;

			//cout << result << endl;
			if (result > 1.0f || result > RANDOM->Float(0, 1))
			{
				if (RANDOM->Int(1, 100) == 1)
				{
					Ray ray;
					ray.position = vertices[i * rowSize + j].position; +Vector3(0, 1000, 0);
					ray.direction = Vector3(0, -1, 0);
					Vector3 Hit;
					if (MAP->ComPutePicking(ray, Hit))
					{
						TreeBeech* treeBeech = new TreeBeech(Hit);
						treeBeech->GetActor()->rotation.y = RANDOM->Float(0, 360) * ToRadian;
						treeBeech->GetActor()->scale = Vector3(RANDOM->Float(0.2f, 0.3f), RANDOM->Float(0.2f, 0.3f), RANDOM->Float(0.2f, 0.3f));
						objects.emplace_back(treeBeech);
						count++;
					}
				}
			}
		}
	}
	cout << "생성된 나무 수:" << count;
}
