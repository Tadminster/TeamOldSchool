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
    SceneName 				currentSceneKey;             // ����
    map<SceneName, Scene*>  scenes;

    float changingTime = 0.0f;

public:
    ~SceneManager();

    //�� �߰�
    bool    AddScene(SceneName key, Scene* value);
    //�� ����
    bool    DeleteScene(SceneName key);
    //�� ����
    Scene*  ChangeScene(SceneName key, float changingTime = 0.0f);
    //�� ��������
    Scene*  GetScene(SceneName key);
    //���� �� ��������
    Scene*  GetCurrentScene();

    void    Release();
    void    Update();
    void    LateUpdate();
    void    Render();
    void    PreRender();
    void    ResizeScreen();

    // @brief   ���� ���� Ű�� ��ġ�ϴ��� Ȯ��
    // @param   key     Ȯ���� Ű
    // @return  ��ġ�ϸ� true
    bool    IsMacthScene(SceneName key);
};
