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
    move(vel_x*elapsed.asSeconds(),vel_y*elapsed.asSeconds());
    rotate(vel_r*elapsed.asSeconds());
    bounce();
    calcTrueCP();
    if (collisionList!=nullptr) {
        for (auto elem : *collisionList) {
            if (this==dynamic_cast<Asteroida*>(elem)) continue;
            if(isCollision(elem)) {
                if(top_right&&bot_right){
                    move(-2000*elapsed.asSeconds(),0);
                    elem->move(2000*elapsed.asSeconds(),0);
                    top_right=false;
                    bot_right=false;
                }
                if(top_left&&top_right){
                    move(0,2000*elapsed.asSeconds());
                    elem->move(0,-2000*elapsed.asSeconds());
                    top_left=false;
                    top_right=false;
                }
                if(top_left&&bot_left){
                    move(2000*elapsed.asSeconds(),0);
                    elem->move(-2000*elapsed.asSeconds(),0);
                    top_left=false;
                    bot_left=false;
                }
                if(top_left){
                    move(2000*elapsed.asSeconds(),2000*elapsed.asSeconds());
                    elem->move(-2000*elapsed.asSeconds(),-2000*elapsed.asSeconds());
                    top_left=false;
                }
                if(top_right){
                    move(-2000*elapsed.asSeconds(),2000*elapsed.asSeconds());
                    elem->move(2000*elapsed.asSeconds(),-2000*elapsed.asSeconds());
                    top_right=false;
                }
                if(bot_left){
                    move(2000*elapsed.asSeconds(),-2000*elapsed.asSeconds());
                    elem->move(-2000*elapsed.asSeconds(),2000*elapsed.asSeconds());
                    bot_left=false;
                }
                if(bot_right){
                    move(-2000*elapsed.asSeconds(),-2000*elapsed.asSeconds());
                    elem->move(2000*elapsed.asSeconds(),2000*elapsed.asSeconds());
                    bot_right=false;
                }
             return;
            }
        }
    }
};
