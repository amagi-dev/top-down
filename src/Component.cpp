#include "Component.hpp"
#include <box2d/id.h>

b2WorldId Collision::worldId = b2WorldId();
b2WorldDef Collision::worldDef = b2WorldDef();

std::vector<SpriteRenderer::Sprite> SpriteRenderer::textures;

void BoxCollision::Ready()
{
    shape = b2MakeBox(16 * 3,16 * 3);

    bodyDef = b2DefaultBodyDef();
    bodyDef.type = b2_dynamicBody;

    bodyId = b2CreateBody(worldId,&bodyDef);

    shapeDef = b2DefaultShapeDef();
    shapeDef.density = 1.0f;
    shapeDef.material.friction = 0.6f;

    b2CreatePolygonShape(bodyId, &shapeDef, &shape);
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

    b2CreateCircleShape(bodyId, &shapeDef, &shape);
}


