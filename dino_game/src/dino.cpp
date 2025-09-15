#include "dino.hpp"
#include "game_master.hpp"

static Vector2 dinoInitPos{100, 300};

Dino::Dino()
    : position{100, 300}, isGrounded(true), speed(200)
{   
    texture = LoadTexture("Dino.png");
}

Dino::~Dino()
{
    // UnloadTexture(texture); // Unload Dino texture
}

void Dino::draw(void)
{
    DrawRectangleLines(position.x, position.y, texture.width, texture.height, WHITE); // Dino Hitbox
    DrawTexture(texture, position.x, position.y, WHITE);

    DrawRectangle(0, dinoInitPos.y + texture.height, screenWidth, screenHeight - dinoInitPos.y - texture.height, GREEN); // Ground
}

void Dino::update(int command)
{
    jump(command);
}

void Dino::jump(int command)
{
    float frameTime = GetFrameTime();

    //if(IsKeyPressed(KEY_SPACE) && isGrounded) // Prevents double jump
    if(command == 1 && isGrounded)
    {
        PlaySound(jumpSound);
        speed = 550;
        isGrounded = false;
    }

    if(!isGrounded){
        speed -= 23; // gravity
        position.y -= speed * frameTime;
    }

    if(position.y >= dinoInitPos.y)
    {
        isGrounded = true;
        position.y = dinoInitPos.y;
    }

    

}

void Dino::loadParams(void)
{
    texture = LoadTexture("Dino.png");
    jumpSound = LoadSound("mario-coin.mp3");
}

Vector2 Dino::getPosition()
{
    return position;
}

Vector2 Dino::getSize()
{
    return {static_cast<float>(texture.width), static_cast<float>(texture.height)};
}