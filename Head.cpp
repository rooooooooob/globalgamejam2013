#include "Head.hpp"

#include <string>
#include "TexManager.hpp"
#include "Player.hpp"

namespace ggj
{

Head::Head(const Player * const player)
    :Entity(player->stage, player->pos, sf::Vector2i(8, 8), sf::Vector2i(-4, -4))
    ,player(player)
    ,sprite(TexManager::get(player->character + "head.png"))
    ,state(Fine)
{
    pos.y -= 4;
    sprite.setOrigin(4, 4);
#ifdef GGJ_DEBUG
    rect.setSize(sf::Vector2f(dim.x, dim.y));
    rect.setFillColor(sf::Color::Transparent);
    if (player->team == 0)
        rect.setOutlineColor(sf::Color::Blue);
    else if (player->team == 1)
        rect.setOutlineColor(sf::Color::Red);
    rect.setOutlineThickness(1);
#endif
}

void Head::draw(sf::RenderTarget& target) const
{
    target.draw(sprite);
#ifdef GGJ_DEBUG
    target.draw(rect);
#endif
}

void Head::update()
{
    switch (state)
    {
        case Fine:
            pos.x = player->pos.x;
            pos.y = player->pos.y - 4;
            break;
        case Decapitated:
            pos += spd;
            spd.y += 0.15;
            break;
    }
    sprite.setPosition(pos);
#ifdef GGJ_DEBUG
    rect.setPosition(pos + sf::Vector2f(offset.x, offset.y));
#endif
}

Entity::Type Head::type() const
{
    return tHead;
}

}
