#include "Powerup.h"

Powerup::Powerup(const std::string& file,
       std::map <std::string,sf::Image*>Images,
       std::map<std::string,sf::Texture*> Textures,
       std::map<std::string,sf::VertexArray> beginCollisionPointsOfTextures) : Obiekt(file,Images,Textures,beginCollisionPointsOfTextures)
{
    nr = (rand()%3)+1;
    switch (nr) {
        case 1 :
            setColor(sf::Color(255,1,1,255));
        break;
        case 2 :
            setColor(sf::Color(1,255,1,255));
        break;
        case 3 :
            setColor(sf::Color(1,1,255,255));
        break;
        default :
            setColor(sf::Color(255,255,255,255));
    }
    setSpeed(0,100,90);
    setScale(0.5,0.5);
}
void Powerup::animate(const sf::Time &elapsed, Statek& statek, std::list<Obiekt*>* collisionList)
{
    move(vel_x*elapsed.asSeconds(),vel_y*elapsed.asSeconds());
    rotate(vel_r*elapsed.asSeconds());
    calcTrueCP();
}
