#ifndef DINO_HPP
#define DINO_HPP

#include "raylib.h"

#include <iostream>
#include <string>

class Dino
{
public:
    Dino();
    
    void draw(void);
    void update(int);
    void jump(int);

    void loadParams(void);

    Vector2 getPosition();
    Vector2 getSize();

    ~Dino();

private:
    Vector2 position;
    Texture2D texture;
    Sound jumpSound;
    int speed; // Speed of the Dino in px/s
    bool isGrounded;
};

#endif // DINO_HPP