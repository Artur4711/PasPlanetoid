#include <Obiekty.h>
#include <Statek.h>

int HEIGHT=1080;
int WIDTH=1920;

std::map <std::string,sf::Image*> Images;
std::map<std::string,sf::Texture*> Textures;
std::map<std::string,sf::VertexArray> beginCollisionPointsOfTextures;
std::list <Obiekty*> Rockets;
std::list <Obiekty*> Asteroidy;
sf::VertexArray Gwiazdy(sf::PrimitiveType::Points,2000);


void ustaw_przeszkody()
{
    for (int j=0; j<200; j++) {
        for (int i=0; i<3; i++) {
            Asteroidy.push_back(new Obiekty("asteroida.png",Images,Textures,beginCollisionPointsOfTextures));
            Asteroidy.back()->setBounds(0,WIDTH,0,HEIGHT);
            Asteroidy.back()->setSpeed(std::rand()%80-40,80,std::rand()%100-50);
            Asteroidy.back()->setScale(1.0f + (rand()%41)/100.0 , 1.0f + (rand()%41)/100.0);
            Asteroidy.back()->setPosition(-50+std::rand()%(HEIGHT+100),-200*j+100*i );
            Asteroidy.back()->setColor(sf::Color(rand()%255,rand()%255,rand()%255,255));
        }
    }
    //gwiazdy
    for (auto i = 0u; i<Gwiazdy.getVertexCount(); i++) {
        Gwiazdy[i].position = sf::Vector2f(rand()%WIDTH,rand()%HEIGHT);
        Gwiazdy[i].color = sf::Color(rand()%156+100,rand()%156+100,rand()%156+100,255);
    }
}
Statek ustaw_statek()
{
    Statek statek("statek.png",Images, Textures,beginCollisionPointsOfTextures);
    statek.setPosition(WIDTH/2,HEIGHT-100);
    statek.setScale(0.6,0.6);
    statek.setBounds(0,WIDTH,0,HEIGHT);
    return statek;
}
void kolizje(Statek &kosmiczny)
{
    sf::FloatRect statek_b = kosmiczny.getGlobalBounds();
    for (auto as : Asteroidy){
        sf::FloatRect asteroida = as->getGlobalBounds();
        if (statek_b.top >= asteroida.top && statek_b.top <= asteroida.top+asteroida.height &&
            statek_b.left >= asteroida.left && statek_b.left <= asteroida.left+asteroida.width)
        {
            kosmiczny.top_left=true;
        }
        if (statek_b.top >= asteroida.top && statek_b.top <= asteroida.top+asteroida.height &&
            statek_b.left+statek_b.width >= asteroida.left && statek_b.left+statek_b.width<=asteroida.left+asteroida.width)
        {
            kosmiczny.top_right=true;
        }
        if (statek_b.top+statek_b.height >= asteroida.top && statek_b.top+statek_b.height <= asteroida.top+asteroida.height &&
            statek_b.left >= asteroida.left && statek_b.left <= asteroida.left+asteroida.width)
        {
            kosmiczny.bot_left=true;
        }
        if (statek_b.top+statek_b.height >= asteroida.top && statek_b.top+statek_b.height <= asteroida.top+asteroida.height &&
            statek_b.left+statek_b.width >= asteroida.left && statek_b.left+statek_b.width<=asteroida.left+asteroida.width)
        {
            kosmiczny.bot_right=true;
        }
    }
}
int main()
{

    sf::RenderWindow window(sf::VideoMode(WIDTH, HEIGHT), "Pas planetoid");
    window.setFramerateLimit(60);
    window.setKeyRepeatEnabled(false);
    window.setVerticalSyncEnabled(true);
    window.setPosition(sf::Vector2i(0,0));

    sf::Clock clock;
    std::map<int,bool> status;

    ustaw_przeszkody();
    auto kosmiczny = ustaw_statek();

    sf::Event event;
    while (window.isOpen()) {

    //EVENTS
        while (window.pollEvent(event)) {
            if (event.type == sf::Event::Closed || (sf::Keyboard::isKeyPressed(sf::Keyboard::Escape) )) window.close();
            if (event.type==sf::Event::KeyPressed) status[event.key.code]=true;
            if (event.type==sf::Event::KeyReleased)status[event.key.code]=false;

            kosmiczny.eventAnalysis(event,Rockets,Images,Textures,beginCollisionPointsOfTextures);
        }

    //LOGIC
        sf::Time elapsed = clock.restart();
        window.clear(sf::Color(20,20,50));
        kolizje(kosmiczny);
        kosmiczny.animate(elapsed,status,Asteroidy);
        for(auto i=0; i<Gwiazdy.getVertexCount();i++)
        {
            Gwiazdy[i].position.y+=1;
            if(Gwiazdy[i].position.y>HEIGHT)
            {
                Gwiazdy[i].position.y=0;
            }
        }

    //DRAW
        window.draw(Gwiazdy);
        auto as = Asteroidy.begin();
        while (as!=Asteroidy.end()) {
            Obiekty* asteroida = *as;
            asteroida->animate(elapsed,kosmiczny,nullptr,false);
            if (asteroida->isDead()||asteroida->getPosition().y>HEIGHT) {
                delete asteroida;
                as = Asteroidy.erase(as);
            }
            else {
                window.draw(*asteroida);
                as++;
            }
        }
        auto ro = Rockets.begin();
        while(ro!=Rockets.end()) {
            Obiekty* rocket = *ro;
            rocket->animate(elapsed,kosmiczny,&Asteroidy,true);
            if (rocket->isDead()||rocket->getPosition().y<50) {
                delete rocket;
                ro = Rockets.erase(ro);
            }
            else {
                window.draw(*rocket);
                ro++;
            }
        }
        kosmiczny.draw(window);
        window.display();
    }

    return 0;
}
