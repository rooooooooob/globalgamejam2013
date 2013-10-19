#ifndef PLAYER_HPP
#define PLAYER_HPP

#include <string>
#include "Entity.hpp"
#include "Head.hpp"

namespace ggj
{

class Player : public Entity
{
    public:
        Player(Stage * const stage, const sf::Vector2f& pos, int id, int team, const std::string& character);

        void update();
        void draw(sf::RenderTarget& target) const;
        Type type() const;

    private:
        enum State {Active, Recovering, Attacking};

        const std::string character;
        const int team;
        const int id;
        sf::Sprite body;
        sf::Sprite arm;
        sf::Sprite aimer;
        const sf::Texture *runningAnim[4];
        const sf::Texture *swordAnim[4];
        const sf::Texture *shurikenAnim[2];
        State state;
        float frame;
        float maxhp;
        float hp;
        float gravity;
        sf::Vector2f prevPos;
        Head head;
        int shurikenCooldown;
        int lastUsedWep;
        float armAngle;
        int timer;

#ifdef GGJ_DEBUG
        sf::RectangleShape rect;
#endif

        friend class Head;
};

}

#endif
