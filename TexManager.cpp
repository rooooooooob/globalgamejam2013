#include "TexManager.hpp"

#ifdef GGJ_DEBUG
    #include <iostream>
#endif

namespace ggj
{

TexManager *TexManager::man = NULL;

TexManager::TexManager()
{
}

TexManager::~TexManager()
{
    for (auto it = textures.begin(); it != textures.end(); ++it)
        delete it->second;
}

void TexManager::load()
{
    if (!man)
        man = new TexManager();
}

void TexManager::unload()
{
    if (man)
        delete man;
    man = NULL;
}

const sf::Texture& TexManager::get(const std::string& id)
{
    if (!man->textures[id])
    {
        man->textures[id] = new sf::Texture();
        man->textures[id]->loadFromFile("img/" + id);
#ifdef GGJ_DEBUG
        std::cout << "Loaded " << id << std::endl;
#endif
    }
    return *(man->textures[id]);
}

}
