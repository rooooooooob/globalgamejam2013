#include "Scenery.hpp"

#include "TexManager.hpp"

namespace ggj
{

Scenery::Scenery(Stage * const stage, const sf::Vector2f& pos, const std::string& fname)
    :Entity(stage, pos, sf::Vector2i(0, 0))
    ,sprite(TexManager::get(fname))
{
    sprite.setPosition(pos);
}

void Scenery::update()
{
    //  shit don't move
}

void Scenery::draw(sf::RenderTarget& target) const
{
    target.draw(sprite);
}

Entity::Type Scenery::type() const
{
    return tScenery;
}

}
