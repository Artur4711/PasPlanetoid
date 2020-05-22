#include "Przeszkody.h"

Przeszkody::Przeszkody(sf::Vector2f size,sf::Vector2f position)
{
       setSize(size);
       setPosition(position);
}
void Przeszkody::setSpeed(int vel_x,int vel_y, int vel_r)
{
    vel_r_=vel_r;   vel_x_=vel_x;   vel_y_=vel_y;
}
void Przeszkody::animate(const sf::Time &elapsed)
{
    move(vel_x_*elapsed.asSeconds(),vel_y_*elapsed.asSeconds());
    rotate(vel_r_*elapsed.asSeconds());
    bounce();
}
void Przeszkody::setBounds(int left,int right,int top, int bot)
{
    this->left = left;   this->right = right;
    this->top = top;     this->bot = bot;
}
void Przeszkody::bounce()
{
    sf::FloatRect przeszkoda = getGlobalBounds();
    if ((przeszkoda.left <= this->left && vel_x_<0)||(przeszkoda.left+przeszkoda.width >=this->right && vel_x_>0))
    {
        vel_x_=-vel_x_;
    }
}

