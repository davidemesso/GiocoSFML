#include <SFML/Graphics.hpp>
#include "Player.cpp"

using namespace sf; // <3 Cala

int main() 
{
    RenderWindow window(VideoMode(200, 200), "SFML works!");
    CircleShape shape(100.f);
    shape.setFillColor(Color::Green);

    Clock clock;
    const float FPS = 60.0f;
    bool redraw = true;

    Player p("Paoli", 12, 12); 

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
            else if (event.type == Event::KeyPressed)
                if (event.key.code == Keyboard::Escape)
                    window.close();
                else if (event.key.code == Keyboard::Right)
                    p.move(1, 0);
        }   

        // Draw
        if(redraw)
        {
            window.clear();
            p.update(); 

            window.draw(shape);
            window.draw(p);

            window.display();
        }
    }

    return 0;
}