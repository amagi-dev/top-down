#ifndef ___PLAYER_CONTROLLER_HPP___
#define ___PLAYER_CONTROLLER_HPP___
// #include <iostream>
#include "Component.hpp"
#include "Actor.hpp"
#include <iostream>

class PlayerController : public Component
{
public:
    using Component::Component;
    
    Transform* transform;
    RigidBody* body;

    const int spriteSize = 16;
    void Ready() override
    {
        
    }

    void Start() override
    {
        transform = (Transform*)owner->GetComponent<Transform>();
        body = owner->GetComponent<RigidBody>();
        
    
        owner->GetComponent<SpriteRenderer>()->SetSprite("res/sprite/tile.png");
        
        owner->GetComponent<SpriteRenderer>()->beginSize = glm::vec2(spriteSize * 2,0.0f);
        owner->GetComponent<SpriteRenderer>()->endSize = glm::vec2(spriteSize,spriteSize);
        owner->GetComponent<SpriteRenderer>()->scale = glm::vec2(3.0f,3.0f);




    }




    void Update() override
    {

        float speed = 500.0f; // Movement speed in pixels per second
        glm::vec2 move(0.0f, 0.0f);
        if(ray::IsKeyDown(ray::KEY_W))
        {
            move.y = -speed;
        }
        if(ray::IsKeyDown(ray::KEY_S))
        {
            move.y = speed;
        }
        if(ray::IsKeyDown(ray::KEY_A))
        {
            move.x = -speed;
        }
        if(ray::IsKeyDown(ray::KEY_D))
        {
            move.x = speed;
        }
        
        // std::cout<<"Move: "<< transform->getPosition().x<<"\n";
        body->Move(move);
        
        
    }
};

#endif
