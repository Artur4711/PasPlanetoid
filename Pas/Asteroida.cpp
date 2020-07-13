#include "Asteroida.h"

Asteroida::Asteroida(const std::string& file,
                     std::map <std::string,sf::Image*>Images,
                     std::map<std::string,sf::Texture*> Textures,
                     std::map<std::string,sf::VertexArray> beginCollisionPointsOfTextures) : Obiekt(file,Images,Textures,beginCollisionPointsOfTextures)
{
    setScale(1.0f + (rand()%41)/100.0 , 1.0f + (rand()%41)/100.0);
    setSpeed(std::rand()%90-45,80,std::rand()%100-50);
    setColor(sf::Color(rand()%255,rand()%255,rand()%255,255));
}
void Asteroida::animate(const sf::Time &elapsed, Statek& statek, std::list<Obiekt*>* collisionList)
{
    if(statek.speedup)Sboost=80;
    else Sboost=0;
    if(vel_x>0)move((vel_x+Sboost/2+statek.booster)*elapsed.asSeconds(),(vel_y+Sboost+statek.booster)*elapsed.asSeconds());
    else move((vel_x-Sboost/2-statek.booster)*elapsed.asSeconds(),(vel_y+Sboost+statek.booster)*elapsed.asSeconds());
    rotate(vel_r*elapsed.asSeconds());
    bounce();
    calcTrueCP();
    if (collisionList!=nullptr) {
        for (auto elem : *collisionList) {
            if (!(dynamic_cast<Asteroida*>(elem))){

            }
            else{
                if(isCollision(elem)) {
                    if(rand()%5==1){
                    vel_y=abs(vel_y);
                    vel_x=-vel_x;
                    }
                    elem->setSpeed(-vel_x,-vel_y,30);
                    return;
                }
            }
        }
    }
};
