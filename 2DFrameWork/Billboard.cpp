#include "framework.h"

Billboard* Billboard::Create(string name)
{
    Billboard* temp = new Billboard();
    temp->name = name;
    temp->type = ObType::Billboard;
    temp->mesh = make_shared<Mesh>();
    temp->mesh->LoadFile("7.Billboard.mesh");
    temp->shader = RESOURCE->shaders.Load("7.Billboard.hlsl");
    temp->shader->LoadGeometry();

    return temp;
}

void Billboard::Release()
{
}

void Billboard::Update()
{
    Actor::Update();
    VertexBillboard* vertex = (VertexBillboard*)mesh->vertices;
    vertex[0].mov.x = rotation.x;
    vertex[0].mov.y = rotation.y;

    vertex[0].size.x = scale.x;
    vertex[0].size.y = scale.y;
    mesh->UpdateBuffer();
}

void Billboard::Render(shared_ptr<Shader> pShader)
{
    //���� ����
    //DEPTH->Set(false);
    //������ �ѱ�
    BLEND->Set(true);
    Actor::Render(pShader);
    //���������
    BLEND->Set(false);
    //���� �ѱ�
    //DEPTH->Set(true);
}

void Billboard::DepthRender(shared_ptr<Shader> pShader)
{
    //���� ����
    DEPTH->Set(false);
    //������ �ѱ�
    BLEND->Set(true);
    Actor::Render(pShader);
    //���������
    BLEND->Set(false);
    //���� �ѱ�
    DEPTH->Set(true);
}

void Billboard::RenderDetail()
{
    Actor::RenderDetail();
    if (ImGui::BeginTabBar("MyTabBar3"))
    {
        if (ImGui::BeginTabItem("Billboard"))
        {
            ImGui::DragFloat2("mov", (float*)&rotation, -100.0f, 100.0f);
            ImGui::DragFloat2("size", (float*)&scale, 0.001f, 100.0f);

            ImGui::EndTabItem();
        }
        ImGui::EndTabBar();
    }

    if (ImGui::Button("Load Geometry"))
    {
        if (this->shader) this->shader->LoadGeometry();
    };
}
