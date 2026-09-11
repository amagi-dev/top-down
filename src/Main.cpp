#include <LDtkLoader/Tile.hpp>
#include <LDtkLoader/Project.hpp>
#include <cinttypes>
#include <glm/glm.hpp>
#include <entt/entt.hpp>

#include "Ray.hpp"
#include "Data.hpp"
#include "Actor.hpp"
#include "Component.hpp"
#include "System.hpp"
#include "ResourceManager.hpp"
#include "SceneManager.hpp"



#include "Player.hpp"
#include "CameraController.hpp"

const int TILE_SIZE = 16;
glm::vec2 cameraPosition = { 0.0f, 0.0f };
std::vector<std::shared_ptr<Actor>> actors;

void SetEntities(std::vector<std::shared_ptr<Actor>> &actors,const ldtk::Layer& layer)
{
    if(layer.getType() != ldtk::LayerType::Entities)
    {
        ray::TraceLog(ray::LOG_ERROR,"Ldtk: Not entities layer %s",layer.getName().c_str());
    }

    for(const auto& entity : layer.allEntities())
    {
        int grid_x = entity.getGridPosition().x;
        int grid_y = entity.getGridPosition().y;

        int value = -1;
        if(entity.getName() == ((std::string)"Chest"))
        {
            value = 1;

        }
        else if(entity.getName() == ((std::string)"Player"))
        {
            actors.push_back(std::make_shared<Actor>());
            actors.back()->AddComponent<Transform>();

            actors.back()->GetComponent<Transform>()->position = glm::vec2(grid_x * ray::TILE_SIZE_SCALED, grid_y * ray::TILE_SIZE_SCALED);

            actors.back()->AddComponent<SpriteRenderer>();
            actors.back()->AddComponent<CircleCollision>();
            actors.back()->AddComponent<Movement>();

            actors.back()->AddScript<Player>();

            cameraPosition = actors.back()->GetComponent<Transform>()->position;
        }
        else
        {
            value = -1;
        }

    }
}

void SetTiles(entt::registry &registry,const ldtk::Layer& layer)
{
    if(layer.getType() != ldtk::LayerType::Tiles)
    {
        ray::TraceLog(ray::LOG_ERROR,"Ldtk: Not tile layer %s",layer.getName().c_str());
    }

    for(const auto& tile : layer.allTiles())
    {
        int grid_x = tile.getGridPosition().x;
        int grid_y = tile.getGridPosition().y;

        // std::cout<<tile.tileId<<std::endl;
        if(tile.tileId == 0)
        {
            auto entity = registry.create();
            registry.emplace<Transform_Data>(entity,glm::vec2(grid_x * ray::TILE_SIZE_SCALED, grid_y * ray::TILE_SIZE_SCALED));


            registry.emplace<SpriteRenderer_Data>(entity,glm::vec2(0,0),glm::vec2(TILE_SIZE,TILE_SIZE));
            registry.emplace<BoxCollision_Data>(entity,glm::vec2(0,0),glm::vec2(ray::TILE_SIZE_SCALED,ray::TILE_SIZE_SCALED));
        }
    }
}

int main()
{
    ldtk::Project stage;
    stage.loadFromFile("res/debug.ldtk");
    const auto& world = stage.getWorld();

    const auto& level = world.getLevel(0);

    const ray::Vector2 window = {(float)2560,(float)1440};   // 4K Monitor
    //const Vector2 window = {(float)1280,(float)720};  // FullHD Monitor
    //const Vector2 window = {(float)1080,(float)1920}; // Mobile Phone Portrait
    //const Vector2 window = {(float)1920,(float)1080}; // Mobile Phone Landscape

    //const Vector2 screen = {(float)2560,(float)1440};   // 4K Monitor
    const ray::Vector2 screen = {(float)1280,(float)720};  // FullHD Monitor
    //const Vector2 screen = {(float)1080,(float)1920}; // Mobile Phone Portrait
    //const Vector2 screen = {(float)1920,(float)1080}; // Mobile Phone Landscape

    const ray::Vector2 scale = {(float)window.x / screen.x,(float)window.y / screen.y};

    ray::InitWindow(window.x,window.y,"app");
    ray::SetWindowState(ray::FLAG_VSYNC_HINT);

    ResourceManager::LoadTexture("res/sprite/tile.png","tile");

    /*############################################################
    # Framework init
    ############################################################ */

    Collision::Init(glm::vec2(0.0f,0.0f));
    entt::registry registry;

    SetTiles(registry,level.getLayer("Wall"));
    SetEntities(actors,level.getLayer("Character"));
    System::Init(registry);

    // Camera


    /*############################################################
    # Object init
    ############################################################*/
    SceneManager::Add("Main");
    SceneManager::SetInit_Process("Main",[](auto& scene)
    {
        std::cout<<"SceneManager: Main scene init"<<std::endl;

    });


    SceneManager::Allocate("Main");
    SceneManager::SetCurrent("Main");




    while(ray::WindowShouldClose() == false)
    {

        /*############################################################
        # Draw to the render texture
        ############################################################ */
        {
            SceneManager::Loop();
        }


        /*############################################################
        # Draw to the screen
        ############################################################ */
        {
            ray::BeginDrawing();
            ray::ClearBackground(ray::BLACK);

                /*
                ray::DrawTexturePro(
                camera->getTarget().texture,
                (ray::Rectangle){ 0, 0, (float)camera->getTarget().texture.width, -(float)camera->getTarget().texture.height },   // Source (flipped)
                (ray::Rectangle){ 0, 0, (float)window.x,window.y },                                     // Destination
                (ray::Vector2){0,0},                                                                    // Origin
                0.0f,                                                                                   // Rotation
                ray::WHITE
                );
                */

            ray::EndDrawing();
        }
    }


    return 0;
}
