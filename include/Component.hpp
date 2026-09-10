#ifndef ___COMPONENT_HPP___
#define ___COMPONENT_HPP___


#include "Ray.hpp"
#include <box2d/collision.h>
#include <glm/glm.hpp>
#include <box2d/box2d.h>
#include <entt/entt.hpp>

/*#############################################################
 * ECS component data
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

/*#############################################################
 * Internal component data
 *#############################################################*/
struct SpriteRenderer_Data_Internal
{
    ray::Texture2D sprite = { };
};


/*#############################################################
 * Component class
 *#############################################################*/
class Actor;
class Component
{
public:
    Component(Actor *const actor) : owner(actor){   }
    virtual ~Component() = default;

    virtual void Start(){ }
    virtual void Update(){ }
    virtual void Render()const{ }


protected:
    Actor *const owner;
};

class Transform : public Component
{
public:


    using Component::Component;
    virtual ~Transform() = default;

    glm::vec2 position = { 0.0f, 0.0f };

private:
    glm::vec2 forward = { 1.0f, 0.0f };

};

class Collision;
class SpriteRenderer : public Component
{
public:

    Collision *collision = nullptr;

    struct Texture
    {
        ray::Texture2D texture = {  };
        const std::string path = {  };
    };

    Transform *transform = nullptr;
    ray::Texture2D texture = {  };

    static void LoadTextureFromFile(const std::string& path)
    {
        for(auto& texture : textures)
        {
            if(texture.path == path)
            {
                ray::TraceLog(ray::LOG_WARNING,"SpriteRenderer: Texture already loaded %s",path.c_str());
                return;
            }
        }

        Texture texture = { .path = path };
        texture.texture = ray::LoadTexture(texture.path.c_str());
        textures.push_back(texture);
    }

    static ray::Texture2D GetTexture(const std::string& path)
    {
        for(auto& texture : textures)
        {
            if(texture.path == path)
            {
                return texture.texture;
            }
        }

        ray::TraceLog(ray::LOG_ERROR,"SpriteRenderer: Texture not found %s",path.c_str());
        return {  };
    }

    void SetTexture(const std::string& path)
    {
        texture = GetTexture(path);
    }

    virtual void Start() override;
    virtual void Render()const override;

    using Component::Component;
    virtual ~SpriteRenderer() = default;



    inline static std::vector<Texture> textures;

    //ray::Texture2D sprite = {  };
    glm::vec2 beginSize = { };
    glm::vec2 endSize = { };
};



class Collision : public Component
{
public:
    static void Init(const glm::vec2 gravity)
    {
        worldDef = b2DefaultWorldDef();
        worldDef.gravity = { gravity.x,gravity.y };
        worldId = b2CreateWorld(&worldDef);
    }

    using Component::Component;
    virtual ~Collision() = default;

    static void WorldUpdate()
    {
        b2World_Step(worldId,1.0f / 60.0f,4);
    }

    static b2WorldId GetWorldId()
    {
        return worldId;
    }

    b2BodyId GetBodyId()
    {
        return bodyId;
    }
protected:

    b2BodyDef bodyDef = b2BodyDef();
    b2ShapeDef shapeDef = b2ShapeDef();
    b2BodyId bodyId = b2BodyId();

    inline static b2WorldId worldId;
    inline static b2WorldDef worldDef;

};

class BoxCollision : public Collision
{
public:

    void Start() override
    {
        shape = b2MakeBox(ray::TILE_SIZE_SCALED / 2.0f,ray::TILE_SIZE_SCALED / 2.0f);

        bodyDef = b2DefaultBodyDef();
        bodyDef.type = b2_dynamicBody;

        bodyId = b2CreateBody(worldId,&bodyDef);

        shapeDef = b2DefaultShapeDef();
        shapeDef.density = 1.0f;
        shapeDef.material.friction = 0.0f;
        shapeDef.material.restitution = 0.0f;

        b2CreatePolygonShape(bodyId,&shapeDef,&shape);
    }

    using Collision::Collision;
    virtual ~BoxCollision() = default;

private:
    b2Polygon shape = b2Polygon();
};

class CircleCollision : public Collision
{
public:

    void Start() override
    {
        b2Circle circle = {
            .center = {0,0},
            // .center = {ray::TILE_SIZE_SCALED / 2.0f, ray::TILE_SIZE_SCALED / 2.0f},
            .radius = (ray::TILE_SIZE_SCALED / 2.0f) - 0.1f
        };

        shape = circle;
        bodyDef = b2DefaultBodyDef();
        bodyDef.type = b2_dynamicBody;

        bodyId = b2CreateBody(worldId,&bodyDef);

        shapeDef = b2DefaultShapeDef();
        shapeDef.density = 1.0f / (ray::TILE_SIZE_SCALED * ray::TILE_SIZE_SCALED);

        shapeDef.material.friction = 0.0f;
        shapeDef.material.restitution = 0.0f;

        b2CreateCircleShape(bodyId,&shapeDef,&shape);
        // std::cout<< "CircleCollision: Start " << std::endl;
    }

    using Collision::Collision;
    virtual ~CircleCollision() = default;

private:
    b2Circle shape = b2Circle();
};


class Movement : public Component
{
public:
    using Component::Component;
    virtual ~Movement() = default;

    virtual void Start() override;
    virtual void Update() override;

    void Move(glm::vec2 move)
    {
        std::cout<< "Movement: Move " << move.x << "," << move.y << std::endl;
        b2Body_SetLinearVelocity(collision->GetBodyId(),{ move.x,move.y });
    }

    Collision* collision = nullptr;
    Transform* transform = nullptr;
};

#endif
