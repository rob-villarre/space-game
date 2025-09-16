#ifndef RESOURCE_MANAGER_H
#define RESOURCE_MANAGER_H

#include "raylib.h"
#include <memory>
#include <unordered_map>
#include <string>

template <typename T, T(*LoadFunc)(const char*), void(*UnloadFunc)(T)>
class ResourceManager {
private:
    std::unordered_map<std::string, std::weak_ptr<T>> resources;
    ResourceManager() {};
    
public:
    ResourceManager(const ResourceManager& other) = delete;
    ResourceManager(ResourceManager&& other) = delete;
    ResourceManager& operator=(const ResourceManager& other) = delete;

    ~ResourceManager() {}

    static std::shared_ptr<T> load(const std::string &filename) {
        auto& manager = instance();

        // Already loaded?
        auto it = manager.resources.find(filename);
        if (it != manager.resources.end()) {
            if (auto ptr = it->second.lock()) {
                return ptr;
            }
        }

        T resource = LoadFunc(filename.c_str());
        if (resource.id == 0) {
            return nullptr;
        }

        std::shared_ptr<T> ptr(
            new T(resource),
            [](T* resource) {
                if (resource) {
                    UnloadFunc(*resource);
                    delete resource;
                }
            }
        );

        manager.resources[filename] = ptr;
        return ptr;
    }

    static ResourceManager& instance() {
        static ResourceManager manager;
        return manager;
    }
};

// Predefined resource managers.
// Manages loading of textures.
typedef ResourceManager<Texture2D, LoadTexture, UnloadTexture> TextureManager;

// Manages loading of sounds. 
typedef ResourceManager<Sound, LoadSound, UnloadSound> SoundManager;

#endif