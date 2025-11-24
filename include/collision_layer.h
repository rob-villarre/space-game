#ifndef COLLISION_LAYERS_H
#define COLLISION_LAYERS_H

#include <cstdint>

enum class CollisionLayer : uint32_t {
  NONE = 0,
  SHIP = 1 << 0,
  BULLET = 1 << 1,
  ASTEROID = 1 << 2,
  ALL = 0xFFFFFFFF
};

inline bool canCollide(CollisionLayer layer1, CollisionLayer layer2,
                       uint32_t mask1, uint32_t mask2) {
  uint32_t l1 = static_cast<uint32_t>(layer1);
  uint32_t l2 = static_cast<uint32_t>(layer2);
  return (mask1 & l2) || (mask2 & l1);
}

#endif