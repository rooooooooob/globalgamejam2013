#ifndef SCENE_HPP
#define SCENE_HPP

#include <SFML/Graphics/RenderTarget.hpp>

namespace ggj
{

class Scene
{
    public:
        virtual ~Scene() = default;

        virtual void draw(sf::RenderTarget& target) const = 0;

        virtual void update() = 0;


        virtual void onEnter() = 0;

        virtual void onExit() = 0;

    protected:
        Scene() = default;
};

}

#endif
