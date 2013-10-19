#ifndef SCENERY_HPP
#define SCENERY_HPP

#include <string>
#include "Entity.hpp"

namespace ggj
{

class Scenery : public Entity
{
    public:
        Scenery(Stage * const stage, const sf::Vector2f& pos, const std::string& fname);

        void update();
        void draw(sf::RenderTarget& target) const;
        Entity::Type type() const;

    private:
        sf::Sprite sprite;
};

}

#endif
