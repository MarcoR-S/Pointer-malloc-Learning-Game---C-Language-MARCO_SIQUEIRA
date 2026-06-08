#include <stdio.h>
#include "raylib/include/raylib.h"

// Função Botao corrigida para usar cores nativas sem erro
void Botao(Rectangle area, const char* texto, Color cor){
    DrawRectangleRec(area, cor); // Constrói o fundo do botão
    DrawRectangleLinesEx(area, 4, BLACK); // Borda preta simples e funcional
    DrawText(texto, area.x + 25, area.y + 20, 28, WHITE); // Texto branco para contraste
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

    GameState estado = MENU; 
    Vector2 playerPos = {500,500};
    float vel = 10.0f;

    // Definição das áreas dos botões do menu
    Rectangle botaoJogar = { 350, 420, 300, 70 };
    Rectangle botaoInstrucoes = { 350, 520, 300, 70 };

    while (!WindowShouldClose())
    {
        BeginDrawing();
            // Fundo cinza escuro nativo - elegante e seguro contra erros
            ClearBackground(DARKGRAY);
            
            if(estado == MENU){
                // Painel central usando MAROON (um tom de vinho/vermelho escuro)
                DrawRectangle(200, 200, 600, 600, MAROON);
                DrawRectangleLinesEx((Rectangle){200, 200, 600, 600}, 4, WHITE);
                
                // Título alternando entre duas cores nativas seguras (GOLD e ORANGE)
                Color corTitulo = ((int)(GetTime() * 2) % 2 == 0) ? GOLD : ORANGE;
                DrawText("RETÂNGULO ADVENTURE", 240, 260, 45, corTitulo);
                
                // Renderizando os botões com cores padrões da Raylib
                Botao(botaoJogar, "1. JOGAR", LIME);      // Verde limão padrão
                Botao(botaoInstrucoes, "2. REGRAS", BLUE); // Azul padrão
                
                DrawText("Dica: Use o mouse para clicar ou o teclado!", 270, 720, 20, LIGHTGRAY);

                // Cliques e Teclado
                if((IsMouseButtonPressed(MOUSE_BUTTON_LEFT) && CheckCollisionPointRec(GetMousePosition(), botaoJogar)) || IsKeyPressed(KEY_ENTER)){
                    estado = JOGO;
                }
                else if((IsMouseButtonPressed(MOUSE_BUTTON_LEFT) && CheckCollisionPointRec(GetMousePosition(), botaoInstrucoes)) || IsKeyPressed(KEY_I)){
                    estado = INSTRUCT;
                }
            }
            else if(estado == PAUSA){
                DrawRectangle(200, 200, 600, 600, MAROON);
                DrawRectangleLinesEx((Rectangle){200, 200, 600, 600}, 4, ORANGE);
                
                DrawText("PAUSA", 435, 260, 50, ORANGE);
                DrawText("PRESSIONE ENTER PARA VOLTAR", 310, 500, 24, WHITE);
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

                // O jogador agora é um quadrado SKYBLUE (Azul Claro) com borda branca
                DrawRectangleV(playerPos, (Vector2){ 40, 40 }, SKYBLUE);
                DrawRectangleLinesEx((Rectangle){playerPos.x, playerPos.y, 40, 40}, 2, WHITE);
                
                if (IsKeyDown(KEY_RIGHT)) playerPos.x += vel;
                if (IsKeyDown(KEY_LEFT))  playerPos.x -= vel;
                if (IsKeyDown(KEY_UP))    playerPos.y -= vel;
                if (IsKeyDown(KEY_DOWN))  playerPos.y += vel;
            }
            else if(estado == INSTRUCT){
                DrawRectangle(200, 200, 600, 600, MAROON);
                DrawRectangleLinesEx((Rectangle){200, 200, 600, 600}, 4, SKYBLUE);
                
                DrawText("INSTRUCOES", 360, 260, 50, SKYBLUE);
                DrawText("Movimente o personagem com as teclas: SETAS", 245, 480, 22, WHITE);
                DrawText("Pressione M para voltar ao MENU", 320, 540, 22, LIGHTGRAY);
                
                if(IsKeyPressed(KEY_M)){
                    estado = MENU;
                }
                if(IsKeyPressed(KEY_ENTER)){
                    estado = JOGO;
                }
            }
            else if(estado == GAME_OVER){
                DrawRectangle(200, 200, 600, 600, MAROON);
                DrawRectangleLinesEx((Rectangle){200, 200, 600, 600}, 4, RED);
                
                DrawText("GAME OVER", 370, 260, 50, RED);
                DrawText("CLIQUE G PARA REVIVER", 360, 500, 24, WHITE);
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