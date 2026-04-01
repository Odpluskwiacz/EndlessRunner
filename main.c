#include "raylib.h"
// nie mogę sie zdecydowac camalCase PascalCase snake_case :(
// raylib ma PascalCase ja też powinieniem


  bool IsPressLimit(float time, float *CzasPrzytrzymania, double JumpPressStartTime ){  
    *CzasPrzytrzymania = (float)GetTime() - JumpPressStartTime;
    if (*CzasPrzytrzymania >= time) return true;
    return false;
  }


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
  while (!WindowShouldClose()){
  //========================== LOGIKA ====================
  if(IsKeyDown(KEY_SPACE) && !IsHoldingJump){
    JumpPressStartTime = GetTime();
    IsHoldingJump = true;
  }
  if((IsKeyReleased(KEY_SPACE)) && IsHoldingJump){
    IsHoldingJump = false;
    CzasPrzytrzymania = GetTime() - JumpPressStartTime;
    
    // TODO ładny Postęp od tąd zaczynaj 
    Player_one_Position.y -= 10 * CzasPrzytrzymania;
  } 



  //===================================== Drawing ================================
  BeginDrawing();

    ClearBackground(RAYWHITE);

    DrawCircleV(Player_one_Position, PlayerSize, MAROON);
    
    DrawRectangleV(Ziemia, Rozmiar  , DARKGRAY );

    DrawText(TextFormat("Y Pos: %.0f", Player_one_Position.y), 10, 10, 20, BLACK);
    DrawText(TextFormat("JumpPressStartTime: %.02f", JumpPressStartTime), 10, 40, 20, BLACK);
    DrawText(TextFormat("CzasPrzytrzymania: %.02f", CzasPrzytrzymania), 10, 60, 20, BLACK);
    // DrawText(TextFormat("Is Jumping: %s", IsJumping ? "YES" : "NO"), 10, 60, 20, BLACK);
 

  EndDrawing();
  }
  
  CloseWindow();
  return 0;
}
