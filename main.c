#include "raylib.h"

// TODO BOX ENEMY further development
// TODO SCORE = GAME TIME 
// TODO BOX ENEMY SPEED == SCORE HIGHT 


   
int main(void)
{
  const int screenWidth = 800;
  const int screenHeight = 450;
  const int PlayerSize = 50; 

  Vector2 BoxSize = { 50, 50 };
  
  

  Vector2 Player_one_Position = { (float)screenWidth / 5, 300};
  Vector2 BoxPosition = {  500, 300};

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
  //======================== LOGIKA - ENEMY BOX
  BoxPosition.x -= 2;

  if(BoxPosition.x < 0 - BoxSize.x){
    BoxPosition.x = screenWidth;
  }


  //===================================== Drawing ================================
  BeginDrawing();

    ClearBackground(RAYWHITE);

    DrawCircleV(Player_one_Position, PlayerSize, MAROON);
    DrawRectangleV( BoxPosition, BoxSize , BLACK);
    
    DrawRectangleV(Ziemia, Rozmiar, DARKGRAY );

    DrawText(TextFormat("Y Pos: %.0f", Player_one_Position.y), 10, 10, 20, BLACK);
    DrawText(TextFormat("Velocity: %.02f", Velocity), 10, 40, 20, BLACK);
    DrawText(TextFormat("BoxPosition: %.1f", BoxPosition.x), 10, 60, 20, BLACK);
    // DrawText(TextFormat("Is Jumping: %s", IsJumping ? "YES" : "NO"), 10, 60, 20, BLACK);
 

  EndDrawing();
  }
  
  CloseWindow();
  return 0;
}
