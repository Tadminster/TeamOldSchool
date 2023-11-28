#pragma once
class MiniMap : public Actor
{
	friend class Terrain;
	
private:
	UI*      miniMap;
	UI*      playerIcon;
	
	//�̴ϸ��̹�����  x���ּҰ��� y�� �ִ밪�Դϴ� 
	float    miniMapMinScaleX = 0.75f;
	float    miniMapMaxScaleY = 0.95f;
	//����ȭ�� �÷��̾��� �̵�������ġ����
	float    moveWeightX = 0.2f;
	float    moveWeightY = 0.3f;

public:
	MiniMap();
	~MiniMap();

	void Init();
	void Release();
	void Update();
	void LateUpdate();
	void PreRender();
	void Render();
	void ResizeScreen();
	//------------------------------------------
	
	//���� ���̰��� �������� �̴ϸʿ� ���������ݴϴ�
	Color GetColorForWeight(float normalizedHeight);
	// �ͷ��� ���̸��� BMP ���Ϸ� �����ؼ� �̴ϸ� ui �� diffusemap �����ϴ��Լ�
	void DrawMiniMap(const std::string& filename);
	void LoadMiniMap();
	// �÷��̾� �̴ϸ� �������� �÷��̾��� ȸ�������޾Ƽ� ���¹����� �����ݴϴ�
	void FollowPlayerViewPoint();
	// �÷��̾��� �̵��� �´� ��ġ�� �̴ϸ� �÷��̾� �����ܵ� �̵��մϴ�
	void FollowPlayerMovement();
};

