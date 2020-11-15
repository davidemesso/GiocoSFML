#include <SFML/Graphics.hpp> 
#include "Player.cpp"
#include "Enemy.cpp"
#include <vector>
#include <random>

using namespace sf;

#define WIDTH 640
#define HEIGHT 600

int main() 
{
    RenderWindow window(VideoMode(WIDTH, HEIGHT), "Nice game bruh!");

    Clock clock;
    const float FPS = 60.0f;
    bool redraw = true;

    std::vector<Enemy*> enemies;

    int kills = 0;
    Font font;
    if (!font.loadFromFile("font/Gioco-Regular.ttf"));
    Text killCounter;
    Text lifeCounter;

    killCounter.setFont(font);
    killCounter.setCharacterSize(48);  
    killCounter.setColor(sf::Color::Red);

    lifeCounter.setFont(font);
    lifeCounter.setCharacterSize(48);  
    lifeCounter.setColor(sf::Color::Red);

    Player p("Lapis", 500, 12, "img/character.png");
    Enemy e("vila", 50, 12, "img/log.png", &p); 
    enemies.push_back(&e);
    for(int i = 0; i < 3; i++)
        enemies.push_back(new Enemy("vila", 50, 12, "img/log.png", &p));

    Texture background;
    if (!background.loadFromFile("img/tileset.png"));
    background.setSmooth(true);
    background.setRepeated(true);
    Sprite bg(background, IntRect(300, 0, 210, 150));
    bg.setScale(2,2);

    sf::View followPlayer; //private member in class
    followPlayer.setSize(640, 600);
    window.setView(followPlayer);

    while (window.isOpen())
    {
        // Game loop system
        //Wait until 1/60th of a second has passed, then update everything.
        if (clock.getElapsedTime().asSeconds() >= 1.0f / FPS)
        {
            redraw = true; //We're ready to redraw everything
            clock.restart();
        }
        else //Sleep until next 1/60th of a second comes around
        {
            Time sleepTime = seconds((1.0f / FPS) - clock.getElapsedTime().asSeconds());
            sleep(sleepTime);
        }

        // Event
        Event event;
        while (window.pollEvent(event))
        {
            if (event.type == Event::Closed)
                window.close();

            if (event.type == Event::MouseButtonPressed)
                if(event.mouseButton.button == Mouse::Button::Left)
                    p.attacking = true;

            if (event.type == Event::MouseButtonReleased)
                if(event.mouseButton.button == Mouse::Button::Left)
                    p.attacking = false;

            if (event.type == Event::KeyPressed)
            {
                switch(event.key.code)
                {  
                    case Keyboard::Escape:
                        window.close();
                    case Keyboard::D:
                        p.setVelocity(1, p.getVelocity().y);
                        break;
                    case Keyboard::A:
                        p.setVelocity(-1, p.getVelocity().y);
                        break;
                    case Keyboard::W:
                        p.setVelocity(p.getVelocity().x, -1);
                        break;
                    case Keyboard::S:
                        p.setVelocity(p.getVelocity().x, 1);
                        break;
                }
            }

            if (event.type == Event::KeyReleased)
                switch (event.key.code)
                {
                    case Keyboard::D:
                    case Keyboard::A:
                        p.resetVelocityX();
                        break;
                    case Keyboard::W:
                    case Keyboard::S:
                        p.resetVelocityY();
                        break;
                }
            
            if (event.type == sf::Event::Resized)
            {
                // update the view to the new size of the window
                sf::FloatRect visibleArea(0.f, 0.f, event.size.width, event.size.height);
                window.setView(sf::View(visibleArea));
            }

            p.animate();
        }   

        p.update();

        std::random_device rd; // obtain a random number from hardware
        std::mt19937 gen(rd()); // seed the generator
        std::uniform_int_distribution<> distr(-300, 300);
        std::uniform_int_distribution<> poss(0, 300);

        Vector2f pos = Vector2f(distr(gen), distr(gen));
        if(poss(gen) > 292 && enemies.size() <= 20)
            enemies.push_back(new Enemy("vila", 50, 12, "img/log.png", &p, pos));

        for(int i = enemies.size()-1; i >= 0; i--)
        {
            enemies[i]->update();
            if(!enemies[i]->isVisible())
            {
                enemies.erase(enemies.begin()+i);
                kills++;
            }
        }

        // Draw
        if(redraw)
        {
            window.clear();
            window.draw(bg);
            p.draws(window);

            for(int i = 0; i < enemies.size(); i++)
            {
                enemies[i]->draws(window);     
                p.interact(enemies[i]);    
            } 

            followPlayer.setCenter(p.getPosition());
            window.setView(followPlayer);

            killCounter.setPosition(followPlayer.getCenter().x - WIDTH/2, followPlayer.getCenter().y - HEIGHT/2); 
            lifeCounter.setPosition(followPlayer.getCenter().x, followPlayer.getCenter().y - HEIGHT/2); 

            killCounter.setString("Nemici uccisi; " + to_string(kills));
            lifeCounter.setString("Vita; " + to_string(static_cast<int>(p.life)));
            window.draw(killCounter);
            window.draw(lifeCounter);

            window.display();
        }
    }

    return 0;
}