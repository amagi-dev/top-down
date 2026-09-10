#ifndef ___COMPONENT_HPP___
#define ___COMPONENT_HPP___


#include "Ray.hpp"
#include <box2d/collision.h>
#include <box2d/box2d.h>
#include <glm/glm.hpp>
#include <raylib.h>
#include <vector>


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
    using Component::Component;
    virtual ~SpriteRenderer() = default;

    Collision *collision = nullptr;
    Transform *transform = nullptr;

    glm::vec2 beginSize = { };
    glm::vec2 endSize = { };
    ray::Texture2D texture = {  };


    virtual void Start() override;
    virtual void Render()const override;

    void setTexture(const char* indexName);
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
        b2World_Step(worldId,ray::GetFrameTime(),4);
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

    void Move(glm::vec2 move)const
    {
        // std::cout<< "Movement: Move " << move.x << "," << move.y << std::endl;
        b2Body_SetLinearVelocity(collision->GetBodyId(),{ move.x,move.y });
    }

    Collision* collision = nullptr;
    Transform* transform = nullptr;
};


class Camera : public Component
{
private:

public:

    inline static glm::vec2 screenSize = {(float)1280,(float)720};
    inline static ray::RenderTexture2D target = { };

        ray::Camera2D camera = { 0 };
    using Component::Component;
    virtual ~Camera() = default;

    Transform *transform = nullptr;
    Movement *movement = nullptr;

    void Begin()const;
    void End()const;

    ray::RenderTexture2D getTarget()const
    {
        return target;
    }

    void Move(glm::vec2 move)const
    {
        transform->position += move * ray::GetFrameTime();
    }

    virtual void Start()override;
    virtual void Update()override;
    virtual void Render()const override;


};


#endif
