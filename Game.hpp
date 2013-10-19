#ifndef GAME_HPP
#define GAME_HPP

#include <SFML/Graphics.hpp>
#include <stack>
#include "Scene.hpp"

namespace ggj
{

class Game
{
    public:
        Game();
        ~Game();

        int execute();

        void changeScene(Scene *scene);

        void pushScene(Scene *scene);

    private:
        std::stack<Scene*> scenes;
};

}

#endif
