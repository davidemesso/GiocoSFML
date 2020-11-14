#ifndef PLAYER
#define PLAYER 

// g++ Game.cpp -lsfml-graphics -lsfml-window -lsfml-system
#include <stdlib.h>
#include <string.h>
#include <SFML/Graphics.hpp> 
#include "Entity.cpp"

using namespace sf;
using namespace std;

class Player : public Entity
{
private:
    float speed = 3;
public:
    // INHERITED ENTITY FIELDS 
    // Inventory inventory

    Player(string name, float life, float attack, string file, Vector2f position = Vector2f(0,0)) : Entity(name, life, attack, file, position)
    {
        // SOME PLAYER STUFF
    } 

    // For future custom drawing function
    // void draw(sf::RenderTarget &window, sf::RenderStates state) const 
    // {
    //     window.draw(sprite);
    // }
}; 

#endif