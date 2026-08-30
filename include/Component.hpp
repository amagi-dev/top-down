#ifndef ___COMPONENT_HPP___
#define ___COMPONENT_HPP___

#include <box2d/collision.h>
#include <box2d/id.h>
#include <box2d/types.h>
#include <glm/glm.hpp>
#include <box2d/box2d.h>
#include <vector>
#include <string>
#include <iostream>


namespace ray{
    #include <raylib.h>
};


class Actor;
class Component
{
public:

    Component(Actor* actor) : owner(actor){    }; 
    virtual ~Component() = default;

    virtual void Ready(){   };
    virtual void Start(){   };

    virtual void Update(){   };
    virtual void Render()const{   };

//    void *const owner = nullptr;
    Actor *const owner = nullptr;
};





/*############################################################
 * Default Component Types
############################################################ */
class Transform : public Component
{
public:
    using Component::Component;

    ~Transform() = default;

    glm::vec2 position = glm::vec2(0.0f);
    glm::vec2 forward = glm::vec2(0.0f);

};

class SpriteRenderer : public Component
{
public:
    using Component::Component;
    ~SpriteRenderer() = default;

    static void Init(std::vector<std::string>& paths)
    {
        for(const std::string& path : paths)
        {
            bool isLoaded = false;
            // check if the texture is already loaded
            for(const Sprite& sprite : textures)
            {
                if(sprite.name == path)
                {
                    isLoaded = true;
                    break;
                }
            }

            if(isLoaded == false)
            {
                ray::Texture2D texture = ray::LoadTexture(path.c_str());

                // std::cout<<texture.width<<","<<texture.height<<"\n";
                if(texture.id == 0)
                {
                    ray::TraceLog(ray::LOG_ERROR,"SpriteRenderer: Failed to load texture %s",path.c_str());
                    exit(1);
                }
                else
                {
                    textures.push_back(Sprite{texture,path});
                    ray::TraceLog(ray::LOG_INFO,"SpriteRenderer: Successfully to load texture %s",path.c_str());
                }
            }
        }
    }

    Transform* transform = nullptr;


    void SetSprite(const std::string& path)
    {
        for(const Sprite& texture : textures)
        {
            if(texture.name == path)
            {
                sprite.texture = texture.texture;
                sprite.name = texture.name;

                // std::cout<<"SpriteRenderer: Successfully to set texture "<<sprite.texture.width<<"\n";
                return;
            }
        }
    }


    void Ready() override;
    virtual void Start() override;
    virtual void Render()const override;

    std::string texturePath = "";

    glm::vec2 beginSize = glm::vec2(0.0f);
    glm::vec2 endSize = glm::vec2(0.0f);
    glm::vec2 scale = glm::vec2(1.0f);


    struct Sprite
    {
        ray::Texture2D texture = {  };
        std::string name = "";

    };
    Sprite sprite = {  };
    static std::vector<Sprite> textures;
};


class Collision : public Component
{
public:
    using Component::Component;
    ~Collision() = default;

    b2BodyDef bodyDef = b2BodyDef();
    b2ShapeDef shapeDef = b2ShapeDef();
    b2BodyId bodyId = b2BodyId();

    static void Init(const glm::vec2 gravity = glm::vec2(0.0f,0.0f))
    {
        worldDef = b2DefaultWorldDef();
        worldDef.gravity = { gravity.x,gravity.y };
        worldId = b2CreateWorld(&worldDef);
    }

protected:

static b2WorldId worldId;
static b2WorldDef worldDef;

};


class BoxCollision : public Collision
{
public:
    using Collision::Collision;
    ~BoxCollision() = default;

    virtual void Ready() override;

    b2Polygon shape = b2Polygon();
};

class CircleCollision : public Collision
{
public:
    using Collision::Collision;
    ~CircleCollision() = default;

    virtual void Ready() override;

    b2Circle shape = b2Circle();
};






#endif
