#include <iostream>
#include <raylib.h>

using namespace std;

Color Green = Color{38, 185, 154, 255};
Color DarkGreen = Color{20, 160, 133, 255};
Color LightGreen = Color{129, 204, 184, 255};
Color Yellow = Color{ 243, 219, 91, 255};

int player_score = 0;
int cpu_score = 0;

class Ball{
public:
float x,y;
int speedx, speedy;
int radius;

void Draw(){
    DrawCircle(x, y, 20, Yellow);
}

void Update(){
    x += speedx;
    y += speedy;

    if (y + radius >= GetScreenHeight() || y - radius <= 0)
    {
        speedy *= -1;
    }
    if (x + radius >= GetScreenWidth()){
        cpu_score += 1;
        resetBall();
    }
    if (x - radius <= 0)
    {
        player_score += 1;
        resetBall();
    }
}

void resetBall(){
    x = GetScreenWidth()/2;
    y = GetScreenHeight()/2;
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
    DrawRectangleRounded(Rectangle{x, y, width, height}, 0.8, 0, WHITE);
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

        // checking for collisions
        if (CheckCollisionCircleRec(Vector2{ball.x, ball.y}, ball.radius, Rectangle{player.x, player.y, player.width, player.height})){
            ball.speedx *= -1;
        }
        if (CheckCollisionCircleRec(Vector2{ball.x, ball.y}, ball.radius, Rectangle{cpu.x, cpu.y, cpu.width, cpu.height})){
            ball.speedx *= -1;
        }

        // drawing
        ClearBackground(DarkGreen); // clears the background before drawing the new frames
        DrawRectangle(screen_width/2, 0, screen_width/2, screen_height, Green);
        DrawCircle(screen_width/2, screen_height/2, 150, LightGreen);


        ball.Draw();
        cpu.Draw();
        player.Draw();
        // draw line
        DrawLine(screen_width/2, 0, screen_width/2, screen_height, WHITE);
        DrawText(TextFormat("%i", cpu_score), screen_width/4 - 20, 20, 80, WHITE);
        DrawText(TextFormat("%i", player_score), 3 * screen_width/4 - 20, 20, 80, WHITE);


        EndDrawing();
    }

    CloseWindow();
    return 0;
}