#include "stdafx.h"
#include "GameManager.h"
#include "MiniMap.h"

MiniMap::MiniMap()
{

	miniMap = UI::Create("UI_MiniMap");
	miniMap->LoadFile("UI_MiniMap.xml");
	miniMap->visible = true;

	playerIcon = UI::Create("UI_Player_Icon");
	playerIcon->LoadFile("UI_Player_Icon.xml");
	playerIcon->visible = true;


}

MiniMap::~MiniMap()
{
}

void MiniMap::Init()
{
	int textureSize = MAP->rowSize;
	DrawMiniMap("DrawMiniMap");
	LoadMiniMap();
}

void MiniMap::Release()
{
}

void MiniMap::Update()
{
	/*ImGui::Begin("UI Hierarchy");
	{
		miniMap->RenderHierarchy();
		playerIcon->RenderHierarchy();
	}
	ImGui::End();*/
	miniMap->Update();
	playerIcon->Update();
}

void MiniMap::LateUpdate()
{

	//�ͷ��� ���� ���̿� ���� �ٸ��ؽ��� �������� ��Ʈ�ʻ���
	//if (ImGui::Button("DrawMiniMap"))
	//{
	//	string test = "DrawMiniMap";
	//	DrawMiniMap(test);
	//}
	////�̴ϸ� ���͸��� ��ǻ��� �ͷ��θ��̹����߰����
	//if (ImGui::Button("MiniMapTextureLoad"))
	//{
	//	string filepath = "MiniMap/DrawMiniMap.bmp";
	//	SafeReset(miniMap->material->diffuseMap);
	//	miniMap->material->diffuseMap = RESOURCE->textures.Load(filepath);
	//}

	//-------------------------------------------------

	//�÷��̾� ������ ���¹��⿡���� ȸ����Ű��
	FollowPlayerViewPoint();
	//�÷��̾� ������ �÷��̾� �̵������� �����̱� ���Ŀ� ����ȭ�� �����ϸ� �ð���� ex gettick
	//������ ���ʿ��Ѱ����� ���̰� �ϱ�
	FollowPlayerMovement();
}

void MiniMap::PreRender()
{
}

void MiniMap::Render()
{
	miniMap->Render();
	playerIcon->Render();
}

void MiniMap::ResizeScreen()
{
}

Color MiniMap::GetColorForWeight(float normalizedHeight)
{
	if (normalizedHeight <= 0)
		return Color(0.0f, 0.358f, 0.6f); //�ٴٻ�
	float minmapheight = normalizedHeight * normalizedHeight;
	// �𷡻����� ������� �ڿ������� ����
	Color sandColor(0.7608f, 0.6980f, 0.5020f);    // �𷡻�
	Color grassColor(0.0f, 0.4020f, 0.0f);         // �ʷϻ�

	return Color::Lerp(sandColor, grassColor, minmapheight);
}


void  MiniMap::DrawMiniMap(const string& filename)
{
	int miniMapSize = MAP->rowSize;
	VertexTerrain* vertices = (VertexTerrain*)MAP->mesh->vertices;

	BITMAPFILEHEADER bfh;
	BITMAPINFOHEADER bih;

	// BMP ��� ����
	bfh.bfType = 0x4D42; // "BM"�� ��Ÿ��
	bfh.bfSize = sizeof(BITMAPFILEHEADER) + sizeof(BITMAPINFOHEADER) + miniMapSize * miniMapSize * 4; // 4�� RGBA ä�� ��
	bfh.bfReserved1 = 0;
	bfh.bfReserved2 = 0;
	bfh.bfOffBits = sizeof(BITMAPFILEHEADER) + sizeof(BITMAPINFOHEADER);

	bih.biSize = sizeof(BITMAPINFOHEADER);
	bih.biWidth = miniMapSize;
	bih.biHeight = miniMapSize;
	bih.biPlanes = 1;
	bih.biBitCount = 32; // 32��Ʈ RGBA
	bih.biCompression = 0;
	bih.biSizeImage = miniMapSize * miniMapSize * 4;
	bih.biXPelsPerMeter = 0;
	bih.biYPelsPerMeter = 0;
	bih.biClrUsed = 0;
	bih.biClrImportant = 0;

	// BMP ���� ����
	string fullpath = "../Contents/Texture/MiniMap/";
	ofstream file(fullpath + filename + ".bmp", ios::out | ios::binary);
	file.write(reinterpret_cast<char*>(&bfh), sizeof(BITMAPFILEHEADER));
	file.write(reinterpret_cast<char*>(&bih), sizeof(BITMAPINFOHEADER));

	// ���̸ʿ��� RGBA ������ ���� �� ����
	// ������ �ּҰ��� �ִ밪�� ã�� ���� ����
	double minHeight = DOUBLE_MAX;    // �ּҰ��� ã�� ���� �ִ밪 ����
	double maxHeight = DOUBLE_MIN;    // �ִ밪�� ã�� ���� �ּҰ� ����

	// ��� ������ ��ȸ�Ͽ� �ִ� ���̸� ã��
	for (int i = 0; i < miniMapSize * miniMapSize; i++)
	{
		minHeight = min(minHeight, vertices[i].position.y);
		maxHeight = max(maxHeight, vertices[i].position.y);
	}

	for (int i = 0; i < miniMapSize; ++i)
	{
		for (int j = 0; j < miniMapSize; ++j)
		{
			int index = i * miniMapSize + j;                    // �ε��� ���

			float height = vertices[index].position.y;
			float normalizedHeight = height < 0.0 ? (height - minHeight) / (minHeight - maxHeight) : (height - minHeight) / (maxHeight - minHeight);

			// ���� ����
			Color color = GetColorForWeight(normalizedHeight);

			// BMP ���Ͽ����� B, G, R, A ������ �����
			file.put(static_cast<uint8_t>(color.B() * 255));  // Blue
			file.put(static_cast<uint8_t>(color.G() * 255)); // Green
			file.put(static_cast<uint8_t>(color.R() * 255));   // Red
			file.put(255);   // Alpha (���̸ʿ����� ������� ����)

		}
	}

	file.close();
}

void MiniMap::LoadMiniMap()
{
	string filepath = "MiniMap/DrawMiniMap.bmp";
	SafeReset(miniMap->material->diffuseMap);
	miniMap->material->diffuseMap = RESOURCE->textures.Load(filepath);
}

void MiniMap::FollowPlayerViewPoint()
{
	playerIcon->rotation.z = PLAYER->GetActor()->rotation.y;
}

void MiniMap::FollowPlayerMovement()
{
	//����ȭ�� �÷��̾� ��ġ
	float playerPosX = (PLAYER->GetActor()->GetWorldPos().x + MAP->rowSize * 0.5f) / MAP->rowSize;
	float playerPosZ = (PLAYER->GetActor()->GetWorldPos().z + MAP->rowSize * 0.5f) / MAP->rowSize;

	// �÷��̾� �������� �̴ϸ� �󿡼��� ��ġ�� �̵�
	playerIcon->SetWorldPosX(miniMapMinScaleX + moveWeightX * playerPosX);
	playerIcon->SetWorldPosY(miniMapMaxScaleY - moveWeightY * playerPosZ);
}

