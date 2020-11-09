#include <SFML/Graphics.hpp>
#include "Player.cc"

using namespace sf; // <3 Cala

int main() 
{
    RenderWindow window(VideoMode(200, 200), "SFML works!");
    CircleShape shape(100.f);
    shape.setFillColor(Color::Green);

    Player p("Paoli", 12, 12); 

    while (window.isOpen())
    {
        Event event;
        while (window.pollEvent(event))
        {
            if (event.type == Event::Closed)
                window.close();
        } 

        window.clear();
        window.draw(shape);
        window.draw(p); // prova
        
        window.display();
    }

    return 0;
}