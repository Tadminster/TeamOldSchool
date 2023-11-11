#include "stdafx.h"

#include <list>

#include "Prototype.h"
#include "TreeBeech.h"
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
	if (ImGui::Button("GenerateInstanceGrass"))
	{
		GenerateInstanceGrass();
	}

	static float distanceCalCycle = 0;
	if (TIMER->GetTick(distanceCalCycle, 1.0f))
	{
		Vector3 CameraPos = Camera::main->GetWorldPos();
		for (auto& obj : objects)
		{
			// Down Casting
			TreeBeech* treeBeechObj = dynamic_cast<TreeBeech*>(obj);
			if (treeBeechObj)
			{
				// �Ÿ��� ���� LOD ����
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
	double frequencyScale = 1.0 / rowSize * 2;			// �� ũ�⿡ ���� ���ļ� ������ ����
	siv::PerlinNoise perlin(RANDOM->Int(0, 10000));		// ���� �õ�� �޸������� ����

	VertexTerrain* vertices = (VertexTerrain*)MAP->mesh->vertices;
	Ray ray; Vector3 Hit;

	for (int i = 0; i < rowSize; i++)
	{
		for (int j = 0; j < rowSize; j++)
		{
			float positionY = vertices[i * rowSize + j].position.y;

			// ����üũ
			// ���̰� -1 ���� �ΰ������� �������� ����
			if (positionY < -1.0f) continue;
			// ���̰� -1 ~ 1 �̸�, 50���� 1 Ȯ���� ����
			else if (positionY < 1.0f)
			{
				if (RANDOM->Int(1, 50) != 1) continue;
			}
			// ���̰� 1 ~ 10 �̸�, 30���� 1 Ȯ���� ����
			else if(positionY < 10.0f)
			{
				if (RANDOM->Int(1, 30) != 1) continue;
			}
			else // ���̰� 10 �̸�, 20���� 1 Ȯ���� ����
			{
				if (RANDOM->Int(1, 20) != 1) continue;
			}

			double x = (double)i * frequencyScale;
			double y = (double)j * frequencyScale;
			double z = 0.5;
			double noiseValue = perlin.noise3D(x, y, z);

			// �޸������� �� üũ
			if (noiseValue > -0.2f)
			{
				ray.position = vertices[i * rowSize + j].position; +Vector3(0, 1000, 0);
				ray.direction = Vector3(0, -1, 0);
				if (MAP->ComPutePicking(ray, Hit))
				{
					TreeBeech* treeBeech = new TreeBeech(Hit, RenderType::SINGLE);
					treeBeech->GetActor()->rotation.y = RANDOM->Float(0, 360) * ToRadian;
					treeBeech->GetActor()->scale = Vector3(RANDOM->Float(0.002f, 0.003f), RANDOM->Float(0.002f, 0.003f), RANDOM->Float(0.002f, 0.003f));
					objects.emplace_back(treeBeech);
				}
			}
		}
	}
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
	Ray ray;
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

	TreeBeech* treeBeech = new TreeBeech(Vector3(0, 0, 0), RenderType::INSTANCING);
	//TreeBeech* treeBeech = new TreeBeech(Vector3(0, treePos[0].y, 0), RenderType::INSTANCING);

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

void ObjectManager::GenerateInstanceGrass()
{
	int rowSize = MAP->rowSize;
	double frequencyScale = 1.0 / rowSize * 2;    // �� ũ�⿡ ���� ���ļ� ������ ����
	//double centerPeak = 2.0;                      // �߾� ���� ����
	//double edgeSteepness = 10.0;                  // �����ڸ� ����� ���ĸ� ����

	int randomSeed = RANDOM->Int(0, 10000);       // ���� �õ�
	siv::PerlinNoise perlin(randomSeed);

	VertexTerrain* vertices = (VertexTerrain*)MAP->mesh->vertices;
	vector<Vector3> grassPos;

	Ray ray;
	Vector3 Hit;
	for (int i = 0; i < rowSize; i++)
	{
		for (int j = 0; j < rowSize; j++)
		{
			double x = (double)i * frequencyScale;
			double y = (double)j * frequencyScale;
			double z = 0.5;
			double noiseValue = perlin.noise3D(x, y, z);

			//// �߾ӿ����� �Ÿ��� ���� ����ġ ����
			//double maxDistance = sqrt(2) * (rowSize / 2.0);

			//// �� ���������� ���� ����� �����ڸ������� �ּ� �Ÿ� ���
			//double minEdgeDistance = min(min(i, rowSize - 1 - i), min(j, rowSize - 1 - j));
			//double edgeFactor = pow((maxDistance - minEdgeDistance) / maxDistance, edgeSteepness) - 1;

			// ���� ���� ���
			//float result = noiseValue - edgeFactor;

			//cout << noiseValue << endl;

			if (noiseValue > 0.0)
			{
				if (RANDOM->Int(1, 5) == 1)
				{

					ray.position = vertices[i * rowSize + j].position; +Vector3(0, 1000, 0);
					ray.direction = Vector3(0, -1, 0);



					if (MAP->ComPutePicking(ray, Hit))
					{
						grassPos.emplace_back(Hit);
					}
				}
			}
		}
	}

	Grass* grass = new Grass(Vector3(0, 0, 0));
	//Grass* grass = new Grass(Vector3(0, grassPos[0].y, 0));

	UINT count = grassPos.size();
	cout << count << endl;
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
