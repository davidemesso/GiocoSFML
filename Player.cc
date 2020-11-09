// g++ Game.cpp -lsfml-graphics -lsfml-window -lsfml-system; ./a.out
#include <stdlib.h>
#include <string.h>
#include <SFML/Graphics.hpp> 

using namespace sf;
using namespace std;

class Player : public Drawable
{
private:
    Texture texture;

public:
    string name;  // rip
    float atk; 
    float life;
    Sprite sprite;
    // Inventory inventory
    // animation TO DO

    Player(string name, float life, float attack)
    {
        this->name = name; 
        this->life = life; 
        this->atk  = atk; 

        if (!texture.loadFromFile("npc.png"));
        texture.setSmooth(true);

        sprite.setTexture(texture);
        sprite.setTextureRect(IntRect(0, 0, 32, 32)); // Sprite 32x32
        sprite.setScale(Vector2f(2, 2)); 
    } 

    void draw(sf::RenderTarget &window, sf::RenderStates state) const 
    {
        window.draw(sprite);
    }

    void update()
    {
        
    } 
}; 