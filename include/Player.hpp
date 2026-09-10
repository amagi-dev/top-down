#ifndef ___PLAYER_HPP___
#define ___PLAYER_HPP___

#include "Actor.hpp"
#include "Component.hpp"
#include "Script.hpp"

#include <iostream>
class Player : public Script
{
private:

    float speed = 200.0f;

public:
    using Script::Script;
    virtual ~Player() = default;

    SpriteRenderer* renderer = nullptr;
    Movement *movement = nullptr;
    void Start() override
    {
        renderer = owner->GetComponent<SpriteRenderer>();
        renderer->SetTexture("res/sprite/tile.png");
        renderer->beginSize = glm::vec2(0.0f,ray::TILE_SIZE);
        renderer->endSize = glm::vec2(ray::TILE_SIZE, ray::TILE_SIZE);


        movement = owner->GetComponent<Movement>();


    }

    void Update() override
    {
        glm::vec2 direction = { 0.0f, 0.0f };

        if(ray::IsKeyDown(ray::KEY_W))
        {
            direction.y = -speed;

        }
        else if(ray::IsKeyDown(ray::KEY_S))
        {
            direction.y = speed;
        }

        if(ray::IsKeyDown(ray::KEY_A))
        {
            direction.x = -speed;
        }
        else if(ray::IsKeyDown(ray::KEY_D))
        {
            direction.x = speed;
        }

        movement->Move(direction);
    }
};



#endif
