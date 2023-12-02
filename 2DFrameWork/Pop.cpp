#include "framework.h"
ID3D11Buffer* Pop::PopBuffer = nullptr;
ID3D11Buffer* Pop::PopPsBuffer = nullptr;
void Pop::CreateStaticMember()
{
	{
		D3D11_BUFFER_DESC desc = { 0 };
		desc.ByteWidth = sizeof(POP_DESC);
		desc.Usage = D3D11_USAGE_DYNAMIC;
		desc.BindFlags = D3D11_BIND_CONSTANT_BUFFER;//상수버퍼
		desc.CPUAccessFlags = D3D11_CPU_ACCESS_WRITE;
		desc.MiscFlags = 0;
		desc.StructureByteStride = 0;
		HRESULT hr = D3D->GetDevice()->CreateBuffer(&desc, NULL, &PopBuffer);
		assert(SUCCEEDED(hr));
	}

	{
		D3D11_BUFFER_DESC desc = { 0 };
		desc.ByteWidth = sizeof(POP_PS_DESC);
		desc.Usage = D3D11_USAGE_DYNAMIC;
		desc.BindFlags = D3D11_BIND_CONSTANT_BUFFER;//상수버퍼
		desc.CPUAccessFlags = D3D11_CPU_ACCESS_WRITE;
		desc.MiscFlags = 0;
		desc.StructureByteStride = 0;
		HRESULT hr = D3D->GetDevice()->CreateBuffer(&desc, NULL, &PopPsBuffer);
		assert(SUCCEEDED(hr));
	}
}

void Pop::DeleteStaticMember()
{
	SafeRelease(PopBuffer);
}

Pop* Pop::Create(string name)
{
	Pop* temp = new Pop();
	temp->name = name;
	temp->mesh = make_shared<Mesh>();
	temp->mesh->LoadFile("8.Billboard.mesh");
	temp->shader = RESOURCE->shaders.Load("8.Pop.hlsl");
	temp->shader->LoadGeometry();
	temp->type = ObType::Pop;
	return temp;
}

void Pop::Render()
{
	desc.duration = duration;
	//재생을 시작한 시간
	desc.time = playTime;
	{
		D3D11_MAPPED_SUBRESOURCE mappedResource;
		D3D->GetDC()->Map(PopBuffer, 0, D3D11_MAP_WRITE_DISCARD, 0, &mappedResource);
		memcpy_s(mappedResource.pData, sizeof(POP_DESC), &desc,
			sizeof(POP_DESC));
		D3D->GetDC()->Unmap(PopBuffer, 0);
		D3D->GetDC()->VSSetConstantBuffers(10, 1, &PopBuffer);
	}

	{
		D3D11_MAPPED_SUBRESOURCE mappedResource;
		D3D->GetDC()->Map(PopPsBuffer, 0, D3D11_MAP_WRITE_DISCARD, 0, &mappedResource);
		memcpy_s(mappedResource.pData, sizeof(POP_PS_DESC), &desc2,
			sizeof(POP_PS_DESC));
		D3D->GetDC()->Unmap(PopPsBuffer, 0);
		D3D->GetDC()->PSSetConstantBuffers(10, 1, &PopPsBuffer);
	}
	if (isPlaying)
		Actor::Render();
}

void Pop::Update()
{
	Particle::UpdateParticle();
	Actor::Update();
}

