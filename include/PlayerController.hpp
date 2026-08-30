#ifndef ___PLAYER_CONTROLLER_HPP___
#define ___PLAYER_CONTROLLER_HPP___
// #include <iostream>
#include "Component.hpp"
#include "Actor.hpp"

class PlayerController : public Component
{
public:
    using Component::Component;
    
    Transform* transform;
    
    const int spriteSize = 16;
    void Ready() override
    {
        
    }

    void Start() override
    {
        transform = (Transform*)owner->GetComponent<Transform>();
        

        owner->GetComponent<SpriteRenderer>()->SetSprite("res/sprite/tile.png");
        
        owner->GetComponent<SpriteRenderer>()->beginSize = glm::vec2(spriteSize * 2,0.0f);
        owner->GetComponent<SpriteRenderer>()->endSize = glm::vec2(spriteSize,spriteSize);
        owner->GetComponent<SpriteRenderer>()->scale = glm::vec2(3.0f,3.0f);
    }




    void Update() override
    {
        // std::cout<<transform->position.x<<","<<transform->position.y<<"\n";

        float speed = 200.0f; // Movement speed in pixels per second
        if(ray::IsKeyDown(ray::KEY_W))
        {
            transform->position.y -= speed * ray::GetFrameTime(); // Adjust movement speed based on frame time
        }
        if(ray::IsKeyDown(ray::KEY_S))
        {
            transform->position.y += speed * ray::GetFrameTime();
        }
        if(ray::IsKeyDown(ray::KEY_A))
        {
            transform->position.x -= speed * ray::GetFrameTime();
        }
        if(ray::IsKeyDown(ray::KEY_D))
        {
            transform->position.x += speed * ray::GetFrameTime();
        }



    }
};

#endif
