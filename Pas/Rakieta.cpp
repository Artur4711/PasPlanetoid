#include "Rakieta.h"

Rakieta::Rakieta(const std::string& file,
                     std::map <std::string,sf::Image*>Images,
                     std::map<std::string,sf::Texture*> Textures,
                     std::map<std::string,sf::VertexArray> beginCollisionPointsOfTextures) : Obiekt(file,Images,Textures,beginCollisionPointsOfTextures)
{
    setScale(0.1,0.1);
}

void Rakieta::animate(const sf::Time &elapsed, Statek &statek, std::list<Obiekt*>* collisionList)
{
    move(0,-200*elapsed.asSeconds());
    calcTrueCP();
    if (collisionList!=nullptr) {
        for (auto elem : *collisionList) {
            if (this==elem) continue;
            if(isCollision(elem)) {
             elem->toKill=true;
             this->toKill=true;
             statek.rakiet--;
             return;
            }
        }
    }
    if(getPosition().y<100){
        this->toKill=true;
        statek.rakiet--;

    }
}
