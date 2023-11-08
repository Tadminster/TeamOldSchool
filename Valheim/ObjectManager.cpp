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
	if (ImGui::Button("GenerateFeatures"))
	{
		GenerateFeatures();
	}

	for (auto& prototype : mPrototypes)
	{
		prototype->Update();
	}

}

void ObjectManager::LateUpdate()
{
	for (auto& prototype : mPrototypes)
	{
		prototype->LateUpdate();
	}
}

void ObjectManager::Render()
{
	for (auto& prototype : mPrototypes)
	{
		prototype->Render();
	}
}

void ObjectManager::RenderHierarchy()
{
	ImGui::Begin("TerrainHierarchy");
	{
	}
	ImGui::End();
}

void ObjectManager::GenerateFeatures()
{
	int rowSize = MAP->rowSize;
	double frequencyScale = 1.0 / rowSize * 2;    // �� ũ�⿡ ���� ���ļ� ������ ����
	double centerPeak = 2.0;                      // �߾� ���� ����
	double edgeSteepness = 10.0;                  // �����ڸ� ����� ���ĸ� ����

	int randomSeed = RANDOM->Int(0, 10000);       // ���� �õ�
	siv::PerlinNoise perlin(randomSeed);

	VertexTerrain* vertices = (VertexTerrain*)MAP->mesh->vertices;
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

			// ���� ���� ��� (edgeFactor�� ���ϴ� ������� ����)
			float result = noiseValue - edgeFactor;
			cout << result << endl;

			//cout << result << endl;
			if (result > 1 /*|| result > RANDOM->Float(0, 1)*/)
			{
				
				Ray ray;
				ray.position = vertices[i * rowSize + j].position; + Vector3(0, 10000, 0);
				ray.direction = Vector3(0, -1, 0);
				Vector3 Hit;
				if (MAP->ComPutePicking(ray, Hit))
				{
					cout << "��������";
					mPrototypes.emplace_back(new TreeBeech(Hit));
				}
			}
		}
	}
}
