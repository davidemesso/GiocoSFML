#ifndef ANIMATEDSPRITE
#define ANIMATEDSPRITE 

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
    bool idle = true;

public:
    int state = 0;
    int animationSpeed = 25;
    int animationTime = animationSpeed;
    Vector2f velocity = Vector2f(0,0);
    int yOffset = 0;
    bool attacking = false;

public:
    AnimatedSprite(string file, Vector2f position = Vector2f(0,0))
    {
        initRendering(file);
        setPosition(position);
    }

    void initRendering(string file)
    {
        if (!texture.loadFromFile(file));
            texture.setSmooth(true);

        // Set fields inherited from sf::Sprite for rendering
        setTexture(texture);
        setTextureRect(IntRect(0, 0, 16, 32)); // Sprite 16x32 in first position
        setScale(Vector2f(2, 2)); 
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
        if(velocity.x == 0)
        {
            if(velocity.y == 1)
                yOffset = 0;
            else if(velocity.y == -1)
                yOffset = 2;
        }
        if(velocity.y == 0)
        {
            if(velocity.x == 1)
                yOffset = 1;
            else if(velocity.x == -1)
                yOffset = 3;
        }



        int attackOffset = attacking ? 4 : 0;
        setTextureRect(IntRect(16 * state, 32 * (yOffset + attackOffset), 16, 32));

        if(velocity == Vector2f(0,0))
            idle = true;
        else 
            idle = false;
    }   

    void update()
    {
        if(attacking)
            velocity = Vector2f(0, 0);

        if(!animationTime--)
        {
            if(!idle || attacking)
                state = (state+1) % 3;
            else 
                state = 0;
            animate();
            animationTime = animationSpeed;
        }
    } 
};

#endif