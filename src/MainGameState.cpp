#include "MainGameState.hpp"
#include <iostream>

MainGameState::MainGameState()
{
    player.x = 200;
    player.y = 200;
    gravedad = 400;
}

void MainGameState::init()
{

}

void MainGameState::handleInput()
{
    if(IsKeyPressed(KEY_SPACE))
        player.vy = -300;
}

void MainGameState::update(float deltaTime)
{
    player.vy += gravedad * deltaTime;
    player.y += player.vy * deltaTime;

    spawnTimer += deltaTime;
    if(spawnTimer >= spawnEvery) {
        spawnTimer = 0.0f;

        int pipe_y_offset_top = GetRandomValue(PIPE_H/2, GetScreenHeight()/2);
        int x = GetScreenWidth();

        int y_top = -pipe_y_offset_top;
        int y_bot = (PIPE_H - pipe_y_offset_top) + GetRandomValue(PIPE_H/2, GetScreenHeight()/2);

        Rectangle top{x, y_top, PIPE_W, PIPE_H}, bot{x, y_bot, PIPE_W, PIPE_H};
        PipePair pipe_pair{top, bot};
        
        pipes.emplace_back(pipe_pair);
    }

    for(auto& pipe : pipes) {
        pipe.top.x -= PIPE_SPEED * deltaTime;
        pipe.bot.x -= PIPE_SPEED * deltaTime;
    }

    if(!pipes.empty() && pipes.front().bot.x < 0)
        pipes.pop_front();
}

void MainGameState::render()
{
        BeginDrawing();

            ClearBackground(RAYWHITE);

            DrawText("Bienvenido a Flappy Bird DCA", 20, 256, 15, BLACK);

            DrawCircle(player.x, player.y, 17.0, RED);

            for(auto& pipe : pipes) {
                DrawRectangleRec(pipe.top, GREEN);
                DrawRectangleRec(pipe.bot, GREEN);
            }

        EndDrawing();
}