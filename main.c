#include "raylib.h"

#define screenWidth 800
#define screenHeight 450
#define PlayerSize 50
#define Gravity 4000

// TODO GAME OVER

Vector2 BoxSize = { 50, 50 };
Vector2 Player_one_Position = { (float)screenWidth / 5, 300};
Vector2 BoxPosition = {  500, 300};
Vector2 Podloga = { 0,  (float)screenHeight / 1.5 + PlayerSize };
Vector2 RozmiarPodloga = { screenWidth, 100};
bool OnGround = true;
float Velocity;
bool GamePause = false;




void GameOver(double Score){
  // STOP PLAYER
  // STOP BOX 
  // STOP SCORE 
 DrawText(TextFormat("Score: %.0f", Score), screenWidth/2, screenHeight/2, 50, BLACK);
 GamePause = true;
};

void StartGame(){
  // RESET PLAYER
  // RESET BOX
  // RESET SCORE
}


int main(void)
{  
  InitWindow(screenWidth, screenHeight, "Endles Runner mutliplayer");
  SetTargetFPS(60);

  // MAIN GAME LOOP
  while (!WindowShouldClose()){
  //========================== LOGIKA ====================
  //========================== LOGIKA - SKOK ============
  if (IsKeyDown(KEY_SPACE) && OnGround ){
    Velocity = -1400;
    OnGround = false;
  }
  //========================== LOGIKA - Opadanie ========
  if(!OnGround) {
    Velocity += Gravity * GetFrameTime(); // Grawitacja ciągnąca w dół
    Player_one_Position.y += Velocity * GetFrameTime(); //Ruch na podstawie prędkości
  }
  if(Player_one_Position.y >= 300.0f){
    Player_one_Position.y = 300;
    Velocity = 0;
    OnGround = true;
  }
  //========================= LOGIKA - SCORE COUNT
  double Score = GetTime();
  //======================== LOGIKA - ENEMY BOX
  BoxPosition.x -= 2 + Score/2;
  if(BoxPosition.x < 0 - BoxSize.x){
    BoxPosition.x = screenWidth;
  }


  //========================= LOGIKA - COLISION BOX
  bool IsCollision;
  if(CheckCollisionPointCircle(BoxPosition, Player_one_Position, PlayerSize )){
    IsCollision = true;
    GameOver(Score);
  } else {
    IsCollision = false;
  }



  //===================================== Drawing ================================
  BeginDrawing();

    ClearBackground(RAYWHITE);

    DrawCircleV(Player_one_Position, PlayerSize, MAROON);
    DrawRectangleV( BoxPosition, BoxSize , BLACK);
    
    DrawRectangleV(Podloga, RozmiarPodloga, DARKGRAY );

    DrawText(TextFormat("Y Pos: %.0f", Player_one_Position.y), 10, 10, 20, BLACK);
    DrawText(TextFormat("Velocity: %.02f", Velocity), 10, 40, 20, BLACK);
    DrawText(TextFormat("BoxPosition: %.1f", BoxPosition.x), 10, 60, 20, BLACK);
    DrawText(TextFormat("Is Collision: %s", IsCollision ? "YES" : "NO"), 10, 80, 20, BLACK);
    DrawText(TextFormat("Score: %.0f", Score), screenWidth - 100, 10, 20, BLACK);
 

  EndDrawing();
  }
  CloseWindow();
  return 0;
}
