#pragma once
#include <Obiekt.h>
#include <Statek.h>
#include <Asteroida.h>

class Boss : public Obiekt {
public:
    Boss(const std::string& file,
           std::map <std::string,sf::Image*>Images,
           std::map<std::string,sf::Texture*> Textures,
           std::map<std::string,sf::VertexArray> beginCollisionPointsOfTextures);
    void setSpeed(int velx,int vely, int velr);
    void animate(const sf::Time &elapsed, Statek& statek, std::list<Obiekt*>* collisionList);
    void bounce();
    int moves=0;
    bool atak=false;
    sf::Time t1;

};
