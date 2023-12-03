enum class SceneName
{
    Intro, Title, Loading, InGame
};

#pragma once
class SceneManager :public Singleton<SceneManager>
{
private:
    bool                    isChanging = false;
    Scene *                 nextScene = nullptr;
    Scene *                 currentScene = nullptr;
    SceneName 				currentSceneKey;             // 현재
    map<SceneName, Scene*>  scenes;

    float changingTime = 0.0f;

public:
    ~SceneManager();

    //씬 추가
    bool    AddScene(SceneName key, Scene* value);
    //씬 삭제
    bool    DeleteScene(SceneName key);
    //씬 변경
    Scene*  ChangeScene(SceneName key, float changingTime = 0.0f);
    //씬 가져오기
    Scene*  GetScene(SceneName key);
    //현재 씬 가져오기
    Scene*  GetCurrentScene();

    void    Release();
    void    Update();
    void    LateUpdate();
    void    Render();
    void    PreRender();
    void    ResizeScreen();

    // @brief   현재 씬과 키가 일치하는지 확인
    // @param   key     확인할 키
    // @return  일치하면 true
    bool    IsMacthScene(SceneName key);
};
