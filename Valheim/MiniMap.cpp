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

	//터레인 맵의 높이에 따라 다른텍스쳐 색을가진 비트맵생성
	//if (ImGui::Button("DrawMiniMap"))
	//{
	//	string test = "DrawMiniMap";
	//	DrawMiniMap(test);
	//}
	////미니맵 머터리얼에 디퓨즈맵 터레인맵이미지추가기능
	//if (ImGui::Button("MiniMapTextureLoad"))
	//{
	//	string filepath = "MiniMap/DrawMiniMap.bmp";
	//	SafeReset(miniMap->material->diffuseMap);
	//	miniMap->material->diffuseMap = RESOURCE->textures.Load(filepath);
	//}

	//-------------------------------------------------

	//플레이어 아이콘 보는방향에따라 회전시키기
	FollowPlayerViewPoint();
	//플레이어 아이콘 플레이어 이동에따라 움직이기 추후에 최적화가 가능하면 시간제어나 ex gettick
	//등으로 꼭필요한곳에만 쓰이게 하기
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
		return Color(0.0f, 0.358f, 0.6f); //바다색
	float minmapheight = normalizedHeight * normalizedHeight;
	// 모래색에서 녹색으로 자연스럽게 보간
	Color sandColor(0.7608f, 0.6980f, 0.5020f);    // 모래색
	Color grassColor(0.0f, 0.4020f, 0.0f);         // 초록색

	return Color::Lerp(sandColor, grassColor, minmapheight);
}


void  MiniMap::DrawMiniMap(const string& filename)
{
	int miniMapSize = MAP->rowSize;
	VertexTerrain* vertices = (VertexTerrain*)MAP->mesh->vertices;

	BITMAPFILEHEADER bfh;
	BITMAPINFOHEADER bih;

	// BMP 헤더 설정
	bfh.bfType = 0x4D42; // "BM"을 나타냄
	bfh.bfSize = sizeof(BITMAPFILEHEADER) + sizeof(BITMAPINFOHEADER) + miniMapSize * miniMapSize * 4; // 4는 RGBA 채널 수
	bfh.bfReserved1 = 0;
	bfh.bfReserved2 = 0;
	bfh.bfOffBits = sizeof(BITMAPFILEHEADER) + sizeof(BITMAPINFOHEADER);

	bih.biSize = sizeof(BITMAPINFOHEADER);
	bih.biWidth = miniMapSize;
	bih.biHeight = miniMapSize;
	bih.biPlanes = 1;
	bih.biBitCount = 32; // 32비트 RGBA
	bih.biCompression = 0;
	bih.biSizeImage = miniMapSize * miniMapSize * 4;
	bih.biXPelsPerMeter = 0;
	bih.biYPelsPerMeter = 0;
	bih.biClrUsed = 0;
	bih.biClrImportant = 0;

	// BMP 파일 생성
	string fullpath = "../Contents/Texture/MiniMap/";
	ofstream file(fullpath + filename + ".bmp", ios::out | ios::binary);
	file.write(reinterpret_cast<char*>(&bfh), sizeof(BITMAPFILEHEADER));
	file.write(reinterpret_cast<char*>(&bih), sizeof(BITMAPINFOHEADER));

	// 높이맵에서 RGBA 데이터 생성 및 저장
	// 높이의 최소값과 최대값을 찾기 위한 변수
	double minHeight = DOUBLE_MAX;    // 최소값을 찾기 위해 최대값 저장
	double maxHeight = DOUBLE_MIN;    // 최대값을 찾기 위해 최소값 저장

	// 모든 정점을 순회하여 최대 높이를 찾음
	for (int i = 0; i < miniMapSize * miniMapSize; i++)
	{
		minHeight = min(minHeight, vertices[i].position.y);
		maxHeight = max(maxHeight, vertices[i].position.y);
	}

	for (int i = 0; i < miniMapSize; ++i)
	{
		for (int j = 0; j < miniMapSize; ++j)
		{
			int index = i * miniMapSize + j;                    // 인덱스 계산

			float height = vertices[index].position.y;
			float normalizedHeight = height < 0.0 ? (height - minHeight) / (minHeight - maxHeight) : (height - minHeight) / (maxHeight - minHeight);

			// 색상 결정
			Color color = GetColorForWeight(normalizedHeight);

			// BMP 파일에서는 B, G, R, A 순서로 저장됨
			file.put(static_cast<uint8_t>(color.B() * 255));  // Blue
			file.put(static_cast<uint8_t>(color.G() * 255)); // Green
			file.put(static_cast<uint8_t>(color.R() * 255));   // Red
			file.put(255);   // Alpha (높이맵에서는 사용하지 않음)

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
	//정규화된 플레이어 위치
	float playerPosX = (PLAYER->GetActor()->GetWorldPos().x + MAP->rowSize * 0.5f) / MAP->rowSize;
	float playerPosZ = (PLAYER->GetActor()->GetWorldPos().z + MAP->rowSize * 0.5f) / MAP->rowSize;

	// 플레이어 아이콘을 미니맵 상에서의 위치로 이동
	playerIcon->SetWorldPosX(miniMapMinScaleX + moveWeightX * playerPosX);
	playerIcon->SetWorldPosY(miniMapMaxScaleY - moveWeightY * playerPosZ);
}

