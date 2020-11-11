#include <SFML/Graphics.hpp> 
#include "Player.cpp"
#include <vector>

using namespace sf;

int main() 
{
    RenderWindow window(VideoMode(600, 600), "Nice game bruh!");
    CircleShape shape(100.f);
    shape.setFillColor(Color::Green);

    Clock clock;
    const float FPS = 60.0f;
    bool redraw = true;

    std::vector<Entity*> entities;

    Player p("Paoli", 12, 12, "npc.png"); 
    entities.push_back(&p);

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

            if (event.type == Event::KeyPressed)
            {
                switch(event.key.code)
                {  
                    case Keyboard::Escape:
                        window.close();
                    case Keyboard::Right:
                        p.setVelocity(1, 0);
                        break;
                    case Keyboard::Left:
                        p.setVelocity(-1, 0);
                        break;
                    case Keyboard::Up:
                        p.setVelocity(0, -1);
                        break;
                    case Keyboard::Down:
                        p.setVelocity(0, 1);
                        break;
                }
            }

            if (event.type == Event::KeyReleased)
                switch (event.key.code)
                {
                    case Keyboard::Right:
                    case Keyboard::Left:
                        p.resetVelocityX();
                        break;
                    case Keyboard::Up:
                    case Keyboard::Down:
                        p.resetVelocityY();
                        break;
                }
        }   

        // Draw
        if(redraw)
        {
            window.clear();

            window.draw(p);
            p.update();
            //window.draw(shape);

            // Con una sola entità sembra stupido ma alla lunga ha senso
            // for(int i = 0; i < entities.size(); i++)
            // {
            //     if(entities[i]->isVisible())
            //         window.draw(*entities[i]);
            //     entities[i]->update();
            // }

            window.display();
        }
    }

    return 0;
}