#ifndef ENTITY_HPP
#define ENTITY_HPP

#include <SFML/Graphics.hpp>

namespace ggj
{

class Stage;

class Entity
{
    public:
        enum Type {tPlayer, tHead, tGround, tPlatform, tAttack, tScenery,
                   tBeam, tBlood, tHeart};
        virtual ~Entity() = default;

        virtual void draw(sf::RenderTarget& target) const = 0;
        virtual void update() = 0;
        virtual Type type() const = 0;

        bool isDead() const;
        void destroy();
        bool intersects(const Entity& other, float xoffset = 0, float yoffset = 0) const;

    protected:
        Entity(Stage * const stage, const sf::Vector2f& startPos, const sf::Vector2i& dim, const sf::Vector2i offset = sf::Vector2i(0, 0));

        Stage * const stage;
        sf::Vector2f pos;
        const sf::Vector2i dim;
        const sf::Vector2i offset;
    private:
        bool dead;
};

}

#endif
