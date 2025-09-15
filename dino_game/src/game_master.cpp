#include "game_master.hpp"
#include "raylib.h"
#include <iostream>
#include <string>
#include <vector>
#include <stdlib.h>


GameMaster::GameMaster()
    : gameOver(false), score(0), obstaclesOnScreen(0)
{
    collisionSound = LoadSound("mario-death.mp3");
    m_socket.clientSocket = -1;
    m_socket.serverSocket = -1;
}


void GameMaster::initGame(void)
{
    std::cout << "Initializing game: " << title << " with resolution " << screenWidth << "x" << screenHeight << std::endl;
    // Initialize the window
    SetTargetFPS(60);

    dino.loadParams();
}

void GameMaster::updateGame()
{
    if(!gameOver)
    {
        int command = 0;
        recv(m_socket.clientSocket, &command, sizeof(command), 0);
        dino.update(command);

        if(obstaclesOnScreen  < maxScreenObstacles && (obstacles.empty() || obstacles.back().getPosition().x < screenWidth - (interObstacleDistance + rand() % 640)) )// Add obstacles at random intervals
        {
            std::string randomObstacle = getRandomObstacle();
            obstacles.push_back(Obstacle(randomObstacle));
            obstaclesOnScreen++;
        }

        for(auto& obs : obstacles){
                obs.update();
                Vector2 pos = obs.getPosition();
                // std::cout << "Obstacle type: " << obs.getType() << ", Position: (" << pos.x << ", " << pos.y << ")" << std::endl;

                if(pos.x + obs.getSize().x < 0){ // Remove obstacle from the obstacle queue if it goes off screen
                    if(!obstacles.empty()){
                        obstacles.erase(obstacles.begin());
                    }
                    obstaclesOnScreen--;
                    score++;
            }
        }
        for(auto& obs : obstacles){
            // Collision checking
            if(CheckCollisionRecs({dino.getPosition().x, dino.getPosition().y, dino.getSize().x, dino.getSize().y}, {obs.getPosition().x, obs.getPosition().y, obs.getSize().x, obs.getSize().y})) // Hard coded since texture is not working
            {
                PlaySound(collisionSound);
                gameOver = true;
                std::cout << "Game Over! Final Score: " << score << std::endl;

            }
        }
    }
    else{
        if (IsKeyPressed(KEY_ENTER))
        {
            restartGame();
        }
    }
}

void GameMaster::drawGame()
{
    // drawing
	BeginDrawing();
    ClearBackground(RAYWHITE);

    if(!gameOver)
    {
        dino.draw();
        for(auto& obs : obstacles)
        {
            obs.draw();
        }

        DrawText(TextFormat("Score: %04i", score), 20, 20, 40, BLUE);
    }
    else
    {
        DrawText("Game Over !!", 10, 100, 60, RED);
        DrawText(TextFormat("Score: %04i", score), 10, 170, 40, BLUE);
        DrawText("Press [ENTER] to Restart", 10, 240, 40, DARKGRAY);
    }

    EndDrawing(); // end the frame and get ready for the next one  (display frame, poll input, etc...)
}

void GameMaster::gameLoop(void)
{
    while (!WindowShouldClose())
    {
        updateGame();

        drawGame();
    }
}

void GameMaster::restartGame(void)
{
    obstacles.clear();
    obstaclesOnScreen = 0;
    score = 0;
    gameOver = false;
    std::cout << "Game Restarted!" << std::endl;
}


// Server side socket
void GameMaster::initSockets(void) 
{
    m_socket.serverSocket = socket(AF_INET, SOCK_STREAM, 0);

    sockaddr_in serverAddress;
    serverAddress.sin_family = AF_INET;
    serverAddress.sin_port = htons(8080);
    serverAddress.sin_addr.s_addr = INADDR_ANY;

    bind(m_socket.serverSocket, (struct sockaddr*)&serverAddress, sizeof(serverAddress));

    listen(m_socket.serverSocket, 10);

    m_socket.clientSocket = accept(m_socket.serverSocket, nullptr, nullptr);
}

GameMaster::~GameMaster()
{   
    CloseAudioDevice();
    // destroy the window and cleanup the OpenGL context
	CloseWindow();
}

