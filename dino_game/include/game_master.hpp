#ifndef GAME_MASTER_HPP
#define GAME_MASTER_HPP

#include "raylib.h"
#include "dino.hpp"
#include "obstacle.hpp"
#include <iostream>
#include <string_view>

#include <netinet/in.h>
#include <sys/socket.h>
#include <unistd.h>

constexpr int screenWidth{640};
constexpr int screenHeight{480};
constexpr std::string_view title{"Dino Run"};


class GameMaster
{
public:
    GameMaster();
    
    void initGame(void);
    void updateGame(void);
    void drawGame(void);
    void gameLoop(void);
    void restartGame(void);
    void unloadGame(void);

    void initSockets(void);

    ~GameMaster();

private:
    bool gameOver;
    int score;
    int obstaclesOnScreen;
    Sound collisionSound;

    Dino dino;
    std::vector<Obstacle> obstacles;

    struct Socket{
    int clientSocket = -1;
    int serverSocket = -1;
}m_socket;
};

#endif // GAME_MASTER_HPP