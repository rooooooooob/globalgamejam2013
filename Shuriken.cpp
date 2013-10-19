#include "Shuriken.hpp"

#include "TexManager.hpp"
#include "Stage.hpp"
#include "Trig.hpp"
#include <iostream>

namespace ggj
{

Shuriken::Shuriken(Stage * const stage, const sf::Vector2f& pos, const sf::Vector2f& veloc, int team)
    :Attack(stage, NULL, pos, sf::Vector2i(7, 7), team, 1000, 20, veloc)
    ,sprite(TexManager::get("shuriken.png"))
{
    sprite.setOrigin(3, 3);
}

void Shuriken::update()
{
    Attack::update();
    veloc.y += 0.1;
    if (stage->collision(this, tGround))
        this->destroy();
    if (veloc.x > 0)
    {
        sprite.setScale(1, 1);
        sprite.rotate(pointDistance(sf::Vector2f(0, 0), veloc));
    }
    else
    {
        sprite.setScale(-1, 1);
        sprite.rotate(-pointDistance(sf::Vector2f(0, 0), veloc));
    }
    sprite.setPosition(pos + sf::Vector2f(3, 3));
    if (pos.x < -32 || pos.x > stage->getWidth() + 32 || pos.y > stage->getHeight())
        this->destroy();
}

void Shuriken::draw(sf::RenderTarget& target) const
{
    target.draw(sprite);
#ifdef GGJ_DEBUG
    Attack::draw(target);
#endif
}

}
