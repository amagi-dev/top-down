#ifndef ___ACTOTR_HPP___
#define ___ACTOTR_HPP___

#include "Component.hpp"
#include <vector>
// #include <iostream>

class Component;
class Transform;

class Actor
{
public:

    Actor(){    };
    /*
     * NOTE:
     * Ready()は最初に実行される関数です。初期化するだけ
     * Start()はReady()の後に実行されて。Update()が呼ばれる前に実行されます。ユーザースクリプトの　Start()後に実行されます
     * */


    virtual void Ready()
    {
        for(Component* component : components)
        {

             component->Ready();
        }
    };


    virtual void Start()
    {
        

        for(Component* component : components)
        {
             component->Start();
        }

    };

    virtual void Update()
    {
        for(const Component* component : components)
        {
            ((Component*)component)->Update();
        }
    };

    virtual void Render() const
    {
        for(const Component* component : components)
        {
            component->Render();
            // ((Component*)component)->Render();
        }


    };

    template<typename Type>
    Type* GetComponent()
    {
        static_assert(std::is_base_of_v<Component, Type>,"This type is not component");
        for(Component *component : components)
        {
            Type* c = dynamic_cast<Type*>(component);
            if(c != nullptr)
            {
                return c;
            }
        }
        
        assert(false && "Component is not found!");
        return nullptr;
    }

    template<typename Type>
    Type* AddComponent()
    {
        static_assert(std::is_base_of_v<Component, Type>,"This type is not component");
        for(Component *component : components)
        {
            Type* c = dynamic_cast<Type*>(component);
            if(c != nullptr)
            {
                return c;
            }
        }

        components.push_back(new Type(this));
        return dynamic_cast<Type*>(components.back());
    } 

private:
     std::vector<Component*> components;
};
#endif


