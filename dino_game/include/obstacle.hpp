#ifndef OBSTACLE_HPP
#define OBSTACLE_HPP

#include "raylib.h"

#include <iostream>
#include <string>
#include <vector>
#include <random>
#include <array>

constexpr int interObstacleDistance{400}; // Distance between obstacles is 200 px
constexpr int maxScreenObstacles{3};
const std::vector<std::string> obstacleTypes = {"dino_game/resources/1_Cactus.png", "dino_game/resources/3_Cactus.png", "dino_game/resources/Pterodactyl.png"};

class Obstacle
{
public:
    Obstacle(std::string _obstacleType);

    void draw(void);
    void update();

    void loadParams(std::string);

    Vector2 getPosition();
    Vector2 getSize();

    std::string getType();

    ~Obstacle();

private:
    std::string type;  // "1_Cactus", "3_Cactus" or "Pterodactyl"
    Vector2 position;
    Texture2D texture;
    int obstacleSpeed; // Speed of the Obstacle in px/s
};

std::string getRandomObstacle();

#endif // OBSTACLE_HPP
