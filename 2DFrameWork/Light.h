#pragma once
#define DAY_CYCLE		60.0f
#define HALF_DAY_CYCLE	dayCycleLength * 0.5f

struct DirLight
{
	Vector4			direction;
	Color			color;
	DirLight()
	{
		//������ ������ġ �����մϴ� ���� ���� �÷��̾��� �Ӹ������� �¾��� �����̱�����մϴ�
		direction = Vector4(0, 0, 0, 0);
		color = Vector4(1,1,0.8f,1);
	};
};

enum class LightType
{
	POINT,
	SPOT,
};

struct LightBuffer
{
	int			isActive;
	int			lightType;
	float		inner;
	float		outer;
	//
	int         size;
	Vector3     direction;
	//4
	Vector3		position;
	float		radius;
	//4
	Color		color;
	LightBuffer() :isActive(false), lightType((int)LightType::POINT), color(1, 1, 1),
		radius(50), size(0)
		, inner(84.0f), outer(44.0f), direction(0, 0, 0)
	{

	}
};


class Light : public Actor
{

public:
	LightBuffer*    light;
	~Light();
	static Light*   Create(string name = "Light", int type =0);
	virtual void	Release();
	virtual void	Update() override;
	virtual void	RenderDetail();
	
};

#define MAX_LIGHT 16
class LightManager : public Singleton<LightManager>
{
public:
	const float		dayCycleLength = 60.0f;						// ������ �Ϸ� �ֱ��Դϴ�
	const float		halfdayCycleLength = dayCycleLength * 0.5f;	// �ݳ����� �ֱ��Դϴ�
	float			currentTime = dayCycleLength * 0.5f;		// ������ �ð��Դϴ�
	float			timeRatio;									// ������ �ð������Դϴ�(0 ~ 1, 1:����. 0:����)

private:
	ID3D11Buffer*	dirLightBuffer;
	ID3D11Buffer*	lightBuffer;

public:
	LightManager();
	~LightManager();
	bool				isBoss{ false };
	DirLight			dirLight;
	LightBuffer			light[MAX_LIGHT];
	void				Set();
	void                RenderDetail();
	void                UpdateDirection();
	void				SetSize();
	const float			GetTimeRatio() { return  timeRatio; }
};