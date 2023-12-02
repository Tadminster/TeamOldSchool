#include "framework.h"

Terrain* Terrain::Create(string name)
{
	Terrain* map = new Terrain();
	map->type = ObType::Terrain;
	map->name = name;
	map->rowSize = 257;
	map->size = map->rowSize * map->rowSize;
	map->uvScale = 1.0f;
	map->CreateMesh(map->rowSize);
	map->shader = RESOURCE->shaders.Load("5.Cube.hlsl");
	map->material = new Material();
    return map;
}
ID3D11ComputeShader* Terrain::computeShader = nullptr;
void Terrain::CreateStaticMember()
{
	ID3D10Blob* CsBlob;

	wstring path = L"../Shaders/ComputeShader.hlsl";

	DWORD flags = D3DCOMPILE_ENABLE_STRICTNESS | D3DCOMPILE_DEBUG;


	D3DCompileFromFile(path.c_str(), nullptr, D3D_COMPILE_STANDARD_FILE_INCLUDE,
		"CS", "cs_5_0", flags, 0, &CsBlob, nullptr);

	D3D->GetDevice()->CreateComputeShader(CsBlob->GetBufferPointer(), CsBlob->GetBufferSize(),
		nullptr, &computeShader);
}

void Terrain::DeleteStaticMember()
{
	SafeRelease(computeShader);
}

Terrain::Terrain()
{
}

Terrain::~Terrain()
{
	for (int i = 0; i < size; i++) 
		delete[] isThereFeature[i]; // 각 행에 대한 메모리 해제
	delete[] isThereFeature; // 전체 배열에 대한 메모리 해제
}


void Terrain::CreateStructuredBuffer()
{
	int triSize = (rowSize - 1) * (rowSize - 1) * 2;
	//삼각형 단위
	inputArray = new InputDesc[triSize];
	for (UINT i = 0; i < triSize; i++)
	{
		UINT index0 = mesh->indices[i * 3 + 0];
		UINT index1 = mesh->indices[i * 3 + 1];
		UINT index2 = mesh->indices[i * 3 + 2];

		inputArray[i].v0 = ((VertexTerrain*)(mesh->vertices))[index0].position;
		inputArray[i].v1 = ((VertexTerrain*)(mesh->vertices))[index1].position;
		inputArray[i].v2 = ((VertexTerrain*)(mesh->vertices))[index2].position;

		inputArray[i].index = i;
	}
	//삼각형 단위
	outputArray = new OutputDesc[triSize];



	//input
	{
		ID3D11Buffer* buffer;
		D3D11_BUFFER_DESC desc = {};
		desc.Usage = D3D11_USAGE_DEFAULT;
		desc.ByteWidth = sizeof(InputDesc) * triSize;
		desc.BindFlags = D3D11_BIND_SHADER_RESOURCE;
		desc.MiscFlags = D3D11_RESOURCE_MISC_BUFFER_STRUCTURED;
		desc.StructureByteStride = sizeof(InputDesc);

		D3D11_SUBRESOURCE_DATA initData = {};
		initData.pSysMem = inputArray;

		D3D->GetDevice()->CreateBuffer(&desc, &initData, &buffer);
		input = (ID3D11Resource*)buffer;


		D3D11_SHADER_RESOURCE_VIEW_DESC srvDesc = {};
		srvDesc.Format = DXGI_FORMAT_UNKNOWN;
		srvDesc.ViewDimension = D3D11_SRV_DIMENSION_BUFFEREX;
		srvDesc.BufferEx.FirstElement = 0;
		srvDesc.BufferEx.NumElements = triSize;
		//srv
		D3D->GetDevice()->CreateShaderResourceView(buffer, &srvDesc, &srv);

	}
	//output
	{
		ID3D11Buffer* buffer;
		D3D11_BUFFER_DESC desc = {};
		desc.Usage = D3D11_USAGE_DEFAULT;
		desc.ByteWidth = sizeof(OutputDesc) * triSize;
		desc.BindFlags = D3D11_BIND_UNORDERED_ACCESS;
		desc.MiscFlags = D3D11_RESOURCE_MISC_BUFFER_STRUCTURED;
		desc.StructureByteStride = sizeof(OutputDesc);

		D3D->GetDevice()->CreateBuffer(&desc, nullptr, &buffer);
		//ID3D11Resource
		output = (ID3D11Resource*)buffer;


		D3D11_UNORDERED_ACCESS_VIEW_DESC uavDesc = {};
		uavDesc.Format = DXGI_FORMAT_UNKNOWN;
		uavDesc.ViewDimension = D3D11_UAV_DIMENSION_BUFFER;
		uavDesc.Buffer.FirstElement = 0;
		uavDesc.Buffer.NumElements = triSize;
		//uav
		D3D->GetDevice()->CreateUnorderedAccessView(buffer, &uavDesc, &uav);
	}
	//result read
	{
		ID3D11Buffer* buffer;
		D3D11_BUFFER_DESC desc = {};
		((ID3D11Buffer*)output)->GetDesc(&desc);
		desc.Usage = D3D11_USAGE_STAGING;
		desc.BindFlags = 0;
		desc.MiscFlags = 0;
		desc.CPUAccessFlags = D3D11_CPU_ACCESS_READ;

		D3D->GetDevice()->CreateBuffer(&desc, nullptr, &buffer);

		result = (ID3D11Resource*)buffer;

	}
	{
		D3D11_BUFFER_DESC desc = { 0 };
		desc.Usage = D3D11_USAGE_DEFAULT;
		desc.ByteWidth = sizeof(RayDesc);
		desc.BindFlags = D3D11_BIND_CONSTANT_BUFFER;

		HRESULT hr = D3D->GetDevice()->CreateBuffer(&desc, NULL, &rayBuffer);
		assert(SUCCEEDED(hr));
	}
}

