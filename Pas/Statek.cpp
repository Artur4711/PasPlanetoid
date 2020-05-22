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
    sf::FloatRect statek = getGlobalBounds();
    if(sf::Keyboard::isKeyPressed(sf::Keyboard::Up)&&this->top<=statek.top) {
        move(0,-300*elapsed.asSeconds());
    }
    if(sf::Keyboard::isKeyPressed(sf::Keyboard::Down)&&this->bot>=statek.top+statek.height) {
        move(0,300*elapsed.asSeconds());
    }
    if(sf::Keyboard::isKeyPressed(sf::Keyboard::Left)&&this->left<=statek.left) {
        move(-300*elapsed.asSeconds(),0);
    }
    if(sf::Keyboard::isKeyPressed(sf::Keyboard::Right)&&this->right>=statek.left+statek.width) {
        move(300*elapsed.asSeconds(),0);
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


