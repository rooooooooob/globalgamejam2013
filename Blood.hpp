#ifndef BLOOD_HPP
#define BLOOD_HPP

#include <cstdlib>
#include "Entity.hpp"

namespace ggj
{

class Blood : public Entity
{
    public:
        Blood(Stage * const stage, const sf::Vector2f& pos, const sf::Vector2f& veloc, int type = rand() % 3);

        void update();
        void draw(sf::RenderTarget& target) const;
        Entity::Type type() const;
    private:
        sf::Sprite sprite;
        sf::Vector2f veloc;
        int timer;
};

}

#endif
