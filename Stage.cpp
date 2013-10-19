#include "Stage.hpp"

#include <cstdlib>
#include "Player.hpp"
#include "Ground.hpp"
#include "Scenery.hpp"

namespace ggj
{

Stage::Stage(const std::string& name)
    :Scene()
    ,width(640)
    ,height(480)
{
    //  load the file and shit
}

Stage::~Stage()
{
}

void Stage::draw(sf::RenderTarget& target) const
{
    for (auto it = entities.begin(); it != entities.end(); ++it)
        (*it)->draw(target);
}

void Stage::update()
{
    for (auto it = entities.begin(); it != entities.end();)
    {
        (*it)->update();
        if ((*it)->isDead())
        {
            delete *it;
            *it = entities.back();
            entities.pop_back();
        }
        else
            ++it;
    }
}

void Stage::onEnter()
{
    entities.push_back(new Player(this, sf::Vector2f(96, 320), 0, 0, "blue"));
    entities.push_back(new Player(this, sf::Vector2f(640 - 96, 320), 1, 1, "red"));
    //add a floor and shit or something
    for (int i = 0; i < 640; i += 32)
    {
        for (int j = 1; j < 4; ++j)
            entities.push_back(new Ground(this, sf::Vector2f(i, 480 - j * 32), "dirt.png"));
        entities.push_back(new Scenery(this, sf::Vector2f(i, 480 - 3 * 32 - 6), (rand() % 2 ? "grass0.png" : "grass1.png")));
    }
    entities.reserve(0xFFFF);
}

void Stage::onExit()
{
    for (auto it = entities.begin(); it != entities.end(); ++it)
        delete *it;
    entities.clear();
}

Entity* Stage::collision(const Entity *caller, Entity::Type type, float xoffset, float yoffset) const
{
    for (auto it = entities.begin(); it != entities.end(); ++it)
    {
        if (*it != caller && (*it)->type() == type && caller->intersects(**it, xoffset, yoffset))
            return *it;
    }
    return NULL;
}

void Stage::collision(std::vector<Entity*>& results, const Entity *caller, Entity::Type type, float xoffset, float yoffset) const
{
    results.clear();
    for (auto it = entities.begin(); it != entities.end(); ++it)
    {
        if (*it != caller && (*it)->type() == type && caller->intersects(**it, xoffset, yoffset))
            results.push_back(*it);
    }
}

void Stage::instanceCreate(Entity *instance)
{
    entities.push_back(instance);
}

int Stage::getWidth() const
{
    return width;
}

int Stage::getHeight() const
{
    return height;
}

}
