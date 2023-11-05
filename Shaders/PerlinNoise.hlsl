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

    int h = hash & 15;: 해시 값 hash 에 비트 AND 연산을 적용하여 하위 4비트를 추출합니다. 
    이는 hash 값을 0에서 15 사이의 값으로 제한합니다. & 15 연산은 & 0x0F와 동일하며, 
    이는 16진수에서의 F는 2진수로 1111이므로 하위 4비트만을 선택하는 것입니다.

    float u = h < 8 ? x : y;: h 값에 따라 u 변수에 x 또는 y 값을 할당합니다. 
    만약 h 가 8보다 작으면 u는 x를, 그렇지 않으면 y를 가집니다. 이는 그래디언트 벡터의 첫 번째 성분을 결정합니다.

    float v = h < 4 ? y : h == 12 || h == 14 ? x : z;: v는 h의 값에 따라 y, x, 또는 z 중 하나를 할당받습니다. 
    이는 그래디언트 벡터의 두 번째 성분을 결정하며, h 값에 따라 다양한 경우를 처리합니다.

    return ((h & 1) == 0 ? u : -u) + ((h & 2) == 0 ? v : -v);: 마지막으로, u와 v의 부호를 h의 하위 두 비트에 따라 결정합니다. 
    h & 1은 h의 가장 하위 비트를 확인하고, h & 2는 그 다음 비트를 확인합니다. 
    이 비트들이 0이면 각각 u와 v의 값을 그대로 사용하고, 1이면 해당 값의 부호를 반전시킵니다.
*/
float grad(int hash, float x, float y, float z)
{
    int h = hash & 15;
    float u = h < 8 ? x : y;
    float v = h < 4 ? y : h == 12 || h == 14 ? x : z;
    return ((h & 1) == 0 ? u : -u) + ((h & 2) == 0 ? v : -v);
}


// 3D Perlin Noise 함수
float perlin3D(float x, float y, float z)
{
    int X = (int) floor(x) & 255;
    int Y = (int) floor(y) & 255;
    int Z = (int) floor(z) & 255;
    x -= floor(x);
    y -= floor(y);
    z -= floor(z);
    float u = fade(x);
    float v = fade(y);
    float w = fade(z);
    int p[256];
    // p[] 배열을 적절한 순열 배열로 초기화해야 함

    int A = p[X] + Y, AA = p[A] + Z, AB = p[A + 1] + Z,
        B = p[X + 1] + Y, BA = p[B] + Z, BB = p[B + 1] + Z;

    return lerp(w, lerp(v, lerp(u, grad(p[AA], x, y, z), grad(p[BA], x - 1, y, z)),
                         lerp(u, grad(p[AB], x, y - 1, z), grad(p[BB], x - 1, y - 1, z))),
                   lerp(v, lerp(u, grad(p[AA + 1], x, y, z - 1), grad(p[BA + 1], x - 1, y, z - 1)),
                         lerp(u, grad(p[AB + 1], x, y - 1, z - 1), grad(p[BB + 1], x - 1, y - 1, z - 1))));
}