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
	if (ImGui::Button("GenerateInstanceFeature"))
	{
		GenerateInstanceFeature();
	}

	//static float updateCycle = 0;
	//if (TIMER->GetTick(updateCycle, 1.0f))
	//{
	//	for (auto& obj : objects)
	//	{
	//		if (Camera::main->Intersect(obj->GetActor()->GetWorldPos()))
	//		{
	//			obj->Update();
	//		}
	//	}
	//}

	static float distanceCalCycle = 0;
	if (TIMER->GetTick(distanceCalCycle, 1.0f))
	{
		Vector3 CameraPos = Camera::main->GetWorldPos();
		for (auto& obj : objects)
		{
			TreeBeech* treeBeechObj = static_cast<TreeBeech*>(obj);
			if (treeBeechObj)
			{
				float distance = Vector3::DistanceSquared(CameraPos, treeBeechObj->GetActor()->GetWorldPos());
				if (distance < 2000) treeBeechObj->LodUpdate(LodLevel::LOD0);
				else if (distance < 5000) treeBeechObj->LodUpdate(LodLevel::LOD1);
				else if (distance < 10000) treeBeechObj->LodUpdate(LodLevel::LOD3);
				else continue;

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
		obj->Render();
	}
}

void ObjectManager::FrustumCulling(Camera* cam)
{
	for (auto& obj : objects)
	{
		if (cam->Intersect(obj->GetActor()->GetWorldPos()))
		{
			obj->Render();
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

void ObjectManager::GenerateFeatures()
{
	int rowSize = MAP->rowSize;
	double frequencyScale = 1.0 / rowSize * 2;		// �� ũ�⿡ ���� ���ļ� ������ ����
	double centerPeak = 2.0;						// �߾� ���� ����
	double edgeSteepness = 10.0;					// �����ڸ� ����� ���ĸ� ����

	int randomSeed = RANDOM->Int(0, 10000);			// ���� �õ�
	siv::PerlinNoise perlin(randomSeed);			// �۸� ������ ����

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

			// �߾ӿ����� �Ÿ��� ���� ����ġ ����
			double maxDistance = sqrt(2) * (rowSize / 2.0);

			// �� ���������� ���� ����� �����ڸ������� �ּ� �Ÿ� ���
			double minEdgeDistance = min(min(i, rowSize - 1 - i), min(j, rowSize - 1 - j));
			double edgeFactor = pow((maxDistance - minEdgeDistance) / maxDistance, edgeSteepness) - 1;

			// ���� ���� ���
			float result = noiseValue - edgeFactor;

			if (result > 1.0f || result > RANDOM->Float(0, 1))
			{
				if (RANDOM->Int(1, 50) == 1)
				{
					Ray ray;
					ray.position = vertices[i * rowSize + j].position; +Vector3(0, 1000, 0);
					ray.direction = Vector3(0, -1, 0);
					Vector3 Hit;
					if (MAP->ComPutePicking(ray, Hit))
					{
						TreeBeech* treeBeech = new TreeBeech(Hit, RenderType::SINGLE);
						treeBeech->GetActor()->rotation.y = RANDOM->Float(0, 360) * ToRadian;
						treeBeech->GetActor()->scale = Vector3(RANDOM->Float(0.002f, 0.003f), RANDOM->Float(0.002f, 0.003f), RANDOM->Float(0.002f, 0.003f));
						objects.emplace_back(treeBeech);
						count++;
					}
				}
			}
		}
	}
	cout << "������ ���� ��:" << count;
}

void ObjectManager::GenerateInstanceFeature()
{
	int rowSize = MAP->rowSize;
	double frequencyScale = 1.0 / rowSize * 2;    // �� ũ�⿡ ���� ���ļ� ������ ����
	double centerPeak = 2.0;                      // �߾� ���� ����
	double edgeSteepness = 10.0;                  // �����ڸ� ����� ���ĸ� ����

	int randomSeed = RANDOM->Int(0, 10000);       // ���� �õ�
	siv::PerlinNoise perlin(randomSeed);

	VertexTerrain* vertices = (VertexTerrain*)MAP->mesh->vertices;
	vector<Vector3> treePos;
	for (int i = 0; i < rowSize; i++)
	{
		for (int j = 0; j < rowSize; j++)
		{
			double x = (double)i * frequencyScale;
			double y = (double)j * frequencyScale;
			double z = 0.5;
			double noiseValue = perlin.noise3D(x, y, z);

			// �߾ӿ����� �Ÿ��� ���� ����ġ ����
			double maxDistance = sqrt(2) * (rowSize / 2.0);

			// �� ���������� ���� ����� �����ڸ������� �ּ� �Ÿ� ���
			double minEdgeDistance = min(min(i, rowSize - 1 - i), min(j, rowSize - 1 - j));
			double edgeFactor = pow((maxDistance - minEdgeDistance) / maxDistance, edgeSteepness) - 1;

			// ���� ���� ���
			float result = noiseValue - edgeFactor;

			if (result > 1.0f || result > RANDOM->Float(0, 1))
			{
				if (RANDOM->Int(1, 50) == 1)
				{
					Ray ray;
					ray.position = vertices[i * rowSize + j].position; +Vector3(0, 1000, 0);
					ray.direction = Vector3(0, -1, 0);
					Vector3 Hit;


					if (MAP->ComPutePicking(ray, Hit))
					{
						treePos.emplace_back(Hit);
					}
				}
			}
		}
	}
	//cout << "������ ���� ��:" << count;

	TreeBeech* treeBeech = new TreeBeech(Vector3(0, 0, 0), RenderType::INSTANCING);

	UINT count = treePos.size();
	Matrix* ins = new Matrix[count];
	int idx = 0;
	for (int i = 0; i < count; i++)
	{
		ins[idx] = Matrix::CreateTranslation(treePos[i]);
		ins[idx] = ins[idx].Transpose();
		idx++;
	}
	treeBeech->GetActor()->Find("Lod0")->mesh->CreateInstanceBuffer(ins, count);
	treeBeech->GetActor()->Find("beech_barkMeshObject1")->mesh->CreateInstanceBuffer(ins, count);
	treeBeech->GetActor()->Find("Lod1")->mesh->CreateInstanceBuffer(ins, count);
	treeBeech->GetActor()->Find("Lod3")->mesh->CreateInstanceBuffer(ins, count);

	objects.emplace_back(treeBeech);
}
