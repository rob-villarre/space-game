#ifndef TEXTURE_MANAGER_H
#define TEXTURE_MANAGER_H

#include <memory>
#include <unordered_map>
#include <string>
#include "raylib.h"

class TextureManager {
public:

    // Resource managers should NOT be copyable
    TextureManager(const TextureManager& other) = delete;
    TextureManager(TextureManager&& other) = delete;
    TextureManager& operator=(const TextureManager& other) = delete;

    ~TextureManager() {
        for (auto& [key, texture] : textures) {
            UnloadTexture(texture);
        }
    }

    static Texture2D load(const std::string &filename) {
        auto& textureManager = instance();

        // Check if the resource is already loaded
        auto resIter = textureManager.textures.find(filename);
        if(resIter != textureManager.textures.end()) {
            return resIter->second;
        }
        
        Texture2D texture = LoadTexture(filename.c_str());
        textureManager.textures[filename] = texture;

        return texture;
    }

    static void unload(const std::string &filename) {
        auto& textureManager = instance();

        // Check if the resource is already loaded
        auto it = textureManager.textures.find(filename);
        if(it != textureManager.textures.end()) {
            UnloadTexture(it->second);
            textureManager.textures.erase(it);
        }
    }

    static TextureManager& instance(){
        static TextureManager textureManager;
        return textureManager;
    }

private:
    // The constructor is private so that only the single instance can be used
    TextureManager() {}

    // The map of resources that have been loaded.  
    std::unordered_map<std::string, Texture2D> textures;
};

#endif