#include "Player.hpp"

#include <iostream>
#include <string>
#include <sstream>
#include <vector>
#include "TexManager.hpp"
#include "Input.hpp"
#include "Stage.hpp"
#include "Trig.hpp"
#include "Attack.hpp"
#include "Shuriken.hpp"
#include "Blood.hpp"
#include "Random.hpp"
#include "Heart.hpp"

namespace ggj
{

static const int SWORD_ANIM_FRAMES = 4;
static const float SWORD_ANIM_SPEED = 12;
static const float SWORD_ANIM_TIME = SWORD_ANIM_FRAMES * SWORD_ANIM_SPEED;
static const float ANIM_SPEED = 0.15;
static const float SPEED = 2;
static const float GRAVITY = 0.15;
static const int SWORD_DAMAGE = 50;
static const int AIM_SPEED = 2;

Player::Player(Stage * const stage, const sf::Vector2f& pos, int id, int team, const std::string& character)
    :Entity(stage, pos, sf::Vector2i(16, 24), sf::Vector2i(-8, 0))
    ,character(character)
    ,team(team)
    ,id(id)
    ,aimer(TexManager::get("aimer.png"))
    ,state(Active)
    ,frame(0)
    ,maxhp(100)
    ,hp(maxhp)
    ,prevPos(pos)
    ,head(this)
    ,shurikenCooldown(0)
    ,lastUsedWep(0)
    ,timer(0)
{
    std::stringstream ss;
    for (int i = 0; i < 4; ++i)
    {
        ss << character
           << i
           << ".png";
        runningAnim[i] = &TexManager::get(ss.str());
        ss.str("");
    }
    for (int i = 0; i < SWORD_ANIM_FRAMES; ++i)
    {
        ss << character
           << "sword"
           << i
           << ".png";
        swordAnim[i] = &TexManager::get(ss.str());
        ss.str("");
    }
    for (int i = 0; i < 2; ++i)
    {
        ss << character
           << "shuriken"
           << i
           << ".png";
        shurikenAnim[i] = &TexManager::get(ss.str());
        ss.str("");
    }
    body.setOrigin(12, 0);
    arm.setOrigin(24, 10);
    aimer.setOrigin(4, 4);
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

void Player::update()
{
    switch (state)
    {
        case Active:
            //attacking controls
            if (Input::isKeyReleased(id, Input::Sword))
            {
                lastUsedWep = 0;
                state = Attacking;
                timer = SWORD_ANIM_TIME;
                stage->instanceCreate(new Attack(stage, &pos, sf::Vector2f(-6, -16) + lengthdir(4, armAngle), sf::Vector2i(12, 12), team, timer, SWORD_DAMAGE, sf::Vector2f((body.getScale().x > 0 ? 0.4 : -0.4), 0.25)));
            }

            if (Input::isKeyPressed(id, Input::Throw))
            {
                lastUsedWep = 1;
                if (shurikenCooldown == 0)
                {
                    stage->instanceCreate(new Shuriken(stage, pos + lengthdir(12, armAngle), lengthdir(8, armAngle), team));
                    shurikenCooldown = 16;
                }
            }

            if (Input::isGamepad(id))
            {
            }
            else
            {
                if (body.getScale().x > 0)
                {
                    while (armAngle >= 360)
                        armAngle -= 360;
                    while (armAngle < 0)
                        armAngle += 360;
                    if (armAngle > 90 && armAngle < 270)
                        armAngle = 90 - (armAngle - 90);
                    if (Input::isKeyHeld(id, Input::Up))
                    {
                        armAngle += AIM_SPEED;
                    }
                    else if (Input::isKeyHeld(id, Input::Down))
                    {
                        armAngle -= AIM_SPEED;
                    }
                }
                else
                {
                    while (armAngle >= 360)
                        armAngle -= 360;
                    while (armAngle < 0)
                        armAngle += 360;
                    if (armAngle < 90)
                        armAngle = 90 + (90 - armAngle);
                    if (armAngle > 270)
                        armAngle = 270 - (armAngle - 270);
                    if (Input::isKeyHeld(id, Input::Up))
                    {
                        armAngle -= AIM_SPEED;
                    }
                    else if (Input::isKeyHeld(id, Input::Down))
                    {
                        armAngle += AIM_SPEED;
                    }
                }
            }

            if (lastUsedWep == 0)
            {
                arm.setTexture(*swordAnim[0]);
            }
            else
            {
                arm.setTexture(*shurikenAnim[!shurikenCooldown]);
            }

            arm.setRotation(360 - armAngle);


            if (shurikenCooldown > 0)
                --shurikenCooldown;


            break;
        case Recovering:
            if (timer == 0)
                state = Active;
            break;
        case Attacking:
            if (timer == 0)
            {
                state = Active;
                arm.setTexture(*swordAnim[0]);
            }
            else
                arm.setTexture(*swordAnim[(int) (SWORD_ANIM_FRAMES - timer / SWORD_ANIM_SPEED)]);
            break;
    }
    if (state == Active || state == Attacking)
    {
        //  getting hurt and shit
        std::vector<Entity*> results;
        stage->collision(results, this, tAttack);
        for (auto it = results.begin(); it != results.end(); ++it)
        {
            Attack *other = (Attack*) *it;
            if (other->getTeam() != team)
            {
                for (int i = 0; i < 4; ++i)
                    stage->instanceCreate(new Blood(stage, pos, lengthdir(2 + randomf(3), choose({randomf(360), 45 + randomf(90)}))));

                hp -= other->getDamage();
                state = Recovering;
                timer = 32;
                other->destroy();
                break;
            }
        }
        //  movement
        if (Input::isKeyHeld(id, Input::Right))
        {
            if (!stage->collision(this, tGround, SPEED))
            {
                frame += ANIM_SPEED;
                pos.x += SPEED;
                body.setScale(1, 1);
                head.sprite.setScale(1, 1);
            }
        }
        if (Input::isKeyHeld(id, Input::Left))
        {
            if (!stage->collision(this, tGround, -SPEED))
            {
                frame += ANIM_SPEED;
                pos.x -= SPEED;
                body.setScale(-1, 1);
                head.sprite.setScale(-1, 1);
            }
        }

        if (stage->collision(this, tGround, 0, 1) || (gravity >= 0 && stage->collision(this, tPlatform, 0, 1)))
        {
            if (Input::isKeyPressed(id, Input::Jump))
            {
                gravity = -4;
            }
        }
        if (gravity > 5)
            gravity = 5;
        pos.y += gravity;
    }

    //rebirth
    if (hp <= 0)
    {
        int n = 16 + randomf(16);
        for (int i = 0; i < n; ++i)
            stage->instanceCreate(new Blood(stage, pos, lengthdir(2 + randomf(3), choose({randomf(360), 45 + randomf(90)}))));
        stage->instanceCreate(new Heart(stage, pos, lengthdir(3 + randomf(4), 60 + randomf(60))));
        hp = maxhp;
        pos.x = 32 + rand() % (stage->getWidth() - 64);
        pos.y = -32;
    }

    if (!stage->collision(this, tGround, 0, 1) && (gravity < 0 || !stage->collision(this, tPlatform, 0, 1)))
    {
        gravity += GRAVITY;
    }
    else
    {
        pos.y = prevPos.y;
        gravity = 0;
        while (!stage->collision(this, tGround, 0, 1) && (gravity < 0 || !stage->collision(this, tPlatform, 0, 1)))
        {
            ++pos.y;
        }
    }

    pos.y += gravity;

    if (pos.x > 640)
        pos.x = 640;
    else if (pos.x < 0)
        pos.x = 0;

    prevPos = pos;

    if (timer >= 0)
        --timer;

    while (frame > 4)
        frame -= 4;
    body.setPosition(pos);
    body.setTexture(*runningAnim[(int) frame]);
    arm.setPosition(pos);
    arm.setScale(1, body.getScale().x);
    aimer.setPosition(pos + lengthdir(64, armAngle));

    head.update();
#ifdef GGJ_DEBUG
    rect.setPosition(pos + sf::Vector2f(offset.x, offset.y));
#endif
}

void Player::draw(sf::RenderTarget& target) const
{
    target.draw(body);
    head.draw(target);
    target.draw(arm);
    target.draw(aimer);
#ifdef GGJ_DEBUG
    target.draw(rect);
#endif
}

Entity::Type Player::type() const
{
    return tPlayer;
}

}
