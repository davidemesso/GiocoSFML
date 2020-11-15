#ifndef COIN
#define COIN 

#include <stdlib.h>
#include <string.h>
#include <SFML/Graphics.hpp> 
#include "Player.cpp"

using namespace sf;
using namespace std;

class Coin : public Sprite
{
private:
    Texture texture;
    bool animatingSpawn = true;
    int state = 0;
    int expireTime = 200;
    int animationSpeed = 5;
    int animationTime = animationSpeed;
public:

    Coin() {};
    
    Coin(Vector2f position) 
    {
        if (!texture.loadFromFile("img/coin.png"));
            texture.setSmooth(true);

        // Set fields inherited from sf::Sprite for rendering
        setTexture(texture);
        setTextureRect(IntRect(0, 0, 32, 32)); 
        setScale(Vector2f(1, 1)); 
        setPosition(position);
    };

    bool collect(Player* p)
    {
        if(animatingSpawn)
            return false;

        Vector2f pos = getPosition();
        Vector2f ePos = p->getPosition();
        if(abs(pos.x-ePos.x) < 20 && abs(pos.y-ePos.y) < 20)
        {
            p->coins++;
            return true;
        }
        return false;
    }

    bool update()
    {
        if(!animationTime-- && animatingSpawn)
        {
            if(state != 2)
                state++;
            else
            {
                state = 0;
                animatingSpawn = false;
            }

            animationTime = animationSpeed;
            setTextureRect(IntRect(32 * state, 0, 32, 32));
        }

        if(expireTime-- < 0)
            return true;

        return false;
    } 
}; 

#endif