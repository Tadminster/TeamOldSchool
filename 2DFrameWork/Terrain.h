#pragma once
#include "PerlinNoise.hpp"
class Terrain : public Actor
{
    struct InputDesc
    {
        UINT        index;
        Vector3     v0, v1, v2;
    };
    struct OutputDesc
    {
        int         picked;
        float       u, v, distance;
    };
    struct RayDesc
    {
        Vector3     position;
        float       size;
        Vector3     direction;
        float       padding;
    };
	static ID3D11ComputeShader* computeShader;

public:
	static Terrain* Create(string name = "Terrain");
    static void		CreateStaticMember();
    static void		DeleteStaticMember();

protected:
	Terrain();
	~Terrain();

private:
    //compute Input
    InputDesc*                  inputArray;
    ID3D11Resource*             input;
    ID3D11ShaderResourceView*   srv         { nullptr };    // Read Only

    //compute Output
    OutputDesc*                 outputArray;
    ID3D11Resource*             output;
    ID3D11UnorderedAccessView*  uav;                        // Read and Write

    //copy��
    ID3D11Resource*             result;
    //ray
    RayDesc                     ray;
    ID3D11Buffer*               rayBuffer;

public:
	int				size;
	float			uvScale;
	int				rowSize;
    //CS            ��ǻƮ ���̴��� ��ŷ�Ҷ��� �����
    void            CreateStructuredBuffer();
    void            DeleteStructuredBuffer();

	void			CreateMesh(int   rowSize);
	void			LoadHeightRaw(string file);
	void			LoadHeightImage(string file);
    void            UpdateColor();
	void			UpdateStructuredBuffer();
	void			UpdateNormal();
	void	        RenderDetail();

    bool            ComPutePicking(Ray WRay, OUT Vector3& HitPoint);

private:            // �޸������� ��������
    double          baseFrequency   { 5.0 };            // �⺻ ���ļ�
    double          amplitude       { 10.0 };           // ����
    double          edgeSteepness   { 5.0 };            // �����ڸ� ����� ���ĸ� ����
    double          distanceFactor  { 20 };             // �߾Ӱ��� �Ÿ��� ���� ���� ���

public:
    void            PerlinNoiseHeightMap();
    double          IslandNoise(siv::PerlinNoise& perlin, double x, double y, double z, int i, int j);
    void            ChangeColor(int index, float LerpValue);
};

