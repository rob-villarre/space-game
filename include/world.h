#ifndef WORLD_H
#define WORLD_H

#include <vector>
#include <memory>
#include "entity.h"
#include "ship.h"
#include "asteroid.h"
#include "bullet.h"

class World {

public:

    static World& Instance();

    void Initialize();

    void Draw();

    void Update();

    void CheckCollisions();

    template<typename T, typename... Args>
    void Instantiate(Args&&... args) {
        static_assert(std::is_base_of<Entity, T>::value, "T must derive from Entity");
        if constexpr (std::is_same<T, Asteroid>::value) {
            asteroids.emplace_back(std::make_unique<Asteroid>(std::forward<Args>(args)...));
        } else if constexpr (std::is_same<T, Bullet>::value) {
            bullets.emplace_back(std::make_unique<Bullet>(std::forward<Args>(args)...));
        } else if constexpr (std::is_same<T, Ship>::value) {
            ship = std::make_shared<Ship>(std::forward<Args>(args)...);
        } else {
            static_assert(sizeof(T) == 0, "Type T is not a supported entity type");
        }
    }
    
private:
    World() {};
    World(const World&) = delete;
    World(World&&) = delete;
    World& operator=(const World&) = delete;
    World & operator=(World&&) = delete;

    std::vector<std::unique_ptr<Asteroid>> asteroids;
    std::vector<std::unique_ptr<Bullet>> bullets;
    std::shared_ptr<Ship> ship;
};

#endif