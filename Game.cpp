#include "Game.hpp"

#include "TexManager.hpp"
#include "Stage.hpp"
#include "Input.hpp"

namespace ggj
{

Game::Game()
{
}

Game::~Game()
{
}

int Game::execute()
{
    const int width = 640, height = 480;
    sf::RenderWindow window(sf::VideoMode(width, height), "Global Game Jam 2013");
    window.setFramerateLimit(60);

    Input input;
    TexManager::load();

    pushScene(new Stage("test"));

    while (window.isOpen())
    {
        sf::Event event;
        while (window.pollEvent(event))
        {
            switch (event.type)
            {
                case sf::Event::KeyPressed:
                    switch (event.key.code)
                    {
                        case sf::Keyboard::Escape:
                            window.close();
                            break;
                        default:
                            break;
                    }
                    break;
                case sf::Event::Closed:
                    window.close();
                    break;
                default:
                    break;
            }
        }

        input.update();

        if (!scenes.empty())
            scenes.top()->update();

        window.clear(sf::Color(48, 96, 128));

        if (!scenes.empty())
            scenes.top()->draw(window);

        window.display();
    }
    TexManager::unload();
    return 0;
}

void Game::changeScene(Scene *scene)
{
    if (!scenes.empty())
    {
        scenes.top()->onExit();
        delete scenes.top();
        scenes.pop();
    }
    scenes.push(scene);
    scene->onEnter();
}

void Game::pushScene(Scene *scene)
{
    scenes.push(scene);
    scene->onEnter();
}

}
