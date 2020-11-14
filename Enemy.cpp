#ifndef ENEMY
#define ENEMY

#include <stdlib.h>
#include <string.h>
#include <SFML/Graphics.hpp> 
#include "Entity.cpp"

using namespace sf;
using namespace std;

class Enemy : public Entity
{
private:
    float speed = 3;
public:
    // INHERITED ENTITY FIELDS 
    // Inventory inventory

    Enemy(string name, float life, float attack, string file, Vector2f position = Vector2f(0,0)) : Entity(name, life, attack, file, position)
    {
        // SOME PLAYER STUFF
    } 


    // For future custom drawing function
    // void draw(sf::RenderTarget &window, sf::RenderStates state) const 
    // {
    //     window.draw(sprite);
    // }

    // For future custom update function (every frame or tick)
    void update()
    {
        AnimatedSprite::update();
        // search for player pos
    } 
}; 

#endif