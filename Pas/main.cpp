#include <SFML/Window.hpp>
#include <SFML/Graphics.hpp>
#include <iostream>
#include <Obiekty.h>
#include <Statek.h>

std::vector<Obiekty> ustaw_przeszkody(const int weight, const int height)
{
    std::vector<Obiekty> asteroidy;
    for (int j=0; j<100; j++) {
        for (int i=0; i<2; i++) {
            sf::Vector2f size(weight/10, height/4);
            sf::Vector2f position(-50+std::rand()%(weight+100), -200*j+10*i );
            asteroidy.emplace_back(Obiekty(size, position));
        }
    }
    for (auto &as : asteroidy) {
        as.setFillColor(sf::Color(100, 100, 100));
        as.setBounds(0, weight, 0, height);
        as.setSpeed(std::rand()%22-std::rand()%11, 100, 0);
    }
    return asteroidy;
}
Statek ustaw_statek(const int weight, const int height)
{
    sf::Vector2f size(weight/20, weight/15);
    sf::Vector2f position(weight/2,height-100);
    Statek kosmiczny(size,position);
    kosmiczny.setBounds(0,weight,0,height);
    return kosmiczny;
}
void obsluga_kolizji(Statek &statek,std::vector<Obiekty> asteroidy)
{
    sf::FloatRect statek_b = statek.getGlobalBounds();
    for (auto as : asteroidy){
        sf::FloatRect asteroida = as.getGlobalBounds();
        if (statek_b.top >= asteroida.top && statek_b.top <= asteroida.top+asteroida.height &&
            statek_b.left >= asteroida.left && statek_b.left <= asteroida.left+asteroida.width)
        {
            statek.kolizja("top_left");
            std::cout<<"KOLIZJA lewy gorny!!!"<<std::endl;
        }
        if (statek_b.top >= asteroida.top && statek_b.top <= asteroida.top+asteroida.height &&
            statek_b.left+statek_b.width >= asteroida.left && statek_b.left+statek_b.width<=asteroida.left+asteroida.width)
        {
            statek.kolizja("top_right");
            std::cout<<"KOLIZJA prawy gorny!!!"<<std::endl;
        }
        if (statek_b.top+statek_b.height >= asteroida.top && statek_b.top+statek_b.height <= asteroida.top+asteroida.height &&
            statek_b.left >= asteroida.left && statek_b.left <= asteroida.left+asteroida.width)
        {
            statek.kolizja("bot_left");
            std::cout<<"KOLIZJA lewy dolny!!!"<<std::endl;
        }
        if (statek_b.top+statek_b.height >= asteroida.top && statek_b.top+statek_b.height <= asteroida.top+asteroida.height &&
            statek_b.left+statek_b.width >= asteroida.left && statek_b.left+statek_b.width<=asteroida.left+asteroida.width)
        {
            statek.kolizja("bot_right");
            std::cout<<"KOLIZJA prawy dolny!!!"<<std::endl;
        }
    }
}
int main()
{

    sf::Clock clock;
    int window_height = 600;    int window_weight = 800;
    auto asteroidy = ustaw_przeszkody(window_weight,window_height);
    auto kosmiczny = ustaw_statek(window_weight,window_height);

    sf::RenderWindow window(sf::VideoMode(window_weight, window_height), "Pas planetoid");
    window.setFramerateLimit(60);

    while (window.isOpen()) {

    //EVENTS

        sf::Event event;
        while (window.pollEvent(event)) {
            if (event.type == sf::Event::Closed)
                window.close();
        }
    //LOGIC

        obsluga_kolizji(kosmiczny,asteroidy);
        sf::Time elapsed = clock.restart();
        for (auto &as : asteroidy) {
           as.animate(elapsed);
        }
        kosmiczny.animate(elapsed);

    //DRAW

        window.clear(sf::Color::Black);
        window.draw(kosmiczny);
        for (auto &as : asteroidy) {
           window.draw(as);
        }


        window.display();
    }

    return 0;
}
