#ifndef ATTACK_HPP
#define ATTACK_HPP

#include "Entity.hpp"

namespace ggj
{

class Attack : public Entity
{
    public:
        Attack(Stage * const stage, const sf::Vector2f *follow, const sf::Vector2f& cpos, const sf::Vector2i& dim, int team, int time, float damage, const sf::Vector2f& veloc = sf::Vector2f(0, 0));

        virtual void draw(sf::RenderTarget& target) const;
        virtual void update();
        Entity::Type type() const;

        float getDamage() const;
        int getTeam() const;

    protected:
        const sf::Vector2f *follow;
        sf::Vector2f cpos;
        sf::Vector2f veloc;

    private:
        int team;
        int time;
        float damage;
#ifdef GGJ_DEBUG
        sf::RectangleShape rect;
#endif
};

}

#endif
