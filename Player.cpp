// g++ Game.cpp -lsfml-graphics -lsfml-window -lsfml-system
#include <stdlib.h>
#include <string.h>
#include <SFML/Graphics.hpp> 
#include "AnimatedTexture.cpp"

using namespace sf;
using namespace std;

class Player : public AnimatedSprite
{
public:
    string name; 
    float atk; 
    float life;
    Sprite sprite;
    // Inventory inventory
    // animation TO DO

    Player(string name, float life, float attack) : AnimatedSprite("npc.png")
    {
        this->name = name; 
        this->life = life; 
        this->atk  = atk; 
    } 


    // For future custom drawing function
    // void draw(sf::RenderTarget &window, sf::RenderStates state) const 
    // {
    //     window.draw(sprite);
    // }

    // For future custom update function (every frame or tick)
    // void update()
    // {
        
    // } 
}; 