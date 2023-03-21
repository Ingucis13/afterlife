#include "character.h"
#include "projectiles.h"

#include <cmath>
#include <vector>

#include "raylib.h"


using namespace std;


#define PLAYER_MAX_SHOOTS  20

//static Bullet bullet[PLAYER_MAX_SHOOTS];

vector<Bullet> bullets;




int main()
{

    //init window, set fps, set textures
    InitWindow(800,800, "Afterlife");

    SetTargetFPS(60);
    //SetWindowState(FLAG_VSYNC_HINT);
    Image background = LoadImage("resources/hall.png");
    Image character = LoadImage("resources/character.png");
    Image enemy = LoadImage("resources/foe.png");
    ImageResize(&background,GetScreenWidth(),GetScreenHeight());
    Texture2D Background = LoadTextureFromImage(background);
    Texture2D Character = LoadTextureFromImage(character);
    Texture2D Enemy = LoadTextureFromImage(enemy);
    UnloadImage(background);
    UnloadImage(character);
    UnloadImage(enemy);


    // --move to Interface Movable


    // init characters
    class Character player(Character,70,50,Vector2{200,200},100,100,20,0);
    class Enemy monster(Enemy,140,140,Vector2{100,100});

    player.setFrameWidth(Character.width);
    player.setFrameHeight(Character.height);

    monster.setFrameWidth(Enemy.width);
    monster.setFrameHeight(Enemy.height);

    bool collision = false;

    int frameCounter=0;

    //main game loop
    while (!WindowShouldClose())
    {
        // start render
        BeginDrawing();

        ClearBackground(RAYWHITE);
        DrawTexture(Background, 0, 0, WHITE);
        frameCounter++;
        // mouse tracking

        // make one function that returns rotation
        // or add method to characters
        Vector2 mousePosition = GetMousePosition();
        float dx = mousePosition.x - player.getX();
        float dy = mousePosition.y - player.getY();
        float rotation = atan2f(dy, dx)+(PI/2);
        //enemy rotation parameters
        float dx2 = player.getX()-monster.getX();
        float dy2 = player.getY()-monster.getY();
        float rotation2 = atan2f(dy2, dx2)+(PI/2);




        //check if control key is down
        // --replace by switch
        if (IsKeyDown(KEY_W) && player.getY() >player.getWidth())
        {
            player.setY(-1*player.getSpeedY()*GetFrameTime()) ;
        }
        if (IsKeyDown(KEY_A) && player.getX() >player.getWidth())
        {
            player.setX(-1*player.getSpeedX()*GetFrameTime());
        }
        if (IsKeyDown(KEY_S) && player.getY() < (float(GetScreenHeight())-player.getWidth()))
        {
            player.setY(player.getSpeedY()*GetFrameTime());
        }
        if (IsKeyDown(KEY_D) && player.getX() < (float(GetScreenWidth())-player.getWidth()))
        {
            player.setX(player.getSpeedX()*GetFrameTime()) ;

        }



        //shooting
        if(IsMouseButtonPressed(MOUSE_BUTTON_LEFT))
        {

            if (bullets.size() < PLAYER_MAX_SHOOTS) {


                Bullet temp;
                temp.setSpeed(Vector2 {300,300});
                temp.setRadius(10);
                temp.setActive(false);
                temp.setPos((Vector2){player.getX(),player.getY()});
                temp.setColor(WHITE);
                temp.setTarget(mousePosition);
                bullets.push_back(temp);
            }

        }


        for(auto bullet = bullets.begin(); bullet != bullets.end(); bullet++)
        {
            //auto i = *bullet;

            if(bullet->getX() > bullet->getTarget().x)
            {
                bullet->setX(-1 * (bullet->getSpeedX() ) * GetFrameTime() );
            }
            if(bullet->getX() < bullet->getTarget().x)
            {
                bullet->setX((bullet->getSpeedX() ) * GetFrameTime() );
            }
            if(bullet->getY() > bullet->getTarget().y)
            {
                bullet->setY(-1 * (bullet->getSpeedY() ) * GetFrameTime() );
            }
            if(bullet->getY() < bullet->getTarget().y)
            {
                bullet->setY((bullet->getSpeedY() ) * GetFrameTime() );
            }

            // add logic for collision


            if(bullet->getX() >= 800 || bullet->getX() <= 0 || bullet->getY() >= 800 || bullet->getY() <= 0) // check also y
            {
                bullets.erase(bullet);
                continue;
            }


            DrawCircleV(bullet->getPos(), bullet->getRadius(), WHITE);

            /*if (i.isActive())
            {


                if(i.getX() > i.getTarget().x)
                {
                    i.setX(-1*(i.getSpeedX()+3)*GetFrameTime() );
                }
                if(i.getX() < i.getTarget().x)
                {
                    i.setX((i.getSpeedX()+3)*GetFrameTime() );
                }
                if(i.getY() >  i.getTarget().y)
                {
                    i.setY(-1*(i.getSpeedY()+3)*GetFrameTime() );
                }
                if(i.getY() < i.getTarget().y)
                {
                    i.setY((i.getSpeedY()+3)*GetFrameTime() );
                }

                //bullet[i].setX((bullet[i].getX()+3)*GetFrameTime());

                i.setLifeSpawn(i.getLifeSpawn()+1);

                if(i.getPos().x==i.getTarget().x && i.getPos().y==i.getTarget().y)
                {
                    i.setPos(Vector2{player.getX()+30,player.getY()+30});
                    i.setSpeed(Vector2{0,0});
                    i.setLifeSpawn(0);
                    i.isActive(false);
                }


                if(i.getX()>=800)
                {
                    i.setPos(Vector2{player.getX()+30,player.getY()+30});
                    i.setSpeed(Vector2{0,0});
                    i.setLifeSpawn(0);
                    i.isActive(false);
                }

                if(i.isActive())
                {
                    DrawCircleV(i.getPos(),i.getRadius(),WHITE);
                }

                //if(bullet[i].getLifeSpawn()>=80) {}

            }*/

        }






        //hp decrease and increase
        if (IsKeyPressed(KEY_UP) && player.getHp() < 100)
        {
            if(IsKeyPressed(KEY_UP) && player.getHp()>80)
            player.setHp(player.getHpMax());
            else
            player.setHp(player.getHp()+20);
        }
        if (IsKeyPressed(KEY_DOWN) && player.getHp() > 0)
        {
            player.setHp(player.getHp()-20) ;
        }

        //enemy movement
        if(player.getX() > monster.getX())
        {
          monster.setX(monster.getSpeedX()*GetFrameTime() );
        }
        if(player.getX() < monster.getX())
        {
          monster.setX(-1*monster.getSpeedX()*GetFrameTime() );
        }
        if(player.getY() > monster.getY())
        {
          monster.setY(monster.getSpeedY()*GetFrameTime() );
        }
        if(player.getY() < monster.getY())
        {
          monster.setY(-1*monster.getSpeedY()*GetFrameTime() );
        }

          collision = CheckCollisionRecs((Rectangle){player.getX(),player.getY(),(float)player.getWidth(),(float)player.getHeight()},
          (Rectangle){monster.getX(),monster.getY(),(float)monster.getWidth(),(float)monster.getHeight()});
          if (collision)
          {
            if(frameCounter>60)
            {
            player.setHp(player.getHp()-20);
            frameCounter=0;
            }
          }



        DrawLine(0,GetScreenHeight()/2,GetScreenWidth(),GetScreenHeight()/2,BLACK);
        DrawLine(GetScreenWidth()/2,0,GetScreenWidth()/2,GetScreenHeight(),BLACK);

        DrawTexturePro(player.getTexture(),(Rectangle){0,0,player.getFrameWidth(),player.getFrameHeight()},
                       (Rectangle){player.getX(),player.getY(),player.getWidth(),player.getHeight()},
                       (Vector2){(float)player.getWidth()/2, (float)player.getHeight()/2},
                       rotation*RAD2DEG,
                       WHITE);

        DrawTexturePro(monster.getTexture(),(Rectangle){0,0,monster.getFrameWidth(),monster.getFrameHeight()},
                       (Rectangle){ monster.getX(),monster.getY(),monster.getWidth(),monster.getHeight()},
                       (Vector2){(float)monster.getWidth()/2, (float)monster.getHeight()/2},
                       rotation2*RAD2DEG,
                       WHITE);

        //healthar
        auto HpPercent=  (float)(player.getHp())/(float)player.getHpMax();

        DrawRectangle(10, 10, 400, 30, BLACK);  
        DrawRectangle(14, 14, 392.0f * HpPercent, (22), RED);


        if(player.getHp()<=0)
        {
            DrawText("oh, you died(", 350, 400, 40, WHITE);
        }

        DrawText("AfterLife Test \nPress W A S D to move\nPress arrowup/arrowdown to increase/decrease HP value\nPress MouseLeft to shoot", 10, 50, 20, WHITE);
        DrawFPS(10, 170);

        EndDrawing(); // end render
    }

    // clear gpu
    UnloadTexture(Background);
    UnloadTexture(Character);
    UnloadTexture(Enemy);


    //end
    CloseWindow();

    return 0;
}