void Terrain::DeleteStructuredBuffer()
{
	SafeRelease(input);
	SafeRelease(srv);
	SafeRelease(output);
	SafeRelease(uav);
	SafeRelease(result);
	SafeRelease(rayBuffer);
	SafeDeleteArray(inputArray);
	SafeDeleteArray(outputArray);
}

void Terrain::CreateMesh(int   rowSize)
{
	this->rowSize = rowSize;
	UINT vertexCount = rowSize * rowSize;
	VertexType type = VertexType::TERRAIN;
	VertexTerrain* vertices = new VertexTerrain[rowSize * rowSize];
	//정점 갯수만큼 반복문
	float half = rowSize * 0.5f;

	// isThereFeature 배열 초기화
	Create2DArray(isThereFeature, rowSize);

	for (int i = 0; i < rowSize; i++)
	{
		for (int j = 0; j < rowSize; j++)
		{
			vertices[i * rowSize + j].position = Vector3(j - half, 0, -i + half);
			vertices[i * rowSize + j].normal = Vector3(0, 1, 0);
			vertices[i * rowSize + j].uv = Vector2(j / float(rowSize - 1), i / float(rowSize - 1));
			vertices[i * rowSize + j].weights = Vector4(1, 0, 0, 0);
			vertices[i * rowSize + j].color = Color(1, 1, 1, 1);
		}
	}

	UINT indexCount = (rowSize - 1) * (rowSize - 1) * 6;
	UINT* indices = new UINT[indexCount];

	//사각형 갯수만큼 반복문
	int idxCount = 0;
	for (int i = 0; i < (rowSize - 1); i++)      //세로
	{
		for (int j = 0; j < (rowSize - 1); j++)  //가로
		{
			int RectIdx = i * rowSize + j;

			indices[idxCount++] = i * rowSize + j + 0;
			indices[idxCount++] = i * rowSize + j + 1;
			indices[idxCount++] = i * rowSize + j + rowSize + 1;

			indices[idxCount++] = i * rowSize + j + 0;
			indices[idxCount++] = i * rowSize + j + rowSize + 1;
			indices[idxCount++] = i * rowSize + j + rowSize;
		}
	}
	SafeReset(mesh);
	mesh = make_shared<Mesh>(vertices, vertexCount, indices, indexCount, type);

}

