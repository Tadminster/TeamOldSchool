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
	// �׽�Ʈ�� �ӽ� ������ ����
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

	// ����Ʈ���� ��� ����
	objects.erase(
		std::remove_if
		(
			objects.begin(),
			objects.end(),
			[](Prototype* object)
			{
				// ������Ʈ�� �ı� ���� �˻�
				if (object->IsDestroyed())
				{
					// �ı� �̺�Ʈ ȣ��
					object->DestructionEvent();
					// ���ϰ� ��ȯ�ؼ� ����Ʈ���� ����
					return true;
				}
				// �ı� ������ �ƴϸ� ����Ʈ���� �������� ����
				else false;
			}
		),
		objects.end()
	);

	// ����Ʈ���� ��� ����
	items.erase(
		std::remove_if
		(
			items.begin(),
			items.end(),
			[](ItemProto* item)
			{
				// ������Ʈ�� �ı� ���� �˻�
				if (item->IsDestroyed())
				{
					// �ı� �̺�Ʈ ȣ��
					item->DestructionEvent();
					// ���ϰ� ��ȯ�ؼ� ����Ʈ���� ����
					return true;
				}
				// �ı� ������ �ƴϸ� ����Ʈ���� �������� ����
				else false;
			}
		),
		items.end()
	);


	static float distanceCalCycle = 0;
	// ����ȭ�� ���� ���� �ֱ�� �Ÿ� ���
	if (TIMER->GetTick(distanceCalCycle, 0.1f))
	{
		Vector3 CameraPos = Camera::main->GetWorldPos();
		for (auto& obj : objects)
		{
			// Down Casting
			Beech* beech = dynamic_cast<Beech*>(obj);
			if (beech)
			{
				// �Ÿ��� ���� LOD ����
				float distance = Vector3::DistanceSquared(CameraPos, beech->GetActor()->GetWorldPos());
				if (distance < 1000) beech->LodUpdate(LodLevel::LOD0);			// �Ÿ� 1000 ���ϴ� LOD0
				else if (distance < 2000) beech->LodUpdate(LodLevel::LOD1);		// �Ÿ� 2000 ���ϴ� LOD1
				else if (distance < 4000) beech->LodUpdate(LodLevel::LOD3);		// �Ÿ� 5000 ���ϴ� LOD3
				else continue;													// �Ÿ� 5000 �̻��� continue�� ������Ʈ ����

				obj->Update();
			}

			// Down Casting
			Birch* birch = dynamic_cast<Birch*>(obj);
			if (birch)
			{
				// �Ÿ��� ���� LOD ����
				float distance = Vector3::DistanceSquared(CameraPos, birch->GetActor()->GetWorldPos());
				if (distance < 1000) birch->LodUpdate(LodLevel::LOD0);			// �Ÿ� 1000 ���ϴ� LOD0
				else if (distance < 2000) birch->LodUpdate(LodLevel::LOD1);		// �Ÿ� 2000 ���ϴ� LOD1
				else if (distance < 4000) birch->LodUpdate(LodLevel::LOD3);		// �Ÿ� 5000 ���ϴ� LOD3
				else continue;													// �Ÿ� 5000 �̻��� continue�� ������Ʈ ����

				obj->Update();
			}
			// beech�� �ƴϸ� ������Ʈ��
			else
				obj->Update();

		}
	}



	// ������ ������Ʈ
	for (auto& item : items)
		item->Update();
}

