#pragma once
class MiniMap : public Actor
{
	friend class Terrain;
	
private:
	UI*      miniMap;
	UI*      playerIcon;
	
	//미니맵이미지의  x축최소값과 y축 최대값입니다 
	float    miniMapMinScaleX = 0.75f;
	float    miniMapMaxScaleY = 0.95f;
	//정규화전 플레이어의 이동값가중치변수
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
	
	//맵의 높이값을 기준으로 미니맵에 색상입혀줍니다
	Color GetColorForWeight(float normalizedHeight);
	// 터레인 높이맵을 BMP 파일로 저장해서 미니맵 ui 에 diffusemap 생성하는함수
	void DrawMiniMap(const std::string& filename);
	void LoadMiniMap();
	// 플레이어 미니맵 아이콘이 플레이어의 회전값을받아서 보는방향을 보여줍니다
	void FollowPlayerViewPoint();
	// 플레이어의 이동에 맞는 위치에 미니맵 플레이어 아이콘도 이동합니다
	void FollowPlayerMovement();
};

