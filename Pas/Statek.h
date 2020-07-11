#pragma once
#include <Rakieta.h>
#include <Powerup.h>
#include <Boss.h>

class Statek : public Obiekt {
public:
    Statek(const std::string& file,
           std::map <std::string,sf::Image*>Images,
           std::map<std::string,sf::Texture*> Textures,
           std::map<std::string,sf::VertexArray> beginCollisionPointsOfTextures);

    void draw(sf::RenderWindow& W);

    void eventAnalysis(sf::Event& e,std::list <Obiekt*> &Asteroidy,
                       std::map <std::string,sf::Image*> Images,
                       std::map<std::string,sf::Texture*> Textures,
                       std::map<std::string,sf::VertexArray> beginCollisionPointsOfTextures);
    void animate(const sf::Time elapsed,std::map<int,bool>& status,std::list <Obiekt*>& Asteroidy);
    void animate(const sf::Time &elapsed, Statek& statek, std::list<Obiekt*>* collisionList);
    bool reverse;
    bool speedup;
    int rakiet=0;
    int rocketlimit=5;
    int booster=1;
    bool shoot=false;
    sf::Vector2f posBoss;
protected:
};

