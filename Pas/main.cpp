#include <SFML/Window.hpp>
#include <SFML/Graphics.hpp>
#include <iostream>
#include <Przeszkody.h>
#include <Statek.h>

std::vector<Przeszkody> ustaw_przeszkody(const int weight, const int height)
{
    std::vector<Przeszkody> asteroidy;
    for (int j=0; j<100; j++) {
        for (int i=0; i<2; i++) {
            sf::Vector2f size(weight/10, height/4);
            sf::Vector2f position(100+std::rand()%weight, -200*j+10*i );
            asteroidy.emplace_back(Przeszkody(size, position));
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

int main()
{

    int window_height = 600;
    int window_weight = 800;

    sf::RenderWindow window(sf::VideoMode(window_weight, window_height), "Pas planetoid");
    sf::Clock clock;
    window.setFramerateLimit(60);

    auto asteroidy = ustaw_przeszkody(window_weight,window_height);
    auto kosmiczny = ustaw_statek(window_weight,window_height);

    while (window.isOpen()) {
    //EVENTS

        sf::Event event;

        while (window.pollEvent(event)) {
            if (event.type == sf::Event::Closed)
                window.close();

        }
    //LOGIC
        sf::FloatRect statek = kosmiczny.getGlobalBounds();
        for (auto as : asteroidy){
            sf::FloatRect asteroida = as.getGlobalBounds();

            if (statek.top >= asteroida.top && statek.top <= asteroida.top+asteroida.height &&
                statek.left >= asteroida.left && statek.left <= asteroida.left+asteroida.width)
            {
                kosmiczny.kolizja("top_left");
                std::cout<<"KOLIZJA lewy gorny!!!"<<std::endl;
            }
            if (statek.top >= asteroida.top && statek.top <= asteroida.top+asteroida.height &&
                statek.left+statek.width >= asteroida.left && statek.left+statek.width<=asteroida.left+asteroida.width)
            {
                kosmiczny.kolizja("top_right");
                std::cout<<"KOLIZJA prawy gorny!!!"<<std::endl;
            }
            if (statek.top+statek.height >= asteroida.top && statek.top+statek.height <= asteroida.top+asteroida.height &&
                statek.left >= asteroida.left && statek.left <= asteroida.left+asteroida.width)
{
                kosmiczny.kolizja("bot_left");
                std::cout<<"KOLIZJA lewy dolny!!!"<<std::endl;
            }
            if (statek.top+statek.height >= asteroida.top && statek.top+statek.height <= asteroida.top+asteroida.height &&
                statek.left+statek.width >= asteroida.left && statek.left+statek.width<=asteroida.left+asteroida.width)
            {
                kosmiczny.kolizja("bot_right");
                std::cout<<"KOLIZJA prawy dolny!!!"<<std::endl;
            }
        }
        sf::Time elapsed = clock.restart();
        for (auto &as : asteroidy) {
           as.animate(elapsed);
        }
        kosmiczny.animate(elapsed);

    //DRAW

        window.clear(sf::Color::Black);
        for (auto &as : asteroidy) {
           window.draw(as);
        }
        window.draw(kosmiczny);
        window.display();
    }

    return 0;
}
