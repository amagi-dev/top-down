

#include "Actor.hpp"
#include "Component.hpp"
#include "PlayerController.hpp"
#include <LDtkLoader/Tile.hpp>
#include <LDtkLoader/Project.hpp>
#include <vector>
#include <string>
#include <glm/glm.hpp>

namespace ray
{
    #include <raylib.h>
};


struct Tile
{
    ray::Vector2 grid;
    int value = 0;
};

const int TILE_SIZE = 16;

std::vector<Actor*> actors;

enum ObjectType
{
    Chest = 1,
    Player = 2,
    None = -1
};

void SetEntities(std::vector<Actor*> &actors,const ldtk::Layer& layer)
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
            actors.push_back(new Actor());
            actors.back()->AddComponent<BoxCollision>();
            actors.back()->AddComponent<Transform>();
            actors.back()->AddComponent<SpriteRenderer>();

            actors.back()->AddComponent<PlayerController>();

            actors.back()->GetComponent<Transform>()->position = glm::vec2(grid_x * TILE_SIZE,grid_y * TILE_SIZE);
        }
        else
        {
            value = -1;
        }

    }
}


void SetTiles(std::vector<Actor*> &actors,const ldtk::Layer& layer)
{
    if(layer.getType() != ldtk::LayerType::Tiles)
    {
        ray::TraceLog(ray::LOG_ERROR,"Ldtk: Not tile layer %s",layer.getName().c_str());
    }

    // std::cout<<"alltiles :"<<layer.allTiles().size()<<"\n";
    int i = 0;
    for(const auto& tile : layer.allTiles())
    {
        int grid_x = tile.getGridPosition().x;
        int grid_y = tile.getGridPosition().y;
        
        if(tile.tileId == 0)
        {

            std::cout<<"alltiles :  "<<i<<"\n";

             actors.push_back( new Actor());
             actors.back()->AddComponent<BoxCollision>();
             actors.back()->AddComponent<Transform>();
             actors.back()->AddComponent<SpriteRenderer>();

             actors.back()->GetComponent<Transform>()->position = glm::vec2(grid_x * TILE_SIZE,grid_y * TILE_SIZE);
        }

        i++;
    }
}





std::vector<Tile> walls;
std::vector<Tile> entities;
std::vector<Tile> characters; // init position of characters


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


    ray::InitWindow(window.x,window.y,"App");
    ray::SetWindowState(ray::FLAG_VSYNC_HINT);
    ray::RenderTexture2D target = ray::LoadRenderTexture((int)screen.x,(int)screen.y);
    SetTextureFilter(target.texture,ray::TEXTURE_FILTER_POINT);


    ray::Camera2D camera = { 0 };
    camera.target = (ray::Vector2){ 0.0f, 0.0f };                                                        // Center of 0,0
    camera.offset = (ray::Vector2){0,0};    // Center of the screen
    // camera.offset = (Vector2){(float)target.texture.width/ 2, (float)target.texture.height / 2};    // Center of the screen
    camera.rotation = 0.0f;
    camera.zoom = 1.0f;


    /*############################################################
    # Framework init
    ############################################################ */
    std::vector<std::string> spritePaths;
    spritePaths.push_back("res/sprite/tile.png");
    
    Collision::Init(glm::vec2(0.0f,0.0f));  // Collision init 
    SpriteRenderer::Init(spritePaths);      // SpriteRenderer init


    /*############################################################
    # Level init
    ############################################################ */
    SetEntities(actors,level.getLayer("Character"));


    std::cout<<"Actors: "<<actors.size()<<"\n";
    // SetTiles(actors,level.getLayer("Wall"));

    for(Actor* actor : actors)
    {
        actor->Ready();
        actor->Start();

    }

    while (ray::WindowShouldClose() == false)
    {

        /*############################################################
        # Update
        ############################################################ */



        /*############################################################
        # Rendering     *Draw to the render texture
        ############################################################ */
        ray::BeginTextureMode(target);
        ray::BeginMode2D(camera);
        ray::ClearBackground(ray::BLACK);

        for(Actor* actor : actors)
        {
             actor->Update();
             actor->Render();
        }

        ray::EndTextureMode();
        ray::EndMode2D();

        /*############################################################
        # Draw to the rennder texture to the screen
        ############################################################ */
        ray::BeginDrawing();
        ray::ClearBackground(ray::BLACK);

        ray::DrawTexturePro(
                target.texture,
                (ray::Rectangle){ 0, 0, (float)target.texture.width, -(float)target.texture.height },    // Source (flipped)
                (ray::Rectangle){ 0, 0, (float)window.x,window.y },                                      // Destination
                (ray::Vector2){0,0},                                                                     // Origin
                0.0f,                                                                               // Rotation
                ray::WHITE
                );

        ray::EndDrawing();
    }


    return 0;
}
