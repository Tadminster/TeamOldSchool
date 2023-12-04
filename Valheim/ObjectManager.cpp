#include "stdafx.h"
#include <list>

//#include "Prototype.h"
// ��������(����, ��) ===============================================
#include "FeatureProto.h"
#include "Grass.h"

// ������ =============================================================
#include "ItemProto.h"

// ���౸���� ========================================================
#include "StructureProto.h"
// ���� ===============================================================
#include "Elder.h"

#include "ObjectManager.h"

ObjectManager::ObjectManager()
{
	 //�׽�Ʈ�� �ӽ� ������ ����
	/*
	{
		for (auto& item : stoneAxe)
		{
			item = ItemProto::Create(Item::StoneAxe);
			AddItem(item);
		}

		for (auto& item : woodpile)
		{
			item = ItemProto::Create(Item::Woodpile);
			AddItem(item);
		}

		for (auto& item : stone)
		{
			item = ItemProto::Create(Item::Stone);
			AddItem(item);
		}

		for (auto& item : woodShield)
		{
			item = ItemProto::Create(Item::WoodShield);
			AddItem(item);
		}

		for (auto& item : leather)
		{
			item = ItemProto::Create(Item::Leather);
			AddItem(item);
		}

		for (auto& item : elderTrophy)
		{
			item = ItemProto::Create(Item::ElderTrophy);
			AddItem(item);
		}

		for (auto& item : fineWood)
		{
			item = ItemProto::Create(Item::FineWood);
			AddItem(item);
		}
	}
	*/
}

ObjectManager::~ObjectManager()
{

}

void ObjectManager::Init()
{

	while (featureCount < MINIMUM_FEATURE_COUNT)
		GenerateTree();

	shipwreck = FeatureProto::Create(FeatureType::Shipwreck);
	shipwreck->Init();
	objects.emplace_back(shipwreck);

	for (auto& item : items)
	{
		Vector3 tempPos = Vector3(startingPosition->x + RANDOM->Int(-5, 5), 50, startingPosition->z + RANDOM->Int(-5, 5));
		item->GetActor()->SetWorldPos(tempPos);
	}

	//GenerateInstanceGrass();
}

void ObjectManager::Release()
{
	if (objects.empty()) return;

	for (auto& obj : objects)
	{
		obj->Release();
	}
	objects.clear();

	for (auto& item : items)
	{
		item->Release();
	}
	items.clear();




	featureCount = 0;
}

void ObjectManager::Update()
{
	//if (ImGui::Button("Generate PerinNoiseMap"))
	//{
	//	Release();
	//	MAP->PerlinNoiseHeightMap();
	//}
	//if (ImGui::Button("Generate Tree"))
	//{
	//	Release();
	//	GenerateTree();
	//}
	//if (ImGui::Button("Generate Instancing Tree"))
	//{
	//	GenerateInstanceTree();
	//}
	//if (ImGui::Button("Generate Instance Grass"))
	//{
	//	GenerateInstanceGrass();
	//}

	ListEraser(objects);
	ListEraser(items);
	//ListEraser(structures);

	// ������Ʈ ������Ʈ
	{
		for (auto& obj : objects)
		{
			obj->Update();
		}
	}

	// �ν��Ͻ� ������Ʈ ������Ʈ
	for (auto& instance : instancingObjects)
	{
		instance->Update();
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
}

void ObjectManager::Render()
{
	// �ν��Ͻ� ������Ʈ ������
	for (auto& instance : instancingObjects)
	{
		instance->Render();
	}

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

	// ������ ������
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
	//ImGui::Begin("TerrainHierarchy");
	{
	//	for (auto& obj : objects)
	//	{
	//		obj->GetActor()->RenderHierarchy();
	//	}
		/*for (auto& objInstancing : instancingObjects)
		{
			objInstancing->GetActor()->RenderHierarchy();
		}*/
	}
	//ImGui::End();
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
			// �����¿� Ž���� ���� �ε��� ���
			int preI = clamp(i, 0, rowSize - 1);
			int postI = clamp(i, 0, rowSize + 1);
			int preJ = clamp(j, 0, rowSize - 1);
			int postJ = clamp(j, 0, rowSize + 1);

			// ������Ʈ�� �̹� �����Ǿ��ְų�, 
			if (MAP->isThereFeature[i][j]) continue;
			// �ֺ��� ������Ʈ�� �����Ǿ������� �������� ����
			else if (MAP->isThereFeature[i][preI] || MAP->isThereFeature[i][postI]) continue;
			else if (MAP->isThereFeature[preJ][j] || MAP->isThereFeature[postJ][j]) continue;

			int index = i * rowSize + j;					// �ε��� ���
			float positionY = vertices[index].position.y;	// ���̰� �޾ƿ���

			if (positionY > 0.2f && positionY < 0.5f)
			{
				if (!startingPosition) startingPosition = &vertices[index].position;
				else
				{
					if (RANDOM->Int(1, 50) == 1)
					{
						startingPosition = &vertices[index].position;
					}
				}
			}

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
				ray.position = vertices[index].position; +Vector3(0, 1000, 0);

				// Compute Picking���� ���̿� ���� ������ Hit�� ����
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

					// ������Ʈ ��ġ ����
					feature->GetActor()->SetWorldPos(Hit);

					// ������Ʈ�� �����Ǿ����� ǥ��
					MAP->isThereFeature[i][j] = true;

					featureCount++;

					// ������ ������Ʈ ����Ʈ�� �߰�
					objects.emplace_back(feature);
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


void ObjectManager::GenerateInstanceGrass()
{
	//cout << "Generate Instance Grass" << endl;

	int rowSize = MAP->rowSize;
	double frequencyScale = 1.0 / rowSize * 2;			// �� ũ�⿡ ���� ���ļ� ������ ����
	siv::PerlinNoise perlin(RANDOM->Int(0, 10000));		// ���� �õ�� �޸������� ����

	vector<Vector3> grassPos;							// �ν��Ͻ� Grass ��ġ ������ ����

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
			// ���̰� 0 ���� �ΰ������� �������� ����
			if (positionY < -0.0f) continue;
			// ���̰� 0 ~ 1 �̸�, 50���� 1 Ȯ���� ����
			else if (positionY < 1.0f)
			{
				if (RANDOM->Int(1, 50) != 1) continue;
			}
			// ���̰� 1 ~ 10 �̸�, 20���� 1 Ȯ���� ����
			else if (positionY < 10.0f)
			{
				if (RANDOM->Int(1, 20) != 1) continue;
			}
			else // ���̰� 10 �̻��̸�, 10���� 1 Ȯ���� ����
			{
				if (RANDOM->Int(1, 10) != 1) continue;
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
	grass->Update();
	//float baseline = fabs(grass->GetActor()->GetWorldPos().y);

	UINT count = grassPos.size();
	Matrix* ins = new Matrix[count];
	for (int i = 0; i < count; i++)
	{
		Vector3 insPos = Vector3(grassPos[i].x, grassPos[i].y /*- baseline*/, grassPos[i].z);
		ins[i] = Matrix::CreateTranslation(insPos);
		ins[i] = ins[i].Transpose();
	}

	grass->GetActor()->Find("grasscross__1_")->mesh->CreateInstanceBuffer(ins, count);
	grass->Update();

	//cout << "Instance Grass Count : " << count << endl;
	instancingObjects.emplace_back(grass);
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
