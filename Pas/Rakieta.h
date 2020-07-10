#pragma once
#include <Obiekt.h>
#include <Statek.h>


class Rakieta : public Obiekt {
public:
    Rakieta(const std::string& file,
           std::map <std::string,sf::Image*>Images,
           std::map<std::string,sf::Texture*> Textures,
           std::map<std::string,sf::VertexArray> beginCollisionPointsOfTextures);
    void animate(const sf::Time &elapsed, Statek& statek, std::list<Obiekt*>* collisionList);
};
