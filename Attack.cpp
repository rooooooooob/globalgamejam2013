#include "Attack.hpp"

namespace ggj
{

Attack::Attack(Stage * const stage, const sf::Vector2f *follow, const sf::Vector2f& cpos, const sf::Vector2i& dim, int team, int time, float damage, const sf::Vector2f& veloc)
    :Entity(stage, cpos, dim)
    ,follow(follow)
    ,cpos(cpos)
    ,veloc(veloc)
    ,team(team)
    ,time(time)
    ,damage(damage)
{
#ifdef GGJ_DEBUG
    rect.setSize(sf::Vector2f(dim.x, dim.y));
    rect.setFillColor(sf::Color::Transparent);
    if (team == 0)
        rect.setOutlineColor(sf::Color::Blue);
    else if (team == 1)
        rect.setOutlineColor(sf::Color::Red);
    rect.setOutlineThickness(1);
#endif
}

void Attack::draw(sf::RenderTarget& target) const
{
    //  You can't see attack hitboxes...
#ifdef GGJ_DEBUG
    target.draw(rect);
#endif
}

void Attack::update()
{
    if (--time < 0)
        this->destroy();
    if (follow)
    {
        cpos += veloc;
        pos = *follow + cpos;
    }
    else
        pos += veloc;
#ifdef GGJ_DEBUG
    rect.setPosition(pos);
#endif
}

Entity::Type Attack::type() const
{
    return tAttack;
}

float Attack::getDamage() const
{
    return damage;
}

int Attack::getTeam() const
{
    return team;
}

}