void Pop::Reset()
{
	delete[](VertexPSV*)mesh->vertices;
	delete[] mesh->indices;
	mesh->vertices = new VertexPSV[particleCount];
	mesh->indices = new UINT[particleCount];
	mesh->vertexCount = particleCount;
	mesh->indexCount = particleCount;

	Vector2 scale = Vector2(0, 0);

	for (UINT i = 0; i < particleCount; i++)
	{
		//파티클의 크기
		/*scale.x = max(0.05f,this->scale.x+ RANDOM->Float(-randomSize.x, randomSize.x));
		scale.y = max(0.05f,this->scale.y+ RANDOM->Float(-randomSize.y, randomSize.y));*/
		scale.x =	this->scale.x;
		scale.y =	this->scale.y;

		//위치
		Vector3 position = Vector3(0, 0, 0);
		Vector3 randomPos = Vector3(RANDOM->Float(0, randomPosition.x), RANDOM->Float(0, randomPosition.y), RANDOM->Float(0, randomPosition.z));

		//방향벡터 Right
		Vector3 velocity = Vector3(1, 0, 0);

		//임의의 회전된 3개축
		Vector3 rot;
		rot.y = RANDOM->Float(0.0f, PI * 2.0f);
		rot.x = RANDOM->Float(0.0f, PI * 2.0f);
		rot.z = RANDOM->Float(0.0f, PI * 2.0f);
		//임의의 회전행렬
		Matrix matRot = Matrix::CreateFromYawPitchRoll(rot.y, rot.x, rot.z);
		// v = v * R
		velocity = Vector3::TransformNormal(velocity, matRot);
		velocity *= velocityScalar;


		//내가 방향벡터를 3개축을 랜덤값으로 회전시켜 잡는다.
		((VertexPSV*)mesh->vertices)[i].velocity = velocity;
		((VertexPSV*)mesh->vertices)[i].position = position + randomPos;
		((VertexPSV*)mesh->vertices)[i].size = scale;
		mesh->indices[i] = i;
	}
	SafeRelease(mesh->vertexBuffer);
	SafeRelease(mesh->indexBuffer);

	//CreateVertexBuffer
	{
		D3D11_BUFFER_DESC desc;
		desc = { 0 };
		desc.Usage = D3D11_USAGE_DEFAULT;
		desc.ByteWidth = sizeof(VertexPSV) * particleCount;
		desc.BindFlags = D3D11_BIND_VERTEX_BUFFER;

		D3D11_SUBRESOURCE_DATA data = { 0 };
		data.pSysMem = mesh->vertices;

		HRESULT hr = D3D->GetDevice()->CreateBuffer(&desc, &data, &mesh->vertexBuffer);
		assert(SUCCEEDED(hr));
	}

	//Create Index Buffer
	{
		D3D11_BUFFER_DESC desc;
		ZeroMemory(&desc, sizeof(D3D11_BUFFER_DESC));
		desc.ByteWidth = sizeof(UINT) * particleCount;
		desc.BindFlags = D3D11_BIND_INDEX_BUFFER;

		D3D11_SUBRESOURCE_DATA data = { 0 };
		data.pSysMem = mesh->indices;

		HRESULT hr = D3D->GetDevice()->CreateBuffer(&desc, &data, &mesh->indexBuffer);
		assert(SUCCEEDED(hr));
	}
}

void Pop::Play()
{
	Reset();
	Particle::Play();
}

void Pop::Stop()
{
	Particle::Stop();

}


void Pop::RenderDetail()
{
	Actor::RenderDetail();
	if (ImGui::BeginTabBar("MyTabBar3"))
	{
		if (ImGui::BeginTabItem("Pop"))
		{
			Particle::Gui();
			ImGui::DragFloat("gravity", &desc.gravity, 1.0f, -100.0f, 100.0f);
			ImGui::DragFloat("velocityScalar", &velocityScalar, 1.0f, 0.0f, 1000.0f);
			ImGui::DragFloat2("particleSize", (float*)&scale, 0.5f, 0, 100);
			ImGui::DragFloat2("particleRandomSize", (float*)&randomSize, 0.5f, 0, 100);
			ImGui::DragFloat3("particleRandomPos", (float*)&randomPosition, 0.5f, 0, 100);
			ImGui::DragInt("particleCount", &particleCount, 1, 1, 100);

			if (ImGui::Button("Reset"))
			{
				Reset();
			}
			ImGui::EndTabItem();
		}
		ImGui::EndTabBar();
	}
}

