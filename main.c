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
  Vector2 Player_one_Position = { (float)screenWidth / 5, 300};
  const int screenHeight = 450;
  const int PlayerSize = 50;

  InitWindow(screenWidth, screenHeight, "Endles Runner mutliplayer");
  SetTargetFPS(60);

  Vector2 Ziemia = { 0,  (float)screenHeight / 1.5 + PlayerSize };
  Vector2 Rozmiar = { screenWidth, 100};

  bool OnGround = true;
  float Gravity = 4000;
  float Velocity;

  // MAIN GAME LOOP
  while (!WindowShouldClose()){
  //========================== LOGIKA ====================


  //========================== LOGIKA - SKOK ============
  if (IsKeyPressed(KEY_SPACE) && OnGround ){
    Velocity = -1400;
    OnGround = false;
  }
  //Opadanie
  if(!OnGround) {
    Velocity += Gravity * GetFrameTime(); // Grawitacja ciągnąca w dół
    Player_one_Position.y += Velocity * GetFrameTime(); //Ruch na podstawie prędkości
  }
  if(Player_one_Position.y >= 300.0f){
    Player_one_Position.y = 300;
    Velocity = 0;
    OnGround = true;
  }


  //===================================== Drawing ================================
  BeginDrawing();

    ClearBackground(RAYWHITE);

    DrawCircleV(Player_one_Position, PlayerSize, MAROON);
    
    DrawRectangleV(Ziemia, Rozmiar  , DARKGRAY );

    DrawText(TextFormat("Y Pos: %.0f", Player_one_Position.y), 10, 10, 20, BLACK);
    DrawText(TextFormat("Velocity: %.02f", Velocity), 10, 40, 20, BLACK);
    //DrawText(TextFormat("CzasPrzytrzymania: %.02f", CzasPrzytrzymania), 10, 60, 20, BLACK);
    // DrawText(TextFormat("Is Jumping: %s", IsJumping ? "YES" : "NO"), 10, 60, 20, BLACK);
 

  EndDrawing();
  }
  
  CloseWindow();
  return 0;
}