void Terrain::LoadHeightRaw(string file)
{
	file = "../Assets/" + file;
	FILE* fp;
	//파일 열기
	fopen_s(&fp, file.c_str(), "rb");
	fseek(fp, 0, SEEK_END);
	size = ftell(fp);
	fseek(fp, 0, SEEK_SET);

	BYTE* Height = new BYTE[size];
	for (int i = 0; i < size; i++)
	{
		char c = fgetc(fp);
		Height[i] = c;
	}

	SafeReset(mesh);
	rowSize = (int)sqrt(size);
	CreateMesh(rowSize);

	for (int i = 0; i < rowSize; i++)
	{
		for (int j = 0; j < rowSize; j++)
		{
			VertexTerrain* vertices = (VertexTerrain*)mesh->vertices;
			float _y = Height[i * rowSize + j] * 0.1f;
			vertices[i * rowSize + j].position.y = _y;
			//vertices[i * rowSize + j].color = Color(1, 1, 1, 1);
		}
	}
	mesh->UpdateBuffer();
	delete[] Height;
}

void Terrain::LoadHeightImage(string file)
{
	ScratchImage* img = Texture::GetPixelData(file);

	//cout << "픽셀갯수:" << img->GetPixelsSize() << endl;
	//cout << "포맷:" << img->GetImages()[0].format << endl;
	//cout << "가로크기:" << img->GetImages()[0].width << endl;
	//cout << "세로크기:" << img->GetImages()[0].height << endl;
	//cout << "rowPitch:" << img->GetImages()[0].rowPitch << endl;
	//cout << "slicePitch:" << img->GetImages()[0].slicePitch << endl;

	SafeReset(mesh);
	rowSize = img->GetImages()[0].width;
	size = rowSize * rowSize;
	CreateMesh(rowSize);


	if (img->GetImages()[0].format == DXGI_FORMAT_R8_UNORM)
	{
		unsigned char* data = (unsigned char*)img->GetImages()[0].pixels;
		for (int i = 0; i < rowSize; i++)
		{
			for (int j = 0; j < rowSize; j++)
			{
				VertexTerrain* vertices = (VertexTerrain*)mesh->vertices;
				float _y = (float)data[(i * rowSize + j)] * 0.1f;
				vertices[i * rowSize + j].position.y = _y;
				//vertices[i * rowSize + j].color = Color(1, 1, 1, 1);

			}
		}
	}
	else if (img->GetImages()[0].format == DXGI_FORMAT_R16_UNORM)
	{
		unsigned short* data = (unsigned short*)img->GetImages()[0].pixels;
		for (int i = 0; i < rowSize; i++)
		{
			for (int j = 0; j < rowSize; j++)
			{
				VertexTerrain* vertices = (VertexTerrain*)mesh->vertices;
				float _y = (float)data[(i * rowSize + j)] * 0.01f;
				vertices[i * rowSize + j].position.y = _y;
				//vertices[i * rowSize + j].color = Color(1, 1, 1, 1);

			}
		}
	}
	/*if (img->GetImages()[0].format == DXGI_FORMAT_R32_UNORM)
	{


	}*/


	mesh->UpdateBuffer();
}

void Terrain::PerlinNoiseSea(siv::PerlinNoise perlin)
{
	float time = TIMER->GetWorldTime();
	double frequency = 0.1;  // 주파수 설정
	double amplitude = 1.1;  // 진폭 설정

	VertexTerrain* vertices = (VertexTerrain*)mesh->vertices;
	for (int i = 0; i < rowSize; i++)
	{
		for (int j = 0; j < rowSize; j++)
		{
			double x = i * frequency;
			double y = j * frequency;
			double z = time * 0.2;

			double noiseValueIsland = perlin.noise3D(x, y, z);

			vertices[i * rowSize + j].position.y = noiseValueIsland;
		}
	}

	UpdateNormal();
}

void Terrain::PerlinNoiseHeightMap()
{	
	SafeReset(mesh);
	size = rowSize * rowSize;
	CreateMesh(rowSize);

	// 난수 시드를 사용하여 펄린 노이즈 생성
	siv::PerlinNoise perlin(RANDOM->Int(0, 10000));	
	// 맵 크기에 따른 주파수 스케일 조정
	double frequencyScale{ 1.0 / rowSize * 2 };    

	VertexTerrain* vertices = (VertexTerrain*)mesh->vertices;
	for (int i = 0; i < rowSize; i++)
	{
		for (int j = 0; j < rowSize; j++)
		{
			double x = (double)i * frequencyScale;		// 펄린노이즈의 x좌표
			double y = (double)j * frequencyScale;		// 펄린노이즈의 y좌표
			double z = 0.5;								// 지형의 높이 변화에 영향

			double noiseValueIsland = IslandNoise(perlin, x, y, z, i, j);		// i, j는 정점의 인덱스

			// 최종 높이
			vertices[i * rowSize + j].position.y = noiseValueIsland;
		}
	}

	mesh->UpdateBuffer();
	UpdateNormal();
	UpdateColor();
	UpdateStructuredBuffer();
}

