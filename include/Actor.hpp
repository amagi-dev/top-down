#ifndef ___ACTOR_HPP___
#define ___ACTOR_HPP___
#include <vector>
#include <variant>
#include <memory>

#include "Component.hpp"

class Script;
class Actor
{
public:

    Actor() = default;
    ~Actor() = default;

    void Start();
    void Update();
    void Render();

    template<typename T>
    void AddComponent()
    {
        static_assert(std::is_base_of<Component,T>::value,"is not a Component type");

        for(auto& component : components)
        {
            if(std::holds_alternative<T>(component))
            {
                return;
            }
        }

        components.emplace_back(std::in_place_type<T>, this);
    }

    template<typename T>
    T* GetComponent()
    {
        static_assert(std::is_base_of<Component,T>::value,"is not a Component type");

        for(auto& component : components)
        {
            if(std::holds_alternative<T>(component))
            {
                return &std::get<T>(component);
            }
        }

        return nullptr;
    }

    template<typename T>
    void AddScript()
    {
        static_assert(std::is_base_of<Script,T>::value,"is not a Script type");

        for(auto& c : scripts)
        {
            if(std::dynamic_pointer_cast<T>(c))
            {
                return;
            }
        }

        scripts.emplace_back(std::make_shared<T>(this));

    }


    template<typename T>
    T* GetScript()
    {
        static_assert(std::is_base_of<Script,T>::value,"is not a Script type");

        for(auto& c : scripts)
        {
            if(std::dynamic_pointer_cast<T>(c))
            {
                return std::dynamic_pointer_cast<T>(c).get();
            }
        }

        return nullptr;
    }

private:
    std::vector<std::variant<Transform,SpriteRenderer,CircleCollision,BoxCollision,Movement,Camera>> components;
    std::vector<std::shared_ptr<Script>> scripts;
};
#endif
