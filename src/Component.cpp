#include <box2d/box2d.h>
#include <iostream>
#include "Component.hpp"
#include "Actor.hpp"
#include <box2d/id.h>

b2WorldId Collision::worldId = b2WorldId();
b2WorldDef Collision::worldDef = b2WorldDef();

std::vector<SpriteRenderer::Sprite> SpriteRenderer::textures;

void BoxCollision::Ready()
{
    transform = owner->GetComponent<Transform>();
    shape = b2MakeBox(16 * 3 / 2.0f,16 * 3 / 2.0f);
    
    bodyDef = b2DefaultBodyDef();
    bodyDef.type = b2_dynamicBody;

    bodyId = b2CreateBody(worldId,&bodyDef);

    shapeDef = b2DefaultShapeDef();
    shapeDef.density = 1.0f;
    shapeDef.material.friction = 0.6f;
    
    b2CreatePolygonShape(bodyId,&shapeDef,&shape);
    
    b2Vec2 position = { transform->initPosition.x,transform->initPosition.y };
    b2Body_SetTransform(bodyId,position,b2MakeRot(0));
    transform->setPosition(transform->initPosition);

}



void Transform::Ready()
{
    collision = owner->AddComponent<BoxCollision>();
    
}


void CircleCollision::Ready()
{
    const float tileSize = (16.0f * 3.0f) - 1.0f;

    b2Circle circle = {
    .center = {tileSize / 2.0f, tileSize / 2.0f},
    .radius = (tileSize / 2.0f) - 0.1f
    };

    shape = circle;
    bodyDef = b2DefaultBodyDef();
    bodyDef.type = b2_dynamicBody;

    bodyId = b2CreateBody(worldId,&bodyDef);

    shapeDef = b2DefaultShapeDef();
    shapeDef.density = 1.0f;
    shapeDef.material.friction = 0.6f;

    transform = owner->GetComponent<Transform>();
    b2CreateCircleShape(bodyId,&shapeDef,&shape);
}

void RigidBody::Ready()
{
    collision = owner->AddComponent<BoxCollision>();
    transform = owner->GetComponent<Transform>();
}

void RigidBody::Update()
{
    std::cout<<"RigidBody Update: "<<b2Body_GetPosition(collision->bodyId).x<<","<<b2Body_GetPosition(collision->bodyId).y<<"\n";
    transform->setPosition(glm::vec2(b2Body_GetPosition(collision->bodyId).x,b2Body_GetPosition(collision->bodyId).y));
}