void Terrain::UpdateColor()
{
	// 높이에 따른 색상 정의
	auto GetColorForHeight = [](double height) -> Color 
		{
			Color sandColor(0.7608f, 0.6980f, 0.5020f);		// 모래색
			Color grassColor(0.0f, 0.5020f, 0.0f);			// 초록색

			// 높이에 따라 색상을 보간
			return Color::Lerp(sandColor, grassColor, height);
		};

	VertexTerrain* vertices = (VertexTerrain*)mesh->vertices;
	
	// 높이의 최소값과 최대값을 찾기 위한 변수
	double minHeight = 0;				// 최소 높이는 0으로 초기화 (0이하는 모래색)
	double maxHeight = DOUBLE_MIN;		// 최대값을 찾기위해 최소값 저장
	
	// 모든 정점을 순회하여 최대 높이를 찾음
	for (int i = 0; i < size; i++)
	{
		maxHeight = max(maxHeight, vertices[i].position.y);
	}

	// 모든 정점에 대해 색상을 계산하고 적용
	for (int i = 0; i < size; i++)
	{
		double height = vertices[i].position.y;
		// 높이를 0에서 1 사이의 값으로 정규화
		double normalizedHeight = height < 0.0 ? 0 : (height - minHeight) / (maxHeight - minHeight);
		vertices[i].color = GetColorForHeight(min(1.0f, normalizedHeight + 0.1f));
	}

	mesh->UpdateBuffer();
}

void Terrain::UpdateStructuredBuffer()
{
	DeleteStructuredBuffer();
	CreateStructuredBuffer();
}

void Terrain::UpdateNormal()
{
	for (int i = 0; i < (rowSize); i++)      //세로
	{
		for (int j = 0; j < (rowSize); j++)  //가로
		{
			VertexTerrain* vertices = (VertexTerrain*)mesh->vertices;
			vertices[i * rowSize + j].normal = Vector3(0, 0, 0);
		}
	}
	int idxCount = 0;
	for (int i = 0; i < (rowSize - 1); i++)      //세로
	{
		for (int j = 0; j < (rowSize - 1); j++)  //가로
		{
			int RectIdx = i * rowSize + j;
			UINT* indices = mesh->indices;
			VertexTerrain* vertices = (VertexTerrain*)mesh->vertices;

			int idx1 = indices[idxCount++];
			int idx2 = indices[idxCount++];
			int idx3 = indices[idxCount++];

			Vector3 v1 = vertices[idx1].position - vertices[idx2].position;
			Vector3 v2 = vertices[idx3].position - vertices[idx2].position;

			Vector3 cross = v2.Cross(v1);
			vertices[idx1].normal += cross;
			vertices[idx2].normal += cross;
			vertices[idx3].normal += cross;


			idx1 = indices[idxCount++];
			idx2 = indices[idxCount++];
			idx3 = indices[idxCount++];

			v1 = vertices[idx1].position - vertices[idx2].position;
			v2 = vertices[idx3].position - vertices[idx2].position;

			cross = v2.Cross(v1);
			vertices[idx1].normal += cross;
			vertices[idx2].normal += cross;
			vertices[idx3].normal += cross;
		}
	}


	mesh->UpdateBuffer();
}

