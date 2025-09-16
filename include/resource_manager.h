#ifndef RESOURCE_MANAGER_H
#define RESOURCE_MANAGER_H

#include "raylib.h"
#include <memory>
#include <unordered_map>
#include <string>
#include <stdexcept>

template <typename T, T(*LoadFunc)(const char*), void(*UnloadFunc)(T), bool(*IsValidFunc)(T)>
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

        if (!IsValidFunc(resource)) {
            throw std::runtime_error("Failed to load resource: " + filename);
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
typedef ResourceManager<Texture2D, LoadTexture, UnloadTexture, IsTextureValid> TextureManager;
typedef ResourceManager<Sound, LoadSound, UnloadSound, IsSoundValid> SoundManager;
typedef ResourceManager<Music, LoadMusicStream, UnloadMusicStream, IsMusicValid> MusicManager;

#endif