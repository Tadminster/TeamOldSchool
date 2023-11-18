#pragma once
class MiniMap : public Actor
{
	friend class Terrain;
	
private:
	UI*      miniMapUI;
	UI*      playerPosUI;
	

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
};

