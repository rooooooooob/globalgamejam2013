#include "Blood.hpp"

#include <sstream>
#include "Stage.hpp"
#include "TexManager.hpp"
#include <iostream>
namespace ggj
{

Blood::Blood(Stage * const stage, const sf::Vector2f& pos, const sf::Vector2f& veloc, int type)
    :Entity(stage, pos, sf::Vector2i(3, 3), sf::Vector2i(-1, -1))
    ,veloc(veloc)
    ,timer(360)
{
    std::stringstream ss;
    ss << "blood"
       << type
       << ".png";
    sprite.setTexture(TexManager::get(ss.str()));
    sprite.setOrigin(3, 3);
}

void Blood::update()
{
    if (--timer < 0)
        this->destroy();
    if (!stage->collision(this, tGround))
    {
        veloc.y += 0.2;
        pos += veloc;
    }
    //if (pos.x < -16 || pos.x > stage->getWidth() + 16)
    //    this->destroy();

    sprite.setPosition(pos);
}

void Blood::draw(sf::RenderTarget& target) const
{
    target.draw(sprite);
}

Entity::Type Blood::type() const
{
    return tBlood;
}


}
