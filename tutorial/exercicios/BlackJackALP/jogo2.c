#include <stdio.h>
#include "raylib/include/raylib.h"


void Botao(Rectangle area, const char* texto, Color cor){
    DrawRectangleRec(area,cor); //constrói as dimensões e cores do botao
    DrawRectangleLinesEx(area, 5, BLACK);
    DrawText(texto, area.x+15, area.y+15, 40, BLACK); //Insere o texto no botao
};

typedef enum GameState{
    MENU,
    PAUSA,
    INSTRUCT,
    JOGO,
    GAME_OVER
} GameState;




int main(void)
{
    InitWindow(1000, 1000, "Apenas um Retangulo");

    SetTargetFPS(60); 

    GameState estado = INSTRUCT;
    Vector2 playerPos = {500,500};
    float vel = 10.0f;
    float grav = -5.0f;

    while (!WindowShouldClose())
    {

        BeginDrawing();
            ClearBackground(RAYWHITE);
            if(estado == MENU){
                // Centralizado: Retângulo de 600x600 começando em 200,200
                DrawRectangle(200, 200, 600, 600, GRAY);
                DrawText("MENU", 440, 260, 50, BLACK);
                DrawText("PRESSIONE ENTER PARA JOGAR", 320, 480, 24, BLACK);
                DrawText("PRESSIONE I PARA INSTRUCT", 335, 540, 24, BLACK);
                if(IsKeyPressed(KEY_ENTER)){
                    estado = JOGO;
                }
                else if(IsKeyPressed(KEY_I)){
                    estado = INSTRUCT;
                }
            }
            else if(estado == PAUSA){
                DrawRectangle(200, 200, 600, 600, GRAY);
                DrawText("PAUSA", 435, 260, 50, BLACK);
                DrawText("CLIQUE ENTER PARA JOGAR", 340, 500, 24, BLACK);
                if(IsKeyPressed(KEY_ENTER)){
                    estado = JOGO;
                }

            }
            else if(estado == JOGO){
                if(IsKeyPressed(KEY_SPACE)){
                    estado = PAUSA;
                }
                if(IsKeyPressed(KEY_M)){
                    estado = MENU;
                }

                DrawRectangleV(playerPos, (Vector2){ 40, 40 }, BLUE);
                
                if (IsKeyDown(KEY_RIGHT)) playerPos.x += vel;
                if (IsKeyDown(KEY_LEFT))  playerPos.x -= vel;
                if (IsKeyDown(KEY_UP))    playerPos.y -= vel;
                if (IsKeyDown(KEY_DOWN))  playerPos.y += vel;
            }
            else if(estado == INSTRUCT){
                DrawRectangle(200, 200, 600, 600, GRAY);
                DrawText("INSTRUCOES", 360, 260, 50, BLACK);
                DrawText("Movimente o personagem com as teclas: SETAS", 245, 480, 22, BLACK);
                DrawText("Pressione M para voltar ao MENU", 320, 540, 22, DARKGRAY);
                if(IsKeyPressed(KEY_M)){
                    estado = MENU;
                }
                if(IsKeyPressed(KEY_ENTER)){
                    estado = JOGO;
                }
            }
            else if(estado == GAME_OVER){
                DrawRectangle(200, 200, 600, 600, GRAY);
                DrawText("GAME OVER", 370, 260, 50, BLACK);
                DrawText("CLIQUE G PARA REVIVER", 360, 500, 24, BLACK);
                if(IsKeyPressed(KEY_G)){
                    playerPos = (Vector2){500,500};
                    estado = JOGO;
                }
            }

        EndDrawing();
    }


    CloseWindow();

    return 0;
}