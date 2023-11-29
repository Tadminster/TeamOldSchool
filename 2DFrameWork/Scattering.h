#pragma once
class Scattering 
{
    struct ScatteringBuffer
    {
        Vector3 waveLength = Vector3(0.65f, 0.57f, 0.475f);
        int sampleCount = 5;

        Vector3 invWaveLength;
        float padding;

        Vector3 waveLengthMie;
        float padding2;
        ScatteringBuffer()
        {
            invWaveLength.x = 1.0f / pow(waveLength.x, 4.0f);
            invWaveLength.y = 1.0f / pow(waveLength.y, 4.0f);
            invWaveLength.z = 1.0f / pow(waveLength.z, 4.0f);
            waveLength.x = pow(waveLength.x, 0.84f);
            waveLength.y = pow(waveLength.y, 0.84f);
            waveLength.z = pow(waveLength.z, 0.84f);
        }
    }data;


private:
    RenderTarget* rayleighTarget;
    RenderTarget* mieTarget;

    RenderTarget* rtvs[2];
    ID3D11ShaderResourceView* srvs[2];
    ID3D11Buffer* scatteringBuffer;

    shared_ptr<Mesh> rect;
    shared_ptr<Shader> pass1Shader;

    shared_ptr<Mesh> sphere;
    shared_ptr<Shader> pass2Shader;
    shared_ptr<Texture> pass2Diffuse;
    shared_ptr<Texture> pass2Diffuse2;

public:
    Scattering(UINT width = App.GetWidth(),
        UINT height = App.GetHeight());

    void DrawPass1(Color clear = Color(1, 1, 1, 1));
    void DrawPass2();

    void RenderDetail();
};