void ObjectManager::LateUpdate()
{
	for (auto& item : items)
		item->LateUpdate();

	// ������ �ݱ�(�ӽ�)
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
	// ����� ����� ��
	if (DEBUGMODE)
	{
		// ��� ������Ʈ ������
		for (auto& obj : objects)
		{
			obj->Render();
		}
	}
	// ����� ��尡 �ƴ� ��
	else
	{
		Vector3 CameraPos = Camera::main->GetWorldPos();
		for (auto& obj : objects)
		{
			float distance = Vector3::DistanceSquared(CameraPos, obj->GetActor()->GetWorldPos());
			if (distance > 2500) continue;

			// ī�޶�� �浹�ϴ� ������Ʈ�� ������
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
	// ������Ʈ �Ŵ��� ���� ���̾����Ű
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
	double frequencyScale = 1.0 / rowSize * 2;			// �� ũ�⿡ ���� ���ļ� ������ ����
	siv::PerlinNoise perlin(RANDOM->Int(0, 10000));		// ���� �õ�� �޸������� ����

	VertexTerrain* vertices = (VertexTerrain*)MAP->mesh->vertices;		// ���� ���ؽ� �޾ƿ���
	Ray ray; Vector3 Hit;					// ���̿� ���̰� ���� ������ ������ ����
	ray.position = Vector3();				// ���� ������ �ʱ�ȭ(�ӽ�)
	ray.direction = Vector3(0, -1, 0);		// ���� ����(������ �������� �����ȴ� ����)

	// ���� rowSize * rowSize ��ŭ �ݺ�
	for (int i = 0; i < rowSize; i++)
	{
		for (int j = 0; j < rowSize; j++)
		{
			int index = i * rowSize + j;					// �ε��� ���
			float positionY = vertices[index].position.y;	// ���̰� �޾ƿ���

			// ����üũ
			// ���̰� -1 ���� �ΰ������� �������� ����
			if (positionY < -1.0f)
			{
				continue;
			}
			// ���̰� -1 ~ 1 �̸�, 100���� 1 Ȯ���� ����
			else if (positionY < 0.0f)
			{
				if (RANDOM->Int(1, 100) != 1)
				{
					continue;
				}
			}
			// ���̰� 1 ~ 3 �̸�, 80���� 1 Ȯ���� ����
			else if (positionY < 3.0f)
			{
				if (RANDOM->Int(1, 80) != 1)
				{
					continue;
				}
			}
			// ���̰� 3 ~ 5 �̸�, 70���� 1 Ȯ���� ����
			else if (positionY < 5.0f)
			{
				if (RANDOM->Int(1, 70) != 1)
				{
					continue;
				}
			}
			// ���̰� 5 ~ 7 �̸�, 60���� 1 Ȯ���� ����
			else if (positionY < 7.0f)
			{
				if (RANDOM->Int(1, 60) != 1)
				{
					continue;
				}
			}
			// ���̰� 7 ~ 10 �̸�, 50���� 1 Ȯ���� ����
			else if (positionY < 10.0f)
			{
				if (RANDOM->Int(1, 50) != 1)
				{
					continue;
				}
			}
			else // ���̰� 10 �̻��̸�, 40���� 1 Ȯ���� ����
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

			// �޸������� ���� 0.2 �̻��̰ų�, 50���� 1 Ȯ���� ����
			if (noiseValue > -0.2f/* || RANDOM->Int(1, 50) == 1*/)
			{
				// ������ ��ġ ����
				ray.position = vertices[index].position; + Vector3(0, 1000, 0);	

				// Compute Picking���� ���̿� ���� ������ Hit�� ����
				if (MAP->ComputePicking(ray, Hit))
				{
					// ������Ʈ�� �����ϰ� ��ġ, ȸ��, ũ��	
					FeatureProto* treeBeech;
					
					if (RANDOM->Int(1, 10) == 1)
						treeBeech = (FeatureProto*)FeatureProto::Create(FeatureType::Birch);
					else
						treeBeech = (FeatureProto*)FeatureProto::Create(FeatureType::Beech);


					treeBeech->GetActor()->SetWorldPos(Hit);
					treeBeech->GetActor()->rotation.y = RANDOM->Float(0, 360) * ToRadian;
					treeBeech->GetActor()->scale = Vector3(RANDOM->Float(0.8f, 1.2f), RANDOM->Float(0.4f, 0.6f), RANDOM->Float(0.8f, 1.2f));

					// ������ ������Ʈ ����Ʈ�� �߰�
					objects.emplace_back(treeBeech);
				}
			}
		}
	}

	// ������ ������Ʈ�� ������Ʈ
	for (auto& obj : objects)
	{
		obj->Update();
	}
}

/*
void ObjectManager::GenerateInstanceTree()
{
	int rowSize = MAP->rowSize;
	double frequencyScale = 1.0 / rowSize * 2;			// �� ũ�⿡ ���� ���ļ� ������ ����
	siv::PerlinNoise perlin(RANDOM->Int(0, 10000));		// ���� �õ�� �޸������� ����

	vector<Vector3> treePos;							// �ν��Ͻ� ���� ��ġ ������ ����

	VertexTerrain* vertices = (VertexTerrain*)MAP->mesh->vertices;
	Ray ray; Vector3 Hit;
	ray.position = Vector3();
	ray.direction = Vector3(0, -1, 0);

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
			else if (positionY < 10.0f)
			{
				if (RANDOM->Int(1, 30) != 1) continue;
			}
			else // ���̰� 10 �̻��̸�, 20���� 1 Ȯ���� ����
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
	double frequencyScale = 1.0 / rowSize * 2;			// �� ũ�⿡ ���� ���ļ� ������ ����
	siv::PerlinNoise perlin(RANDOM->Int(0, 10000));		// ���� �õ�� �޸������� ����

	vector<Vector3> grassPos;							// �ν��Ͻ� ���� ��ġ ������ ����

	VertexTerrain* vertices = (VertexTerrain*)MAP->mesh->vertices;
	Ray ray; Vector3 Hit;
	ray.position = Vector3();
	ray.direction = Vector3(0, -1, 0);

	for (int i = 0; i < rowSize; i++)
	{
		for (int j = 0; j < rowSize; j++)
		{
			float positionY = vertices[i * rowSize + j].position.y;

			// ����üũ
			// ���̰� -1 ���� �ΰ������� �������� ����
			if (positionY < -1.0f) continue;
			// ���̰� -1 ~ 1 �̸�, 20���� 1 Ȯ���� ����
			else if (positionY < 1.0f)
			{
				if (RANDOM->Int(1, 20) != 1) continue;
			}
			else // ���̰� 1 �̻� �̸�, 20���� 1 Ȯ���� ����
			{
				if (RANDOM->Int(1, 5) != 1) continue;
			}

			double x = (double)i * frequencyScale;
			double y = (double)j * frequencyScale;
			double z = 0.5;
			double noiseValue = perlin.noise3D(x, y, z);

			// �޸������� �� üũ
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
	cout << "Grass " << count << "�� ����!" << endl;
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
