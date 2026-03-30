#include "raylib.h"

// nie mogę sie zdecydowac camalCase PascalCase snake_case :(
// raylib ma PascalCase ja też powinieniem
#define MIN(a, b) ((a) < (b) ? (a) : (b))

int main(void)
{
  const int screenWidth = 800;
  const int screenHeight = 450;
  const int PlayerSize = 50;

  InitWindow(screenWidth, screenHeight, "Endles Runner mutliplayer");
  SetTargetFPS(60);

  Vector2 Ziemia = { 0,  (float)screenHeight / 1.5 + PlayerSize };
  Vector2 Rozmiar = { screenWidth, 100};
  Vector2 Player_one_Position = { (float)screenWidth / 5, (float)screenHeight / 1.5};

  double JumpPressStartTime;
  float CzasPrzytrzymania;
  float Gravity = 1000;
  float VerticalVelocity;
  float JumpForce;
  bool IsJumping = false;
  bool IsHoldingJump = false;


  // MAIN GAME LOOP
  while (!WindowShouldClose())
  {
  //========================== LOGIKA ====================
  if (IsKeyDown(KEY_SPACE) && !IsJumping ) {
    JumpPressStartTime = GetTime();
    IsHoldingJump = true;
  }
  if (IsKeyReleased(KEY_SPACE) && IsHoldingJump && !IsJumping){
    CzasPrzytrzymania = (float)GetTime() - JumpPressStartTime;
    CzasPrzytrzymania = MIN(CzasPrzytrzymania , 0.3f);
    JumpForce = 600 + (2000 - 600) * (CzasPrzytrzymania / 0.3f);
    VerticalVelocity = -JumpForce;
    IsJumping = true;
    IsHoldingJump = false;
  }
  if (IsJumping){
    VerticalVelocity += Gravity * GetFrameTime();
    Player_one_Position.y += VerticalVelocity * GetFrameTime();
    if (Player_one_Position.y >= 300){
      Player_one_Position.y = 300;
      VerticalVelocity = 0;
      IsJumping = false;
    }
  }


  //===================================== Drawing ================================
  BeginDrawing();

    ClearBackground(RAYWHITE);

    DrawCircleV(Player_one_Position, PlayerSize, MAROON);
    
    DrawRectangleV(Ziemia, Rozmiar  , DARKGRAY );

    DrawText(TextFormat("Y Pos: %.0f", Player_one_Position.y), 10, 10, 20, BLACK);
    DrawText(TextFormat("Velocity: %.0f", VerticalVelocity), 10, 35, 20, BLACK);
    DrawText(TextFormat("Is Jumping: %s", IsJumping ? "YES" : "NO"), 10, 60, 20, BLACK);
    DrawText(TextFormat("Hold Time: %.2f", CzasPrzytrzymania), 10, 85, 20, BLACK);
    DrawText("Press and hold SPACE for higher jump!", 10, screenHeight - 30, 20, DARKGRAY);
 

  EndDrawing();
  }
  
  CloseWindow();
  return 0;
}
