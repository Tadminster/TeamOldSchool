#include "framework.h"

LightManager::LightManager()
{
	{
		D3D11_BUFFER_DESC desc = { 0 };
		desc.ByteWidth = sizeof(DirLight);
		desc.Usage = D3D11_USAGE_DYNAMIC;
		desc.BindFlags = D3D11_BIND_CONSTANT_BUFFER;//상수버퍼
		desc.CPUAccessFlags = D3D11_CPU_ACCESS_WRITE;
		desc.MiscFlags = 0;
		desc.StructureByteStride = 0;
		HRESULT hr = D3D->GetDevice()->CreateBuffer(&desc, NULL, &dirLightBuffer);
		assert(SUCCEEDED(hr));
		D3D->GetDC()->PSSetConstantBuffers(2, 1, &dirLightBuffer);
	}

	{
		D3D11_BUFFER_DESC desc = { 0 };
		desc.ByteWidth = sizeof(LightBuffer) * MAX_LIGHT;
		desc.Usage = D3D11_USAGE_DYNAMIC;
		desc.BindFlags = D3D11_BIND_CONSTANT_BUFFER;//상수버퍼
		desc.CPUAccessFlags = D3D11_CPU_ACCESS_WRITE;
		desc.MiscFlags = 0;
		desc.StructureByteStride = 0;
		HRESULT hr = D3D->GetDevice()->CreateBuffer(&desc, NULL, &lightBuffer);
		assert(SUCCEEDED(hr));
		D3D->GetDC()->PSSetConstantBuffers(3, 1, &lightBuffer);
	}

	light[0].size = 0;
	
}

LightManager::~LightManager()
{
	SafeRelease(dirLightBuffer);
	SafeRelease(lightBuffer);
}

void LightManager::Set()
{

	{
		D3D11_MAPPED_SUBRESOURCE mappedResource;
		D3D->GetDC()->Map(dirLightBuffer, 0, D3D11_MAP_WRITE_DISCARD, 0, &mappedResource);
		memcpy_s(mappedResource.pData, sizeof(DirLight), &dirLight, sizeof(DirLight));
		D3D->GetDC()->Unmap(dirLightBuffer, 0);
	}
	D3D->GetDC()->PSSetConstantBuffers(2, 1, &dirLightBuffer);
	{
		D3D11_MAPPED_SUBRESOURCE mappedResource;
		D3D->GetDC()->Map(lightBuffer, 0, D3D11_MAP_WRITE_DISCARD, 0, &mappedResource);
		memcpy_s(mappedResource.pData, sizeof(LightBuffer) * MAX_LIGHT, light, sizeof(LightBuffer) * MAX_LIGHT);
		D3D->GetDC()->Unmap(lightBuffer, 0);
	}
	D3D->GetDC()->PSSetConstantBuffers(3, 1, &lightBuffer);
}

void LightManager::RenderDetail()
{
	ImGui::SliderFloat3("dirLight", (float*)(&dirLight.direction), -1, 1);
	ImGui::ColorEdit3("dirColor", (float*)(&dirLight.color));
}

void LightManager::SetSize()
{
	int max = -1;
	for (int i = 0; i < MAX_LIGHT; i++)
	{
		if (LIGHT->light[i].isActive)
		{
			if (i > max)
			{
				max = i;
			}
		}
	}
	light[0].size = max + 1;
}

Light::~Light()
{
	light->isActive = false;
	LIGHT->SetSize();
}

Light* Light::Create(string name, int type)
{
	Light* temp = nullptr;
	//16개 생성 제한
	for (int i = 0; i < MAX_LIGHT; i++)
	{
		if (not LIGHT->light[i].isActive)
		{
			temp = new Light();
			temp->name = name;
			LIGHT->light[i].isActive = true;
			LIGHT->light[i].lightType = type;
			temp->light = &LIGHT->light[i];
			LIGHT->SetSize();
			temp->mesh = RESOURCE->meshes.Load("1.SphereCollider.mesh");
			temp->shader = RESOURCE->shaders.Load("1.Collider.hlsl");
			temp->type = ObType::Light;
			break;
		}
	}

	return temp;
}

void Light::Release()
{
	Actor::Release();
}

void Light::Update()
{
	scale.z = scale.y = scale.x = light->radius;
	Actor::Update();
	light->position = GetWorldPos();
	light->direction = Vector3::TransformNormal(GetForward(), W);

}

void Light::RenderDetail()
{
	Actor::RenderDetail();
	if (ImGui::BeginTabBar("MyTabBar3"))
	{
		if (ImGui::BeginTabItem("Light"))
		{
			ImGui::SliderInt("Type", &light->lightType, 0, 1);
			ImGui::ColorEdit3("Color", (float*)(&light->color));
			ImGui::SliderFloat("Range", &light->radius, 0, 200);

			if (light->lightType == (int)LightType::SPOT)
			{
				ImGui::SliderFloat3("Dir", (float*)(&light->direction), -1, 1);
				ImGui::SliderFloat("Outer", &light->outer, 0.0f, 90.0f);
				ImGui::SliderFloat("Inner", &light->inner, 0.0f, 90.0f);
			}

			ImGui::EndTabItem();
		}
		ImGui::EndTabBar();
	}
}

void LightManager::UpdateDirection()
{
	if (currentTime >= dayCycleLength)
	{
		addTime = false;
		cout << TIMER->GetWorldTime() << endl;
	}
	else if (currentTime <= 0.0f) 
	{
		addTime = true;
		cout << TIMER->GetWorldTime() << endl;
	}
	
	if (addTime) currentTime = min(currentTime + 1.0f * DELTA, dayCycleLength);
	else currentTime = max(currentTime - 1.0f * DELTA, 0.0f);
	
	//0~1 낮밤 비율
	timeRatio = currentTime / dayCycleLength;

	dirLight.direction.y = cos(timeRatio  * PI_2);
	dirLight.direction.z = sin(timeRatio  * PI_2);

	// 버퍼 업데이트
	D3D11_MAPPED_SUBRESOURCE mappedResource;
	D3D->GetDC()->Map(dirLightBuffer, 0, D3D11_MAP_WRITE_DISCARD, 0, &mappedResource);
	memcpy_s(mappedResource.pData, sizeof(DirLight), &dirLight, sizeof(DirLight));
	D3D->GetDC()->Unmap(dirLightBuffer, 0);
}