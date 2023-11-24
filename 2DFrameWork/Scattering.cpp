#include "framework.h"

Scattering::Scattering(UINT width, UINT height)
{
    rayleighTarget = new RenderTarget(width, height);
    mieTarget = new RenderTarget(width, height);

    rtvs[0] = rayleighTarget;
    rtvs[1] = mieTarget;

    srvs[0] = rayleighTarget->rgbResource;
    srvs[1] = mieTarget->rgbResource;

    {
        D3D11_BUFFER_DESC desc = { 0 };
        desc.ByteWidth = sizeof(ScatteringBuffer);
        desc.Usage = D3D11_USAGE_DYNAMIC;
        desc.BindFlags = D3D11_BIND_CONSTANT_BUFFER;//상수버퍼
        desc.CPUAccessFlags = D3D11_CPU_ACCESS_WRITE;
        desc.MiscFlags = 0;
        desc.StructureByteStride = 0;
        HRESULT hr = D3D->GetDevice()->CreateBuffer(&desc, NULL, &scatteringBuffer);
        assert(SUCCEEDED(hr));
    }

    rect = RESOURCE->meshes.Load("6.UI.mesh");
    sphere = RESOURCE->meshes.Load("6.Scattering.mesh");
    pass1Shader = RESOURCE->shaders.Load("6.ScatteringTarget.hlsl");
    pass2Shader = RESOURCE->shaders.Load("6.Scattering.hlsl");
    pass2Diffuse = RESOURCE->textures.Load("Space.png");
}

void Scattering::DrawPass1(Color clear)
{
    vector<ID3D11RenderTargetView*> vecRtvs;

    for (int i = 0; i < 2; i++)
    {
        vecRtvs.push_back(rtvs[i]->rgbTarget);
        D3D->GetDC()->ClearRenderTargetView(vecRtvs.back(), (float*)&clear);
    }
    D3D->GetDC()->ClearDepthStencilView(rayleighTarget->depthTarget, D3D11_CLEAR_DEPTH, 1.0f, 0);

    D3D->GetDC()->OMSetRenderTargets(2, vecRtvs.data(), rayleighTarget->depthTarget);

    {
        D3D11_MAPPED_SUBRESOURCE mappedResource;
        D3D->GetDC()->Map(scatteringBuffer, 0, D3D11_MAP_WRITE_DISCARD, 0, &mappedResource);
        memcpy_s(mappedResource.pData, sizeof(ScatteringBuffer), &data, sizeof(ScatteringBuffer));
        D3D->GetDC()->Unmap(scatteringBuffer, 0);
        D3D->GetDC()->PSSetConstantBuffers(10, 1, &scatteringBuffer);
    }

    rect->Set();
    pass1Shader->Set();
    rect->DrawCall();
}

void Scattering::DrawPass2()
{
    sphere->Set();
    pass2Shader->Set();

    D3D->GetDC()->PSSetShaderResources(10, 1, &srvs[0]);
    D3D->GetDC()->PSSetShaderResources(11, 1, &srvs[1]);
    pass2Diffuse->Set(1);
    DEPTH->Set(false);
    sphere->DrawCall();
    DEPTH->Set(true);
}

void Scattering::RenderDetail()
{
    ImGui::SliderInt("SampleCount", &data.sampleCount, 1, 50);
    ImVec2 size(400, 400);
    ImGui::Image((void*)rayleighTarget->rgbResource, size);
    ImGui::Image((void*)mieTarget->rgbResource, size);

}