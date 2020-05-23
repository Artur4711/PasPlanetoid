#include "Statek.h"

Statek::Statek(sf::Vector2f size, sf::Vector2f position)
{
    setSize(size);
    setPosition(position);
}
void Statek::setSpeed(int vel_x,int vel_y, int vel_r)
{
    vel_r_=vel_r;   vel_x_=vel_x;   vel_y_=vel_y;
}
void Statek::animate(const sf::Time &elapsed)
{

    if(!(top_left||top_right||bot_left||bot_right)){
        sf::FloatRect statek = getGlobalBounds();
        if(sf::Keyboard::isKeyPressed(sf::Keyboard::Up)&&this->top<=statek.top) {
            move(0,-200*elapsed.asSeconds());
        }
        if(sf::Keyboard::isKeyPressed(sf::Keyboard::Down)&&this->bot>=statek.top+statek.height) {
            move(0,200*elapsed.asSeconds());
        }
        if(sf::Keyboard::isKeyPressed(sf::Keyboard::Left)&&this->left<=statek.left) {
            move(-200*elapsed.asSeconds(),0);
        }
        if(sf::Keyboard::isKeyPressed(sf::Keyboard::Right)&&this->right>=statek.left+statek.width) {
            move(200*elapsed.asSeconds(),0);
        }
    }
    else{
        if(top_right&&bot_right){
            move(-2000*elapsed.asSeconds(),0);
            top_right=false;
            bot_right=false;
        }
        if(top_left&&top_right){
            move(0,2000*elapsed.asSeconds());
            top_left=false;
            top_right=false;
        }
        if(top_left&&bot_left){
            move(2000*elapsed.asSeconds(),0);
            top_left=false;
            bot_left=false;
        }
        if(top_left){
            move(2000*elapsed.asSeconds(),2000*elapsed.asSeconds());

            top_left=false;
        }
        if(top_right){
            move(-2000*elapsed.asSeconds(),2000*elapsed.asSeconds());

            top_right=false;
        }
        if(bot_left){
            move(2000*elapsed.asSeconds(),-2000*elapsed.asSeconds());

            bot_left=false;
        }
        if(bot_right){
            move(-2000*elapsed.asSeconds(),-2000*elapsed.asSeconds());

            bot_right=false;
        }
    }
    bounce();
}
void Statek::setBounds(int left,int right,int top, int bot)
{
    this->left = left;   this->right = right;
    this->top = top;     this->bot = bot;
}
void Statek::bounce()
{
    sf::FloatRect statek = getGlobalBounds();
    if ((statek.top<= this->top && vel_y_<0)||(statek.top+statek.height>=this->bot && vel_y_>0))
    {
        vel_y_=-vel_y_;
    }
    if ((statek.left <= this->left && vel_x_<0)||(statek.left+statek.width >=this->right && vel_x_>0))
    {
        vel_x_=-vel_x_;
    }
}
void Statek::kolizja(std::string where)
{
    if (where == "top_left") top_left=true;
    if (where == "top_right") top_right=true;
    if (where == "bot_left") bot_left=true;
    if (where == "bot_right") bot_right=true;
}
void Statek::brak_kolizji(){
     top_left = false;
     top_right = false;
     bot_left = false;
     bot_right = false;
}



