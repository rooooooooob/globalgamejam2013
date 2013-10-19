#ifndef STAGE_HPP
#define STAGE_HPP

#include <vector>
#include "Scene.hpp"
#include "Entity.hpp"

namespace ggj
{

class Stage : public Scene
{
    public:
        Stage(const std::string& name);
        ~Stage();

        void draw(sf::RenderTarget& target) const;
        void update();

        void onEnter();
        void onExit();

        Entity* collision(const Entity *caller, Entity::Type type, float xoffset = 0, float yoffset = 0) const;
        void collision(std::vector<Entity*>& results, const Entity *caller, Entity::Type type, float xoffset = 0, float yoffset = 0) const;
        void instanceCreate(Entity *instance);

        int getWidth() const;
        int getHeight() const;

    private:
        std::vector<Entity*> entities;
        int width;
        int height;
};

}

#endif
