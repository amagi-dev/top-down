#ifndef ___DATA_HPP___
#define ___DATA_HPP___


#include <glm/glm.hpp>
#include <box2d/box2d.h>
/*#############################################################
 * ECS data
 *#############################################################*/
struct Transform_Data
{
    glm::vec2 position = { };
};

struct SpriteRenderer_Data
{
    glm::vec2 beginSize = { };
    glm::vec2 endSize = { };
};

struct BoxCollision_Data
{
    glm::vec2 size = { };
    glm::vec2 offset = { };

    b2Polygon shape = { };
    b2ShapeDef shapeDef = { };

    b2BodyDef bodyDef ={ };
    b2BodyId bodyId = { };
};

struct CircleCollision_Data
{
    float radius = 0.0f;
    glm::vec2 offset = { };
};

#endif
