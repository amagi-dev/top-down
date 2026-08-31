#ifndef ___ENTITY_HPP___
#define ___ENTITY_HPP___

#include "Component.hpp"
#include <glm/glm.hpp>
#include <raylib.h>
#include <vector>

#include <box2d/box2d.h>

struct Entity
{
    glm::vec2 position;
    glm::vec2 beginSize;
    glm::vec2 endSize;

    b2BodyId bodyId = b2BodyId();

    b2Polygon shape = b2MakeBox(8,8);
};


class TileLayer
{
public:
    

    
    b2BodyDef bodyDef = b2BodyDef();
    b2ShapeDef shapeDef = b2ShapeDef();

    SpriteRenderer::Sprite sprite;

    TileLayer()
    {
    }

    void Init()
    {
        sprite = SpriteRenderer::GetSprite("res/sprite/tile.png");


        shapeDef = b2DefaultShapeDef();
        shapeDef.density = 1.0f;
        shapeDef.material.friction = 0.6f;

        bodyDef = b2DefaultBodyDef();
        bodyDef.type = b2_staticBody;



    }

    ~TileLayer() = default;

    std::vector<Entity> entities;
    
    void setEntity(const glm::vec2& position, const glm::vec2& beginSize, const glm::vec2& endSize)
    {
        Entity entity;
        entity.position = position * 3.0f;
        entity.beginSize = beginSize;
        entity.endSize = endSize;
        entities.push_back(entity);


        entities.back().bodyId = b2CreateBody(Collision::worldId,&bodyDef);
        
        b2CreatePolygonShape(entities.back().bodyId,&shapeDef,&entities.back().shape);
        
        b2Vec2 pos = {position.x,position.y};
        b2Body_SetTransform(entities.back().bodyId,pos,b2MakeRot(0.0f));
    }


    void Update()
    {

    }

    void Render()
    {
        for(const auto& entity : entities)
        {
            //ray::DrawRectangle(entity.position.x,entity.position.y, 16 * 3, 16 * 3,ray::RED);

            ray::DrawTexturePro(sprite.texture,
            (ray::Rectangle){0,0,16,16},                                          // Source (flipped)
            (ray::Rectangle){entity.position.x - (16 * 3 / 2.0f),entity.position.y  - (16 * 3 / 2.0f),16 * 3,16 * 3},   // Destination
            // (ray::Vector2){16.0f / 2.0f,16.0f / 2.0f},                                                    // Origin
            (ray::Vector2){16.0f * 3 / 2.0f,16.0f * 3 / 2.0f},                                                    // Origin
            0.0f,                                                                   // Rotation
            ray::WHITE);
        }

    }


};

#endif
