#ifndef __SYSTEM_HPP___
#define __SYSTEM_HPP___

#include "Component.hpp"
#include <box2d/box2d.h>
#include <box2d/types.h>
#include <raylib.h>
#include <iostream>

class System
{

public:
    inline static ray::Texture2D texture = {  };

    static void Init(entt::registry& reg)
    {
        SpriteRenderer::LoadTextureFromFile("res/sprite/tile.png");
        texture = SpriteRenderer::GetTexture("res/sprite/tile.png");

        // std::cout<< "System: Init " << texture.id<<std::endl;

        auto view = reg.view<Transform_Data,BoxCollision_Data>();
        for(auto entity : view)
        {
            auto& data = view.get<BoxCollision_Data>(entity);
            auto& transform = view.get<Transform_Data>(entity);


            b2Vec2 position;
            position.x = transform.position.x;
            position.y = transform.position.y;

            data.bodyDef = b2DefaultBodyDef();
            data.bodyDef.type = b2BodyType::b2_staticBody;
            data.bodyId = b2CreateBody(Collision::GetWorldId(),&data.bodyDef);

             //data.shape = b2MakeBox(ray::TILE_SIZE,ray::TILE_SIZE);
            // data.shape = b2MakeBox(ray::TILE_SIZE_SCALED,ray::TILE_SIZE_SCALED);
            data.shape = b2MakeBox(ray::TILE_SIZE_SCALED / 2.0f,ray::TILE_SIZE_SCALED / 2.0f);

            data.shapeDef = b2DefaultShapeDef();
            data.shapeDef.density = 1.0f;
            data.shapeDef.material.friction = 0.0f;
            data.shapeDef.material.restitution = 0.0f;

            b2Body_SetTransform(data.bodyId,position,b2MakeRot(0));

            b2CreatePolygonShape(data.bodyId,&data.shapeDef,&data.shape);


        }

    }



    static void Render(entt::registry& reg)
    {
        auto view = reg.view<Transform_Data,SpriteRenderer_Data,BoxCollision_Data>();
        for(auto entity : view)
        {
            auto& col = view.get<BoxCollision_Data>(entity);
            auto& spriteRenderer = view.get<SpriteRenderer_Data>(entity);

            // std::cout<< "System: Render " << b2Body_GetPosition(col.bodyId).x << std::endl;
            ray::DrawTexturePro(
                texture,
                (ray::Rectangle){ spriteRenderer.beginSize.x, spriteRenderer.beginSize.y, spriteRenderer.endSize.x, spriteRenderer.endSize.y },     // Source
                (ray::Rectangle){ b2Body_GetPosition(col.bodyId).x,b2Body_GetPosition(col.bodyId).y,ray::TILE_SIZE_SCALED,ray::TILE_SIZE_SCALED },  // Destination
           //     (ray::Vector2){ 0,0},                                                                                                                // Origin
                (ray::Vector2){ ray::TILE_SIZE_SCALED /2.0f,ray::TILE_SIZE_SCALED / 2.0f},                                                                                                                // Origin
                0.0f,                                                                                                                               // Rotation
                ray::WHITE
            );

            ray::DrawCircle(b2Body_GetPosition(col.bodyId).x,b2Body_GetPosition(col.bodyId).y,5,ray::RED);

        }
    }

    static void Update(entt::registry& reg)
    {
        auto view = reg.view<Transform_Data,SpriteRenderer_Data>();
        // std::cout<< sizeof(std::variant<Transform,SpriteRenderer>) <<std::endl;

        for(auto entity : view)
        {
            //
            // auto& transform = view.get<Transform_Data>(entity);
            // auto& playerData = view.get<Player>(entity);
            //
            // if(ray::IsKeyDown(ray::KEY_W))
            // {
            //     transform.position.y -= playerData.speed * ray::GetFrameTime();
            // }
            // if(ray::IsKeyDown(ray::KEY_S))
            // {
            //     transform.position.y += playerData.speed * ray::GetFrameTime();
            // }
            // if(ray::IsKeyDown(ray::KEY_A))
            // {
            //     transform.position.x -= playerData.speed * ray::GetFrameTime();
            // }
            // if(ray::IsKeyDown(ray::KEY_D))
            // {
            //     transform.position.x += playerData.speed * ray::GetFrameTime();
            // }
        }
    }
};
#endif
