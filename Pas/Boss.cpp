#include "Boss.h"

Boss::Boss(const std::string& file,
                     std::map <std::string,sf::Image*>Images,
                     std::map<std::string,sf::Texture*> Textures,
                     std::map<std::string,sf::VertexArray> beginCollisionPointsOfTextures) : Obiekt(file,Images,Textures,beginCollisionPointsOfTextures)
{
    setScale(2,2);
    setOrigin((getGlobalBounds().width)/2,(getGlobalBounds().height)/2);
    vel_x=200;
    vel_y=0;
    vel_r=0;
}
void Boss::animate(const sf::Time &elapsed, Statek& statek, std::list<Obiekt*>* collisionList)
{
    t1+=elapsed;
    if(t1>sf::seconds(2)){
        statek.shoot=true;
        statek.posBoss=getPosition();
        t1=sf::seconds(0);
    }
    else{
        statek.shoot=false;
    }
    if(moves==3||atak){
        atak=true;
        if(statek.getPosition().x>this->getPosition().x-600){
            move(100*elapsed.asSeconds(),0);
        }
        if(statek.getPosition().x<this->getPosition().x-600){
            move(-100*elapsed.asSeconds(),0);
        }
        if(statek.getPosition().y>this->getPosition().y-150){
            move(0,100*elapsed.asSeconds());
        }
        if(statek.getPosition().y<this->getPosition().y-150){
            move(0,-100*elapsed.asSeconds());
        }
        if(getPosition().y>=statek.getPosition().y){
            vel_y=-50;
            atak=false;
            moves=0;
        }
    }
    else{
        move(vel_x*elapsed.asSeconds(),vel_y*elapsed.asSeconds());
    }
    bounce();
    calcTrueCP();

}
void Boss::bounce()
{
    sf::FloatRect przeszkoda = getGlobalBounds();
    if ((przeszkoda.top <= -400 && vel_y<0))
    {
        vel_y=0;
    }
    if ((przeszkoda.left <= this->left && vel_x<0)||(przeszkoda.left+przeszkoda.width >=this->right && vel_x>0))
    {
        vel_x=-vel_x;
        moves++;
    }
}
void Boss::setSpeed(int velx,int vely, int velr)
{
    vel_r=velr/1000;   vel_x=velx/1000;   vel_y=vely/1000;
}
