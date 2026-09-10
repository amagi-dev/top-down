#include "Component.hpp"
#include "Actor.hpp"
#include <box2d/box2d.h>
#include <raylib.h>

void SpriteRenderer::Start()
{
    transform = owner->GetComponent<Transform>();

    Collision *c = owner->GetComponent<BoxCollision>();
    if(c)
    {
        collision = c;
    }


    c = owner->GetComponent<CircleCollision>();
    if(c)
    {
        collision = c;
    }
}

void Movement::Start()
{
    transform = owner->GetComponent<Transform>();
    Collision *c = owner->GetComponent<BoxCollision>();
    if(c)
    {
        collision = c;
    }


    c = owner->GetComponent<CircleCollision>();
    if(c)
    {
        collision = c;
    }

    assert(c && "Movement: No BoxCollision or CircleCollision found");

    b2Rot rotation = b2MakeRot(0.0f);

    b2Body_SetTransform(collision->GetBodyId(),{ transform->position.x,transform->position.y },rotation);
}

void Movement::Update()
{
    transform->position.x = b2Body_GetPosition(collision->GetBodyId()).x;
    transform->position.y = b2Body_GetPosition(collision->GetBodyId()).y;
}





void SpriteRenderer::Render()const
{
    // std::cout<< "SpriteRenderer: Render " << texture.id<<std::endl;
    // std::cout<<"Position    "<<transform->position.x<<","<<transform->position.y<<std::endl;
    // std::cout<<"Box2D   "<<b2Body_GetPosition(collision->GetBodyId()).x<<" , "<< b2Body_GetPosition(collision->GetBodyId()).y<<std::endl;
    // std::cout<< " " <<std::endl;

    ray::DrawTexturePro(
        texture,                                                                                                                    // Texture
        (ray::Rectangle){ beginSize.x,beginSize.y,endSize.x,endSize.y },                                                            // Source
        (ray::Rectangle){ (float)transform->position.x,(float)transform->position.y,ray::TILE_SIZE_SCALED,ray::TILE_SIZE_SCALED },  // Destination
        (ray::Vector2){ray::TILE_SIZE_SCALED / 2.0f,ray::TILE_SIZE_SCALED / 2.0f},                                                  // Origin
        0.0f,                                                                                                                       // Rotation
        ray::WHITE                                                                                                                  // Color
    );


    ray::DrawCircle((float)transform->position.x,(float)transform->position.y,5,ray::RED);


}


