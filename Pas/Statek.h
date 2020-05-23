#pragma once

#include <SFML/Graphics.hpp>
#include <Przeszkody.h>


class Statek : public sf::RectangleShape
{
public:
    Statek(sf::Vector2f size,sf::Vector2f position);
    void setSpeed(int vel_x,int vel_y, int vel_r);
    void animate(const sf::Time &elapse);
    void setBounds(int left,int right,int top, int bot);
    void kolizja(std::string where);
    void brak_kolizji();
private:
    void bounce();
    int vel_x_=0;
    int vel_y_=0;
    int vel_r_=0;
    int left=0;
    int right=0;
    int top=0;
    int bot=0;
    bool top_left = false;
    bool top_right = false;
    bool bot_left = false;
    bool bot_right = false;

};
