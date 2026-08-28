#include <LDtkLoader/Tile.hpp>
#include <raylib.h>
#include <LDtkLoader/Project.hpp>
#include <vector>
#include <string>

struct Tile
{
    Vector2 grid;
    int value = 0;
};

const int TILE_SIZE = 16;





void SetEntities(std::vector<Tile> *tiles,const ldtk::Layer& layer)
{

    if(layer.getType() != ldtk::LayerType::Entities)
    {
        TraceLog(LOG_ERROR,"Ldtk: Not entities layer %s",layer.getName().c_str());
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
            value = 2;
        }
        else
        {
            value = -1;
        }

        tiles->push_back({(float)grid_x,(float)grid_y,value});
    }
}

void SetTiles(std::vector<Tile> *tiles,const ldtk::Layer& layer)
{
    if(layer.getType() != ldtk::LayerType::Tiles)
    {
        TraceLog(LOG_ERROR,"Ldtk: Not tile layer %s",layer.getName().c_str());
    }

    for (const auto& tile : layer.allTiles())
    {
        int grid_x = tile.getGridPosition().x;
        int grid_y = tile.getGridPosition().y;

        tiles->push_back({(float)grid_x,(float)grid_y,tile.tileId});
    }
}





std::vector<Tile> walls;
std::vector<Tile> entities;
std::vector<Tile> characters; // init position of characters




struct Player
{
    Vector2 position = {0,0};
    int health = 100;
    
};

Player player;
int main()
{
    ldtk::Project stage;
    stage.loadFromFile("res/debug.ldtk");
    const auto& world = stage.getWorld();

    const auto& level = world.getLevel(0);

   
    const Vector2 window = {(float)2560,(float)1440};   // 4K Monitor
    //const Vector2 window = {(float)1280,(float)720};  // FullHD Monitor
    //const Vector2 window = {(float)1080,(float)1920}; // Mobile Phone Portrait
    //const Vector2 window = {(float)1920,(float)1080}; // Mobile Phone Landscape
 

    //const Vector2 screen = {(float)2560,(float)1440};   // 4K Monitor
    const Vector2 screen = {(float)1280,(float)720};  // FullHD Monitor
    //const Vector2 screen = {(float)1080,(float)1920}; // Mobile Phone Portrait
    //const Vector2 screen = {(float)1920,(float)1080}; // Mobile Phone Landscape
    
    const Vector2 scale = {(float)window.x/screen.x,(float)window.y/screen.y};


    InitWindow(window.x,window.y,"App");


    RenderTexture2D target = LoadRenderTexture((int)screen.x,(int)screen.y);
    SetTextureFilter(target.texture,TEXTURE_FILTER_POINT);


    Camera2D camera = { 0 };
    camera.target = (Vector2){ 0.0f, 0.0f };                                                        // Center of 0,0
    camera.offset = (Vector2){0,0};    // Center of the screen
    // camera.offset = (Vector2){(float)target.texture.width/ 2, (float)target.texture.height / 2};    // Center of the screen
    camera.rotation = 0.0f;
    camera.zoom = 1.0f;
    
    Texture2D sprite = LoadTexture("res/sprite/tile.png");
    

    SetTiles(&walls,level.getLayer("Wall"));
    SetEntities(&entities,level.getLayer("Object"));
    SetEntities(&characters,level.getLayer("Character"));
    

    for(Tile &tile : characters)
    {
        if(tile.value == 2)
        {
            player.position = (Vector2){tile.grid.x * TILE_SIZE * 3,tile.grid.y * TILE_SIZE * 3};

        }
    }

    while (!WindowShouldClose())
    {

        /*############################################################
        # Update
        ############################################################ */

        float speed = 200;
        // std::cout<<GetFrameTime()<<std::endl;

        if(IsKeyDown(KEY_W))
        {
            player.position.y -= speed * GetFrameTime(); // Adjust movement speed based on frame time
        }
        if(IsKeyDown(KEY_S))
        {
            player.position.y += speed * GetFrameTime();
        }
        if(IsKeyDown(KEY_A))
        {
            player.position.x -= speed * GetFrameTime();
        }
        if(IsKeyDown(KEY_D))
        {
            player.position.x += speed * GetFrameTime();
        }




        /*############################################################
        # Rendering     *Draw to the render texture
        ############################################################ */

        BeginTextureMode(target);
        BeginMode2D(camera);
        ClearBackground(BLACK);
    
        for(Tile &tile : walls)
        {


            DrawTexturePro(
                sprite,
                (Rectangle){ 0,0, (float)TILE_SIZE, (float)TILE_SIZE},     // Source
                (Rectangle){ (float)tile.grid.x * TILE_SIZE * 3,(float)tile.grid.y * TILE_SIZE * 3, (float)TILE_SIZE* 3,(float)TILE_SIZE* 3 },      // Destination
                (Vector2){0,0},                                                     // Origin
                0.0f,                                                               // Rotation
                WHITE
            );

        }

        for(Tile &tile : entities)
        {
            DrawTexturePro(
                sprite,
                (Rectangle){ (float)TILE_SIZE,0, (float)TILE_SIZE, (float)TILE_SIZE},     // Source
                (Rectangle){ (float)tile.grid.x * TILE_SIZE * 3,(float)tile.grid.y * TILE_SIZE * 3, (float)TILE_SIZE* 3,(float)TILE_SIZE* 3 },      // Destination
                (Vector2){0,0},                                                     // Origin
                0.0f,                                                               // Rotation
                WHITE
            );

        }

        // Draw the player

        DrawTexturePro(
                sprite,
                (Rectangle){ (float)TILE_SIZE * 2,0, (float)TILE_SIZE, (float)TILE_SIZE},     // Source
                (Rectangle){ (float)player.position.x,(float)player.position.y, (float)TILE_SIZE* 3,(float)TILE_SIZE* 3 },      // Destination
                (Vector2){0,0},                                                     // Origin
                0.0f,                                                               // Rotation
                WHITE
            );







        EndTextureMode();
        EndMode2D();



        /*############################################################
        # Draw to the rennder texture to the screen
        ############################################################ */
        BeginDrawing();
        ClearBackground(BLACK);

        DrawTexturePro(
                target.texture,
                (Rectangle){ 0, 0, (float)target.texture.width, -(float)target.texture.height },    // Source (flipped)
                (Rectangle){ 0, 0, (float)window.x,window.y },                                      // Destination
                (Vector2){0,0},                                                                     // Origin
                0.0f,                                                                               // Rotation
                WHITE
                );

        EndDrawing();
    }


    return 0;
}
