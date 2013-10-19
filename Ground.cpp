#include "Ground.hpp"

#include "TexManager.hpp"

namespace ggj
{

Ground::Ground(Stage * const stage, const sf::Vector2f& pos, const std::string& fname)
    :Entity(stage, pos, sf::Vector2i(TexManager::get(fname).getSize().x, TexManager::get(fname).getSize().y))
    ,sprite(TexManager::get(fname))
{
    sprite.setPosition(pos);
}

void Ground::draw(sf::RenderTarget& target) const
{
    target.draw(sprite);
}

void Ground::update()
{
    //  Updating ground that doesn't move...
}

Entity::Type Ground::type() const
{
    return tGround;
}

}

