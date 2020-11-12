#include <stdlib.h>
#include <iostream>
#include <SFML/Graphics.hpp> 

using namespace sf;
using namespace std;

class AnimatedSprite : public sf::Sprite
{
private:
    Texture texture;
    bool visible = true;

public:
    int state = 0;
    int animationSpeed = 25;
    int animationTime = animationSpeed;
    Vector2f velocity = Vector2f(0, 0);
    int yOffset = 0;

public:
    AnimatedSprite(string file)
    {
        initRendering(file);
    }

    void initRendering(string file)
    {
        if (!texture.loadFromFile(file));
            texture.setSmooth(true);

        // Set fields inherited from sf::Sprite for rendering
        setTexture(texture);
        setTextureRect(IntRect(0, 0, 32, 32)); // Sprite 32x32 in first position
        setScale(Vector2f(1, 1)); 
        setPosition(Vector2f(10, 10));
    }

    void setVisibility(bool visible)
    {   
        this->visible = visible;
    }

    bool isVisible()
    {
        return visible;
    }

    void animate()
    {
        //int xOffset = 0;

        if(velocity.x == 0)
        {
            if(velocity.y == 1)
                yOffset = 0;
            else if(velocity.y == -1)
                yOffset = 3;
        }
        if(velocity.y == 0)
        {
            if(velocity.x == 1)
                yOffset = 2;
            else if(velocity.x == -1)
                yOffset = 1;
        }
        setTextureRect(IntRect(32 * state, 32 * yOffset, 32, 32));

        if(velocity.x == 0 && velocity.y == 0)
            setTextureRect(IntRect(0, 0, 32, 32));
    }   

    void update()
    {
        if(!animationTime--)
        {
            state = (state+1) % 3;
            animate();
            animationTime = animationSpeed;
        }
    } 
};