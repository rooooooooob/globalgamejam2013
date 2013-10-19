#ifndef SHURIKEN_HPP
#define SHURIKEN_HPP

#include "Attack.hpp"

namespace ggj
{

class Shuriken : public Attack
{
    public:
        Shuriken(Stage * const stage, const sf::Vector2f& pos, const sf::Vector2f& veloc, int team);

        void update();
        void draw(sf::RenderTarget& target) const;

    private:
        sf::Sprite sprite;
};

}

#endif


