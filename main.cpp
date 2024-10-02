#include <iostream>
#include <raylib.h>

using namespace std;

class Ball{
public:
float x,y;
int speedx, speedy;
int radius;

void Draw(){
    DrawCircle(x, y, 20, WHITE);
}

void Update(){
    x += speedx;
    y += speedy;

    if (y + radius >= GetScreenHeight() || y - radius <= 0)
    {
        speedy *= -1;
    }
    if (x + radius >= GetScreenWidth() || x - radius <= 0)
    {
        speedx *= -1;
    }
}
};

class Paddle {
protected:
void LimitMovement(){
    if (y <= 0)
    {
        y = 0;
    }

    if (y + height > GetScreenHeight()){
        y = GetScreenHeight() - height;
    }
}

public:
float x,y;
float width, height;
int speed;

void Draw() {
    DrawRectangle(x, y, width, height, WHITE);
}


void Update() {
    if (IsKeyDown(KEY_UP))
    {
        y = y - speed;

    }
    else if (IsKeyDown(KEY_DOWN))
    {
        y = y + speed;
    }

    LimitMovement();
}

};

class CpuPaddle: public Paddle {
    public:
    void Update(int ball_y){
        if (y + height/2 > ball_y)
        {
            y = y - speed;
        }
        if (y + height/2 <= ball_y)
        {
            y = y + speed;
        }

        LimitMovement();
    }
};

// initialize the instance of the ball
Ball ball;
Paddle player;
CpuPaddle cpu;

int main () {
    cout << "starting the game" << endl;
    const int screen_width = 1280;
    const int screen_height = 800;
    InitWindow(screen_width, screen_height, "My Pong Game!");
    // defining the frame rate
    SetTargetFPS(60);

    // set ball qualities
    ball.radius = 20;
    ball.x = screen_width/2;
    ball.y = screen_height/2;
    ball.speedx = 7;
    ball.speedy = 7;

    // initialize paddle
    player.width = 25;
    player.height = 120;
    player.x = screen_width - player.width - 10;
    player.y = screen_height/2 - player.height/2;
    player.speed = 6;

    // initialize cpu
    cpu.width = 25;
    cpu.height = 120;
    cpu.x = 10;
    cpu.y = screen_height/2 - cpu.height/2;
    cpu.speed = 6;

    while(WindowShouldClose() == false){
        BeginDrawing();

        // ball
        ball.Update();
        player.Update();
        cpu.Update(ball.y);

        // drawing
        ClearBackground(BLACK); // clears the background before drawing the new frames
        ball.Draw();
        cpu.Draw();
        player.Draw();
        // draw line
        DrawLine(screen_width/2, 0, screen_width/2, screen_height, WHITE);

        EndDrawing();
    }

    CloseWindow();
    return 0;
}