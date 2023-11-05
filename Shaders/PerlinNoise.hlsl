// 3차원 Perlin Noise를 위한 fade 함수
/*
    t * t * t * (t * (t * 6 - 15) + 10) 은 5차 폴리노미얼(다항식). 
    이 폴리노미얼은 0과 1에서 두 번의 미분이 가능하도록 설계됨. 
    즉, 이 점에서 함수의 기울기가 0이 됨. 이 특성 때문에, fade 함수는 
    Perlin Noise의 격자점에서 값의 변화가 급격하게 발생하는 것을 방지하고, 결과적으로 더 부드러운 전환을 만듬.
    6, 15, 10은 이 다항식이 0과 1에서 부드러운 곡선을 형성하도록 하기 위한 특정 계수
*/
float fade(float t)
{
    return t * t * t * (t * (t * 6 - 15) + 10);
}


// 선형 보간 함수
float lerp(float a, float b, float t)
{
    return a + t * (b - a);
}


// 그래디언트 계산 함수
/*
    래디언트(방향성을 가진 벡터)를 계산하는 데 사용. 
    이 함수는 특정 격자점의 해시 값을 기반으로 해당 점에서의 그래디언트 벡터를 생성. 
    이러한 그래디언트 벡터는 나중에 보간을 통해 최종 노이즈 값을 계산할 때 사용.
*/
float grad(int hash, float x, float y, float z)
{
    int h = hash & 15;
    float u = h < 8 ? x : y;
    float v = h < 4 ? y : h == 12 || h == 14 ? x : z;
    return ((h & 1) == 0 ? u : -u) + ((h & 2) == 0 ? v : -v);
}

// 3D Perlin Noise 값을 계산하는 주 함수
float perlin3D(float3 position)
{
    return noise(position);
}