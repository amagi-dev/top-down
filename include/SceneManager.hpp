#ifndef ___SCENE_HPP___
#define ___SCENE_HPP___

/*
 * NOTE:
 *
 * INFO: 暫定仕様　
 * ラムダ式でオブジェクトを生成
 * ラムダ式でそれぞれを初期化　*参照の持ち合わせなどを指定する
 * シーンをロードする
 * ロードされいるシーンに描画を切り替え
 *
 * MEMO:
 *
 *
 *
 *
 *
 * */
class Scene;
class SceneManager
{

private:

    class Actor;
    class Scene
    {
    public:
        Scene(const char* name);
        ~Scene();

        void Start();
        void Loop();

        const std::string name;

        std::function<void(Scene&)> InitProcess;
    protected:

        std::vector<std::shared_ptr<Actor>> actors;
        std::vector<entt::entity> entityLayers;
    };

public:

    static void Start();
    static void Loop();

    Scene* getScene(const char* name);


    static void SetCurrent(const char* name);
    static void Allocate(const char* name);
    static void Add(const char* name);
    static void SetInit_Process(const char* name,std::function<void(Scene&)> func);
private:


    inline static Scene* current;
    inline static std::vector<Scene> scenes;

    SceneManager();
    ~SceneManager();


};
#endif
