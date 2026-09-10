#ifndef __SYSTEM_HPP___
#define __SYSTEM_HPP___

#include "Ray.hpp"
#include <entt/entt.hpp>
class System
{

public:
    inline static ray::Texture2D texture = {  };

    static void Init(entt::registry& reg);

    static void Render(entt::registry& reg);

    static void Update(entt::registry& reg);
};
#endif
