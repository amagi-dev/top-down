#include "ResourceManager.hpp"


void ResourceManager::LoadTexture(const char* path,const char* indexName)
{
    for(const auto& texture : textures)
    {
        if(texture.indexName == std::string(indexName))
        {
            return;
        }
   //     assert( !(texture.indexName == std::string(indexName)) && "ResourceManager::LoadTexture: indexName already exists");
    }


    for(const auto& texture : textures)
    {
        if(texture.path == std::string(path))
        {
            return;
        }

        // assert( !(texture.path == std::string(path)) && "ResourceManager::LoadTexture: This file is already loaded");
    }

    ray::Texture2D texture = ray::LoadTexture(path);
    assert(texture.id && "ResourceManager::LoadTexture: Failed to load texture");

    ray::GenTextureMipmaps(&texture);
    ray::SetTextureFilter(texture,ray::TEXTURE_FILTER_POINT);




    textures.emplace_back(Texture{std::string(path),indexName,texture});
}

ray::Texture2D ResourceManager::GetTexture(const char* indexName)
{
    for(const auto& texture : textures)
    {
        if(texture.indexName == std::string(indexName))
        {
            return texture.texture;
        }
    }

    assert(false && "ResourceManager::GetTexture: indexName not found");
}

// Release all resources
void ResourceManager::FreeAll()
{
    for(auto& texture : textures)
    {
        ray::UnloadTexture(texture.texture);
    }

    for(auto& sound : sounds)
    {
        ray::UnloadSound(sound.sound);
    }


}
