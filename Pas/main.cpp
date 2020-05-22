#include <SFML/Window.hpp>
#include <SFML/Graphics.hpp>
#include <iostream>
#include <Przeszkody.h>
#include <Statek.h>

std::vector<Przeszkody> ustaw_przeszkody(const int weight, const int height)
{
    std::vector<Przeszkody> asteroidy;
    for (int j=0; j<100; j++) {
        for (int i=0; i<5; i++) {
            sf::Vector2f size(weight/20, height/5);
            sf::Vector2f position(100+std::rand()%600*i, -200*j+10*i );
            asteroidy.emplace_back(Przeszkody(size, position));
        }
    }
    for (auto &as : asteroidy) {
        as.setFillColor(sf::Color(100, 100, 100));
        as.setBounds(0, weight, 0, height);
        as.setSpeed(std::rand()%22-std::rand()%11, 100, (std::rand()%22-std::rand()%11)/10);
    }
    return asteroidy;
}
Statek ustaw_statek(const int weight, const int height)
{
    sf::Vector2f size(weight/20, weight/15);
    sf::Vector2f position(weight/2,height-50);
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
    auto statek = ustaw_statek(window_weight,window_height);

    while (window.isOpen()) {
    //EVENTS

        sf::Event event;

        while (window.pollEvent(event)) {
            if (event.type == sf::Event::Closed)
                window.close();
            if (event.type == sf::Event::KeyReleased) {
                    if (event.key.code == sf::Keyboard::Space) {
                        std::cout << "Space released" << std::endl;
                    }
                }

            if (event.type == sf::Event::MouseButtonPressed) {
                if(event.mouseButton.button == sf::Mouse::Left) {
                }
            }

        }
    //LOGIC
        for (auto as:asteroidy){

        }

        sf::Time elapsed = clock.restart();
        for (auto &as : asteroidy) {
           as.animate(elapsed);
        }
        statek.animate(elapsed);

    //DRAW

        window.clear(sf::Color::Black);
        for (auto &as : asteroidy) {
           window.draw(as);
        }
        window.draw(statek);
        window.display();
    }

    return 0;
}
