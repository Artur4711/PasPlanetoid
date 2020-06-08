#pragma once

#include<Obiekty.h>

class Statek : public Obiekty {
public:
    Statek(const std::string& file,
           std::map <std::string,sf::Image*>Images,
           std::map<std::string,sf::Texture*> Textures,
           std::map<std::string,sf::VertexArray> beginCollisionPointsOfTextures);

    void draw(sf::RenderWindow& W);

    void eventAnalysis(sf::Event& e,std::list <Obiekty*> &Asteroidy,
                       std::map <std::string,sf::Image*> Images,
                       std::map<std::string,sf::Texture*> Textures,
                       std::map<std::string,sf::VertexArray> beginCollisionPointsOfTextures);

    void animate(const sf::Time elapsed,std::map<int,bool>& status,std::list <Obiekty*>& Asteroidy);
};

