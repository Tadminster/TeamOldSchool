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

    //copy용
    ID3D11Resource*             result;

    //ray
    RayDesc                     ray;
    ID3D11Buffer*               rayBuffer;

public:
	int				size;
	float			uvScale;
	int				rowSize;
    //CS            컴퓨트 쉐이더로 피킹할때만 만들기
    void            CreateStructuredBuffer();
    void            DeleteStructuredBuffer();

	void			CreateMesh(int   rowSize);
	void			LoadHeightRaw(string file);
	void			LoadHeightImage(string file);
    void            UpdateColor();
	void			UpdateStructuredBuffer();
	void			UpdateNormal();
	void	        RenderDetail();

    bool            ComputePicking(Ray WRay, OUT Vector3& HitPoint);

private:            // 펄린노이즈 지형생성
    double          baseFrequency   { 5.0 };            // 기본 주파수
    double          amplitude       { 10.0 };           // 진폭
    double          edgeSteepness   { 5.0 };            // 가장자리 경사의 가파름 조절
    double          distanceFactor  { 15 };             // 중앙과의 거리에 따른 높이 계수

public:
    bool**          isThereFeature{ nullptr };          // 지형에 feature가 있는지 없는지를 저장할 배열

public:
    void            PerlinNoiseHeightMap();
    void            PerlinNoiseSea(siv::PerlinNoise perin);
    double          IslandNoise(siv::PerlinNoise& perlin, double x, double y, double z, int i, int j);
    void            ChangeColor(int index, float LerpValue);
};

template<typename T>
inline void Create2DArray(T**& array, int size)
{
    if (array)
    {
        for (int i = 0; i < size; i++) {
            delete[] array[i];
        }
        delete[] array;
	}

	array = new T*[size];
    for (int i = 0; i < size; i++)
    {
		array[i] = new T[size];
	}

    for (int i = 0; i < size; i++)
    {
        for (int j = 0; j < size; j++) {
			array[i][j] = 0;
		}
	}
}
