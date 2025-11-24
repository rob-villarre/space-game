#ifndef RESOURCE_MANAGER_H
#define RESOURCE_MANAGER_H

#include <memory>
#include <stdexcept>
#include <string>
#include <unordered_map>

#include "raylib.h"

template <typename T, T (*LoadFunc)(const char *), void (*UnloadFunc)(T),
          bool (*IsValidFunc)(T)>
class ResourceManager {
 private:
  std::unordered_map<std::string, std::weak_ptr<T>> resources;
  ResourceManager(){};

 public:
  ResourceManager(const ResourceManager &other) = delete;
  ResourceManager(ResourceManager &&other) = delete;
  ResourceManager &operator=(const ResourceManager &other) = delete;

  ~ResourceManager() {}

  static std::shared_ptr<T> Load(const std::string &filename) {
    auto &manager = Instance();

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

    std::shared_ptr<T> ptr(new T(resource), [](T *resource) {
      if (resource) {
        UnloadFunc(*resource);
        delete resource;
      }
    });

    manager.resources[filename] = ptr;
    return ptr;
  }

  static ResourceManager &Instance() {
    static ResourceManager manager;
    return manager;
  }
};

// Predefined resource managers.
typedef ResourceManager<Texture2D, LoadTexture, UnloadTexture, IsTextureValid>
    TextureManager;
typedef ResourceManager<Sound, LoadSound, UnloadSound, IsSoundValid>
    SoundManager;
typedef ResourceManager<Music, LoadMusicStream, UnloadMusicStream, IsMusicValid>
    MusicManager;

#endif