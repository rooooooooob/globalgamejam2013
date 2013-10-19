#include "Entity.hpp"

namespace ggj
{

Entity::Entity(Stage * const stage, const sf::Vector2f& startPos, const sf::Vector2i& dim, const sf::Vector2i offset)
    :stage(stage)
    ,pos(startPos)
    ,dim(dim)
    ,offset(offset)
    ,dead(false)
{
}

bool Entity::isDead() const
{
    return dead;
}

void Entity::destroy()
{
    dead = true;
}

bool Entity::intersects(const Entity& other, float xoffset, float yoffset) const
{
    const int left      = pos.x + offset.x + xoffset,     oleft   = other.pos.x + other.offset.x;
    const int right     = left + dim.x + xoffset,         oright  = oleft + other.dim.x;
    const int top       = pos.y + offset.y + yoffset,     otop    = other.pos.y + other.offset.y;
    const int bottom    = top + dim.y + yoffset,          obottom = otop + other.dim.y;
    return (left <= oright && right > oleft && top <= obottom && bottom > otop);
}

}
