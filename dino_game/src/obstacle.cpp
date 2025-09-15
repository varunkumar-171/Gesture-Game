#include "obstacle.hpp"
#include "game_master.hpp"
#include <stdlib.h>

Obstacle::Obstacle(std::string _obsType)
    : type(_obsType)
{   
    position.x = screenWidth;
    position.y = 300 + 50 - 45;
    texture = LoadTexture(_obsType.c_str()); // TODO: Remove redundant texture loading
    std::cout << "Loaded obstacle: " << _obsType << " at position (" << position.x << ", " << position.y << ")\n";
}


void Obstacle::draw(void)
{
    DrawRectangleLines(position.x, position.y, texture.width, texture.height, WHITE); // Obstacle Hitbox
    // DrawRectangle(position.x, position.y, 50, 50, DARKGRAY); // Placeholder for obstacle
    DrawTexture(texture, position.x, position.y, WHITE);
}

void Obstacle::update()
{
    position.x -= 5; // Move obstacle to the left
}

Vector2 Obstacle::getPosition()
{
    return position;
}

Vector2 Obstacle::getSize()
{
    return {static_cast<float>(texture.width), static_cast<float>(texture.height)};
}

std::string Obstacle::getType()
{
    return type;
}

std::string getRandomObstacle() {

    static std::random_device rd;
    static std::mt19937 gen(rd()); // Standard mersenne_twister_engine seeded with rd()

    static std::uniform_int_distribution<> distrib(0, obstacleTypes.size() - 1);
    int randomIndex = distrib(gen);

    return obstacleTypes[randomIndex];
}

void Obstacle::loadParams(std::string _type)
{
    texture = LoadTexture(_type.c_str());
    std::cout << "Obstacle parameters loaded for type: " << _type << ", height: " << texture.height << ", width: " << texture.width << std::endl;  // print the height and width
}

Obstacle::~Obstacle()
{
    // UnloadTexture(texture); // Unload Dino texture
}