void Terrain::RenderDetail()
{
	Actor::RenderDetail();
	if (ImGui::BeginTabBar("MyTabBar3"))
	{
		if (ImGui::BeginTabItem("Terrain"))
		{
			if (GUI->FileImGui("SaveAll", "SaveAll",
				".xml", "../Contents/GameObject"))
			{
				string path = ImGuiFileDialog::Instance()->GetCurrentPath();
			
				string file = ImGuiFileDialog::Instance()->GetCurrentFileName();
				//terrain.xml;
				size_t tok = file.find('.');
				file = file.substr(0, tok);
				


				Utility::Replace(&path, "\\", "/");
				if (path.find("/GameObject/") != -1)
				{
					size_t tok = path.find("/GameObject/") + 12;
					path = path.substr(tok, path.length())
						+ "/" + ImGuiFileDialog::Instance()->GetCurrentFileName();
				}
				else
				{
					path = ImGuiFileDialog::Instance()->GetCurrentFileName();
				}
			

				UpdateNormal();
				mesh->SaveFile(file + ".mesh");
				material->SaveFile(file + ".mtl");
				shader->LoadFile("5.Cube.hlsl");


				SaveFile(path);
			}


			if (ImGui::Button("UpdateStructuredBuffer"))
			{
				UpdateStructuredBuffer();
			}

			if (GUI->FileImGui("LoadHeightImage", "LoadHeightImage",
				".png,.bmp,.jpg,.jpeg", "../Contents/Texture"))
			{
				string imageFile;
				imageFile = ImGuiFileDialog::Instance()->GetCurrentFileName();
				LoadHeightImage(imageFile);

			}
			ImGui::SameLine();
			if (GUI->FileImGui("LoadHeightRaw", "LoadHeightRaw",
				".raw,.RAW", "../Assets"))
			{
				string imageFile;
				imageFile = ImGuiFileDialog::Instance()->GetCurrentFileName();
				LoadHeightRaw(imageFile);

			}
			if (ImGui::Button("UpdateNormal"))
			{
				UpdateNormal();
			}
			if (ImGui::SliderFloat("UvScale", &uvScale, 1, 100))
			{
				for (int i = 0; i < rowSize; i++)
				{
					for (int j = 0; j < rowSize; j++)
					{
						VertexTerrain* vertices = (VertexTerrain*)mesh->vertices;
						vertices[i * rowSize + j].uv = Vector2(j / float(rowSize - 1), i / float(rowSize - 1));
						vertices[i * rowSize + j].uv *= uvScale;
					}
				}
				mesh->UpdateBuffer();
			}







			int last = rowSize;
			if (ImGui::SliderInt("rowSize", &rowSize, 2, 1000))
			{
				UINT vertexCount = rowSize * rowSize;
				VertexType type = VertexType::TERRAIN;
				VertexTerrain* vertices = new VertexTerrain[rowSize * rowSize];


				float half = rowSize * 0.5f;
				//정점 갯수만큼 반복문
				for (int i = 0; i < rowSize; i++)
				{
					for (int j = 0; j < rowSize; j++)
					{
						vertices[i * rowSize + j].position = Vector3(j - half, 0, -i + half);
						vertices[i * rowSize + j].normal = Vector3(0, 1, 0);
						vertices[i * rowSize + j].uv = Vector2(j / float(rowSize - 1), i / float(rowSize - 1));
					}
				}

				UINT indexCount = (rowSize - 1) * (rowSize - 1) * 6;
				UINT* indices = new UINT[indexCount];

				//사각형 갯수만큼 반복문
				int idxCount = 0;
				for (int i = 0; i < (rowSize - 1); i++)      //세로
				{
					for (int j = 0; j < (rowSize - 1); j++)  //가로
					{
						int RectIdx = i * rowSize + j;

						indices[idxCount] = i * rowSize + j + 0; idxCount++;
						indices[idxCount] = i * rowSize + j + 1; idxCount++;
						indices[idxCount] = i * rowSize + j + rowSize + 1; idxCount++;

						indices[idxCount] = i * rowSize + j + 0; idxCount++;
						indices[idxCount] = i * rowSize + j + rowSize + 1; idxCount++;
						indices[idxCount] = i * rowSize + j + rowSize; idxCount++;
					}
				}
				int Min = min(last, rowSize);

			
				for (int i = 0; i < Min; i++)
				{
					for (int j = 0; j < Min; j++)
					{
						VertexTerrain* ver = (VertexTerrain*)mesh->vertices;
						vertices[i * rowSize + j].position.y = ver[i * last + j].position.y;
						vertices[i * rowSize + j].normal = ver[i * last + j].normal;
						vertices[i * rowSize + j].uv = ver[i * last + j].uv;
					}
				}
				mesh.reset();
				mesh = make_shared<Mesh>(vertices, vertexCount, indices, indexCount, type);

			}



			ImGui::EndTabItem();
		}
		ImGui::EndTabBar();
	}
}

