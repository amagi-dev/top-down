#ifndef ___TILE_HPP___
#define ___TILE_HPP___

// #include <iostream>
#include "Component.hpp"
#include "Actor.hpp"

class Tile : public Component
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
        owner->GetComponent<SpriteRenderer>()->beginSize = glm::vec2(0,0);
        owner->GetComponent<SpriteRenderer>()->endSize = glm::vec2(spriteSize * 1,spriteSize);
        owner->GetComponent<SpriteRenderer>()->scale = glm::vec2(3.0f,3.0f);
    }




    void Update() override
    {


    }
};

#endif
