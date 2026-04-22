#include "raylib.h"

// TODO Zastanów się czy po Polsku czy angielsku, jeśli Angielsku to jak nadrobisz degradację Polskiego

#define screenWidth 800
#define screenHeight 450
#define PlayerSize 50
#define Gravity 4000

// TODO BETER CONDITIONS FOR if GamePause 

Vector2 BoxSize = { 50, 50 };
Vector2 Player_one_Position = { (float)screenWidth / 5, 300};
Vector2 BoxPosition = {  500, 300};
Vector2 Podloga = { 0,  (float)screenHeight / 1.5 + PlayerSize };
Vector2 RozmiarPodloga = { screenWidth, 100};
bool OnGround = true;
float Velocity;
bool GamePause = false;
double Score;
double GameStartOffset = 0;



void GameOver(double Score){
  // STOP PLAYER JUMP
  // STOP BOX 
  // STOP SCORE 
 DrawText("GAME OVER", screenWidth/2, screenHeight/2 - 100, 50, BLACK);
 DrawText(TextFormat("Score: %.0f", Score), screenWidth/2, screenHeight/2, 50, BLACK);
 DrawText("Press 'R' to restart", screenWidth/2, screenHeight/2 - 50, 25, BLACK);
 GamePause = true;
};

void RestartGame(){
  // RESET PLAYER
  Player_one_Position.x = (float)screenWidth / 5;
  // RESET BOX
  BoxPosition.x = 500;
  BoxPosition.y = 300;
  // RESET SCORE
  GameStartOffset = GetTime();

  GamePause = false;
}


int main(void)
{  
  InitWindow(screenWidth, screenHeight, "Endles Runner mutliplayer");
  SetTargetFPS(60);


  // MAIN GAME LOOP
  while (!WindowShouldClose()){
  //========================== LOGIKA ====================
  //========================== LOGIKA - SKOK ============
  if (IsKeyDown(KEY_SPACE) && OnGround  && !GamePause){
    Velocity = -1400;
    OnGround = false;
  }
  //========================== LOGIKA - Opadanie ========
  if(!OnGround && !GamePause) {
    Velocity += Gravity * GetFrameTime(); // Grawitacja ciągnąca w dół
    Player_one_Position.y += Velocity * GetFrameTime(); //Ruch na podstawie prędkości
  }
  if(Player_one_Position.y >= 300.0f){
    Player_one_Position.y = 300;
    Velocity = 0;
    OnGround = true;
  }

  //========================= LOGIKA - SCORE COUNT
  if(!GamePause) Score = GetTime() - GameStartOffset;

  //======================== LOGIKA - ENEMY BOX
  if(!GamePause) BoxPosition.x -= 5 + Score/3;
  
  float BoxSpawnTime;
  if(BoxPosition.x < 0 - BoxSize.x){
    BoxSpawnTime = Score + ((float)GetRandomValue(1, 25) / 10 ); // od 0.1 0.2 0.3 ... 2,48 2,49 2,5 sek
  }
  if(BoxSpawnTime >= Score ){
    BoxPosition.x = screenWidth;
    BoxPosition.y = GetRandomValue(300 , 200); 
  }


  //========================= LOGIKA - COLISION BOX
  bool IsCollision;
  if(CheckCollisionPointCircle(BoxPosition, Player_one_Position, PlayerSize )){
    IsCollision = true;
    GameOver(Score);
  } else {
    IsCollision = false;
  }

  //======================== LOGIKA - Restart Game
  if(IsKeyPressed(KEY_R)) RestartGame();

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
    DrawText(TextFormat("Score: %.3f", Score), screenWidth - 140, 10, 20, BLACK);
 

  EndDrawing();
  }
  CloseWindow();
  return 0;
}
