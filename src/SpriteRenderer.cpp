#ifndef ___SPRITE_RENDERER_CPP___
#define ___SPRITE_RENDERER_CPP___
#include "Component.hpp"
#include "Actor.hpp"

void SpriteRenderer::Ready()
{

    
    transform = owner->GetComponent<Transform>();


}

void SpriteRenderer::Start()
{
    
}



void SpriteRenderer::Render()const
{

     // std::cout<<sprite.texture.id<<"\n";
     //std::cout<<sprite.texture.width<<","<<sprite.texture.height<<"\n";
    //    std::cout<<beginSize.x<<","<<beginSize.y<<","<<endSize.x<<","<<endSize.y<<"\n";

    ray::DrawTexturePro(
            sprite.texture,
            //(ray::Rectangle){ 0,0,16 * 3,16},     // Source
            (ray::Rectangle){ beginSize.x,beginSize.y,endSize.x,endSize.y },     // Source
            (ray::Rectangle){ (float)transform->getPosition().x,(float)transform->getPosition().y,16 * 3,16 * 3 },      // Destination
            // (ray::Vector2){0,0},                                                     // Origin
            (ray::Vector2){16.0f * 3 / 2.0f,16.0f * 3 / 2.0f},                                                    // Origin
            0.0f,                                                               // Rotation
            ray::WHITE
        );
}

#endif
