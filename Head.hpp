#ifndef HEAD_HPP
#define HEAD_HPP

#include "Entity.hpp"

namespace ggj
{

class Player;

class Head : public Entity
{
    public:
        Head(const Player * const player);

        void draw(sf::RenderTarget& target) const;
        void update();
        Entity::Type type() const;

    private:
        enum State {Fine, Decapitated};

        const Player * const player;
        sf::Sprite sprite;
        State state;
        sf::Vector2f spd;

#ifdef GGJ_DEBUG
        sf::RectangleShape rect;
#endif

        friend class Player;
};

}

#endif

