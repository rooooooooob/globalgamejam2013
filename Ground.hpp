#ifndef GROUND_HPP
#define GROUND_HPP

#include "Entity.hpp"

namespace ggj
{

class Ground : public Entity
{
    public:
        Ground(Stage * const stage, const sf::Vector2f& pos, const std::string& fname);

        void draw(sf::RenderTarget& target) const;
        void update();
        Entity::Type type() const;

    private:
        sf::Sprite sprite;
};

}

#endif
