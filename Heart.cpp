#include "Heart.hpp"

#include <cmath>
#include "Blood.hpp"
#include "Stage.hpp"
#include "TexManager.hpp"
#include "Trig.hpp"
#include "Random.hpp"

namespace ggj
{

Heart::Heart(Stage * const stage, const sf::Vector2f& pos, const sf::Vector2f& veloc)
    :Entity(stage, pos, sf::Vector2i(7, 7), sf::Vector2i(-3, -3))
    ,in(TexManager::get("heart0.png"))
    ,out(TexManager::get("heart1.png"))
    ,timer(900)
    ,veloc(veloc)
{
}

void Heart::update()
{
    if (--timer < 0)
        this->destroy();
    if (!stage->collision(this, tGround))
    {
        veloc.y += 0.1;
        pos += veloc;
        sprite.rotate(0.1);
    }
    if (pos.x < -32 || pos.x > stage->getWidth() + 32)
        this->destroy();
    stage->instanceCreate(new Blood(stage, pos, lengthdir((randomf(3) + 2) * (sin(timer / 10.f) + 1) / 2, 75 + rand() % 90), 2));
    sprite.setPosition(pos);
    if (sin(timer / 10.f) > 0)
        sprite.setTexture(out);
    else
        sprite.setTexture(in);
}

void Heart::draw(sf::RenderTarget& target) const
{
    target.draw(sprite);
}

Entity::Type Heart::type() const
{
    return tHeart;
}

}
