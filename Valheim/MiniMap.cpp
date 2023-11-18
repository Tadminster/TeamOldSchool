#include "stdafx.h"
#include "GameManager.h"
#include "MiniMap.h"

MiniMap::MiniMap()
{

	miniMapUI = UI::Create("miniMap_UI");
	miniMapUI->LoadFile("miniMap_UI.xml");
	miniMapUI->visible = true;

	playerPosUI = UI::Create("player_iconUI");
	playerPosUI->LoadFile("player_iconUI.xml");
	playerPosUI->visible = true;

	
}

MiniMap::~MiniMap()
{
}

void MiniMap::Init()
{
	int textureSize = MAP->rowSize;
	
	
}

void MiniMap::Release()
{
}

void MiniMap::Update()
{
	ImGui::Begin("Hierarchy");
	{
		miniMapUI->RenderHierarchy();
		playerPosUI->RenderHierarchy();
	}
	ImGui::End();
	miniMapUI->Update();
	playerPosUI->Update();
}

void MiniMap::LateUpdate()
{
	
	//터레인 맵의 높이에 따라 다른텍스쳐 색을가진 비트맵생성
    if(ImGui::Button("DrawMiniMap"))
    {
        string test = "DrawMiniMap";
        DrawMiniMap(test);
    }
    if (ImGui::Button("MiniMapTextureLoad"))
    {
        //string path = ""
        //miniMapUI->material->diffuseMap = RESOURCE->textures.Load();
    }

	//-------------------------------------------------
	
	//플레이어 아이콘 보는방향에따라 회전시키기

	//플레이어 아이콘 플레이어 이동에따라 움직이기
}

void MiniMap::PreRender()
{
}

void MiniMap::Render()
{
	miniMapUI->Render();
	playerPosUI->Render();
}

void MiniMap::ResizeScreen()
{
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
	double minHeight = DOUBLE_MAX;		//최소값을 찾기위해 최대값 저장
	double maxHeight = DOUBLE_MIN;		// 최대값을 찾기위해 최소값 저장

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
            int index = i * miniMapSize + j;					// 인덱스 계산

			float height = vertices[index].position.y;
			float normalizedHeight = (height - minHeight) / (maxHeight - minHeight);
            uint8_t color = static_cast<uint8_t>(normalizedHeight * 255);
			// 높이를 0에서 1 사이의 값으로 정규화
            //// BMP 파일에서는 B, G, R, A 순서로 저장됨
            //file.put(color); // Blue
            //file.put(color); // Green
            //file.put(color); // Red
            //file.put(255);   // Alpha (높이맵에서는 사용하지 않음)
            // 색상 결정
            uint8_t red = 0;
            uint8_t green = 0;
            uint8_t blue = 0;

            if (normalizedHeight < 0.0f)
            {
                blue = static_cast<uint8_t>((normalizedHeight + 1.0f) * 127.5f); // 파란색 (바다)
            }
            else if (normalizedHeight < 0.5f)
            {
                green = static_cast<uint8_t>(normalizedHeight * 255 * 2); // 노란색
            }
            else
            {
                green = static_cast<uint8_t>((1.0f - normalizedHeight) * 255 * 2); // 초록색
                red = static_cast<uint8_t>((normalizedHeight - 0.5f) * 255 * 2);    // 빨간색
            }

            // BMP 파일에서는 B, G, R, A 순서로 저장됨
            file.put(blue);  // Blue
            file.put(green); // Green
            file.put(red);   // Red
            file.put(255);   // Alpha (높이맵에서는 사용하지 않음)
        }
    }

    file.close();
}