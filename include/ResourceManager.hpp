#ifndef ___RESOURCE_MANAGER_HPP___
#define ___RESOURCE_MANAGER_HPP___

#include "Ray.hpp"
#include <cassert>
#include <vector>



class ResourceManager
{
public:



    static void LoadTexture(const char* path,const char* indexName);
    static ray::Texture2D GetTexture(const char* indexName);


    static void FreeAll();

private:

    struct Texture
    {
        const std::string path = {};
        const std::string indexName = {};
        const ray::Texture2D texture = {};
    };

    struct Sound
    {
        const std::string path = {};
        const std::string indexName = {};
        const ray::Sound sound = {};
    };


    inline static std::vector<Texture> textures;
    inline static std::vector<Sound> sounds;

    ResourceManager() = default;
    ~ResourceManager() = default;
};

#endif
