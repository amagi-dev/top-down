#include "SceneManager.hpp"

SceneManager::Scene::Scene(const char* name) : name(name)
{

}

SceneManager::Scene::~Scene()
{

}

void SceneManager::Scene::Start()
{

}

void SceneManager::Scene::Loop()
{

}

void SceneManager::Loop()
{
    current->Loop();
}

SceneManager::Scene* SceneManager::getScene(const char* name)
{
    for(auto& scene : scenes)
    {
        if(scene.name == std::string(name))
        {
            return &scene;
        }
    }

    assert( false && "SceneManager::getScene(): This scene name was not found");
}

// Add
void SceneManager::Add(const char* name)
{
    for(auto& scene : scenes)
    {
        assert( !(scene.name == std::string(name)) && "SceneManager::AddScene(): This scene name already exists");
    }

    scenes.emplace_back(Scene(name));
}



void SceneManager::SetCurrent(const char* name)
{
    for(auto& scene : scenes)
    {
        if(scene.name == std::string(name))
        {
            current = &scene;
            return;
        }
    }

    assert( false && "SceneManager::SetCurrent(): This scene name was not found");

}


// Allocate
void SceneManager::Allocate(const char* name)
{
    for(auto& scene : scenes)
    {
        if(scene.name == std::string(name))
        {
            scene.InitProcess(scene);
            scene.Start();
            return;
        }
    }

    assert( false && "SceneManager::AllocateScene(): This scene name was not found");
}

void SceneManager::SetInit_Process(const char* name,std::function<void(Scene&)> func)
{
    for(auto& scene : scenes)
    {
        if(scene.name == std::string(name))
        {
            scene.InitProcess = func;
            return;
        }
    }

    assert( false && "SceneManager::SetInit_Process(): This scene name was not found");
}
