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
	
	void DrawMiniMap(const std::string& filename);

};