double Terrain::IslandNoise(siv::PerlinNoise& perlin, double x, double y, double z, int i, int j)
{
	// 펄린 노이즈 값을 계산
	double noiseValue = perlin.noise3D(x * baseFrequency, y * baseFrequency, z);

	// 지형의 중앙으로부터의 거리를 계산
	double distanceToCenter = sqrt(pow(i - rowSize / 2.0, 2) + pow(j - rowSize / 2.0, 2));
	// 지형 중앙부터 가장자리까지의 최대 거리를 계산
	double maxDistance = sqrt(2) * (rowSize / 2.0);
	// 높이 계수를 계산하여 지형의 중앙 부분이 높아지도록 함
	double heightFactor = pow((1.0 - (distanceToCenter / maxDistance)), 2) * 2.0;
	// 각 지점에서 가장자리까지의 최소 거리를 계산
	double minEdgeDistance = min(min(i, rowSize - 1 - i), min(j, rowSize - 1 - j));
	// 가장자리 계수를 계산하여 지형의 가장자리가 낮아지도록 함
	double edgeFactor = amplitude * pow((maxDistance - minEdgeDistance) / maxDistance, edgeSteepness * 2);
	// 중앙과의 거리에 따라 선형적으로 높이 가중치 조정 (distanceFactor가 5라면, 중앙에서 +5 ~ 최대 거리에서 -5)
	double centralDistanceFactor = distanceFactor - (distanceFactor * 2) * (distanceToCenter / maxDistance);

	return (noiseValue * amplitude * heightFactor - edgeFactor) + centralDistanceFactor;
}

void Terrain::ChangeColor(int index, float LerpValue)
{
	// 정점의 현재 색과 모래색을 보간한 색을 계산
	auto GetLerpColor = [](Color color, float LerpValue) -> Color
		{
			Color currentColor(color.x, color.y, color.y);	// 현재 정점 색
			Color sandColor(0.7608f, 0.6980f, 0.5020f);		// 모래색

			// 높이에 따라 색상을 보간
			return Color::Lerp(currentColor, sandColor, LerpValue);
		};

	// 해당 정점에 색을 적용
	VertexTerrain* vertices = (VertexTerrain*)mesh->vertices;
	vertices[index].color = GetLerpColor(vertices[index].color, LerpValue);
}

bool Terrain::ComputePicking(Ray WRay, OUT Vector3& HitPoint)
{
	int triSize = (rowSize - 1) * (rowSize - 1) * 2;
	//쉐이더부터 준비
	D3D->GetDC()->CSSetShader(computeShader, 0, 0);

	//raybuffer binding
	ray.position = WRay.position;
	ray.direction = WRay.direction;
	ray.size = (float)triSize;//삼각형갯수
	Matrix inverse = W.Invert();
	ray.direction = Vector3::TransformNormal(ray.direction, inverse);
	ray.direction.Normalize();
	ray.position = Vector3::Transform(ray.position, inverse);

	//트랜스폼한 Ray를 상수버퍼로 바인딩
	D3D->GetDC()->UpdateSubresource(rayBuffer, 0, NULL, &ray, 0, 0);

	D3D->GetDC()->CSSetConstantBuffers(0, 1, &rayBuffer);

	//input binding
	D3D->GetDC()->CSSetShaderResources(0, 1, &srv);
	//output binding
	D3D->GetDC()->CSSetUnorderedAccessViews(0, 1, &uav, nullptr);

	//멀티스레딩
	//shader 실행
	//올림
	UINT x = (UINT)ceil((float)triSize / 1024.0f);
	D3D->GetDC()->Dispatch(x, 1, 1);

	//동기화

	//gpu -> cpu 복사
	D3D->GetDC()->CopyResource(result, output);

	D3D11_MAPPED_SUBRESOURCE subResource;

	D3D->GetDC()->Map(result, 0, D3D11_MAP_READ, 0, &subResource);
	memcpy(outputArray, subResource.pData, sizeof(OutputDesc) * triSize);
	D3D->GetDC()->Unmap(result, 0);

	float minDistance = FLT_MAX;
	int minIndex = -1;
	for (int i = 0; i < triSize; i++)
	{
		OutputDesc temp = outputArray[i];
		if (temp.picked)
		{
			if (minDistance > temp.distance)
			{
				minDistance = temp.distance;
				minIndex = i;
			}
		}
	}
	if (minIndex >= 0)
	{
		HitPoint = ray.position + ray.direction
			* minDistance;
		HitPoint = Vector3::Transform(HitPoint, W);
		return true;
	}

	return false;
}
