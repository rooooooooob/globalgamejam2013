#ifndef HEART_HPP
#define HEART_HPP

#include "Entity.hpp"

namespace ggj
{

class Heart : public Entity
{
    public:
        Heart(Stage * const stage, const sf::Vector2f& pos, const sf::Vector2f& veloc);

        void update();
        void draw(sf::RenderTarget& target) const;
        Entity::Type type() const;

    private:
        const sf::Texture& in;
        const sf::Texture& out;
        sf::Sprite sprite;
        int timer;
        sf::Vector2f veloc;
};

}

#endif
