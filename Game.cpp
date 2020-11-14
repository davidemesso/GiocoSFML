#include <SFML/Graphics.hpp> 
#include "Player.cpp"
#include "Enemy.cpp"
#include <vector>

using namespace sf;

int main() 
{
    RenderWindow window(VideoMode(640, 600), "Nice game bruh!");
    CircleShape shape(100.f);
    shape.setFillColor(Color::Green);

    Clock clock;
    const float FPS = 60.0f;
    bool redraw = true;

    std::vector<Enemy*> enemies;

    Player p("Lapis", 12, 12, "img/character.png");
    Enemy e("vila", 12, 12, "img/log.png", &p); 
    enemies.push_back(&e);
    for(int i = 0; i < 10; i++)
        enemies.push_back(new Enemy("vila", 12, 12, "img/log.png", &p));

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
        for(int i = 0; i < enemies.size(); i++)
            enemies[i]->update();

        // Draw
        if(redraw)
        {
            window.clear();
            window.draw(bg);
            window.draw(p);

            for(int i = 0; i < enemies.size(); i++)
                if(enemies[i]->isVisible())
                    window.draw(*enemies[i]);      

            followPlayer.setCenter(p.getPosition());
            window.setView(followPlayer);

            window.display();
        }
    }

    return 0;
}