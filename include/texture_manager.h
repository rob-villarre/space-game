#ifndef TEXTURE_MANAGER_H
#define TEXTURE_MANAGER_H

#include <memory>
#include <unordered_map>
#include <string>
#include <iostream>
#include "raylib.h"

class TextureManager {
public:
    TextureManager(const TextureManager& other) = delete;
    TextureManager(TextureManager&& other) = delete;
    TextureManager& operator=(const TextureManager& other) = delete;

    ~TextureManager() {}

    static std::shared_ptr<Texture2D> load(const std::string &filename) {
        auto& textureManager = instance();
        std::cout << "Loading texture: " << filename << std::endl;

        // Already loaded?
        auto resIter = textureManager.textures.find(filename);
        if (resIter != textureManager.textures.end()) {
            if (auto texPtr = resIter->second.lock()) {
                std::cout << "Texture already loaded" << std::endl;
                return texPtr;
            }
        }

        // Allocate Texture2D on heap, but don't call delete later
        Texture2D tex = LoadTexture(filename.c_str());
        if (tex.id == 0) {
            std::cerr << "Failed to load texture: " << filename << std::endl;
            return nullptr;
        }

        std::shared_ptr<Texture2D> texturePtr(
            new Texture2D(tex),
            [](Texture2D* tex) {
                if (tex) {
                    std::cout << "Unloading texture: " << tex->id << std::endl;
                    UnloadTexture(*tex);  // frees GPU data
                    delete tex;           // frees the struct itself
                }
            }
        );

        textureManager.textures[filename] = texturePtr;
        std::cout << "Texture loaded successfully" << std::endl;
        return texturePtr;
    }

    static TextureManager& instance() {
        static TextureManager textureManager;
        return textureManager;
    }

private:
    TextureManager() {}
    std::unordered_map<std::string, std::weak_ptr<Texture2D>> textures;
};

#endif
