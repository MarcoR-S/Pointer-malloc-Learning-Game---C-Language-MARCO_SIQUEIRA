//Importando as bibliotecas
#include <stdio.h>
#include "raylib/include/raylib.h"

//Automação da criação de botões com texto
void Botao(Rectangle area, const char* texto, Color cor){
    DrawRectangleRec(area,cor); //constrói as dimensões e cores do botao
    DrawRectangleLinesEx(area, 5, BLACK);
    DrawText(texto, area.x+15, area.y+15, 40, BLACK); //Insere o texto no botao
};

//Receber a carta
int entregarCarta(int n){ //n = vezes que vai receber a carta
    int soma = 0; //soma = valor agregado à contagem
    for(int i = 0; i<n; i++ ){ //inicio; condição; incremento
        soma += GetRandomValue(1,11); //Sorteia um valor int entre 1 e 11
    }
    return soma; //retorna o valor recebido
}

//Verificar se a contagem == 21
void verificar21(int *contagemP, int *contagemD, 
                int *gameState, char *resultado){
    if(*contagemP == 21){ //Se a contagem do jogador for igual a 21
        *resultado = 'p'; //De o resultado de vitoria do jogador ('p')
        *gameState = 3; //Pule para o último gameState
    }
    if(*contagemD == 21){ //Se a contagem do dealer for igual a 21
        *resultado = 'd'; //De o resultado de vitoria do dealer ('d')
        *gameState = 3;//Pule para o último gameState
    }
}
//Verificar se a contagem passou de 21
void verificarEstouro(int *contagemP, int *contagemD, 
                int *gameState, char *resultado){
    if(*contagemP > 21){ //Se a contagem do jogador for maior que 21
        *resultado = 'd'; //De o resultado de vitoria do dealer ('d')
        *gameState = 3; //Pule para o último gameState
    }
    if(*contagemD > 21){ //Se a contagem do dealer for maior que 21
        *resultado = 'p'; //De o resultado de vitoria do jogador ('p')
        *gameState = 3; //Pule para o último gameState
    }
}

//Reiniciar a rodada
void reiniciar(int *contagemP, int *contagemD, 
                int *gameState, char *resultado){
    *gameState = 0;  //Zera todos os valores da rodada
    *contagemP = 0;
    *contagemD = 0;
    *resultado = ' ';                    

}

//Verificar quem teve a maior soma
int verificarMaior(int *contagemP, int *contagemD){
    int maior = 'd'; 
    if(*contagemP > *contagemD){
        maior ='p';
    }
    return maior;
}

typedef enum EstadoJogo{
    MENU,
    INSTRUCT,
    JOGO,
    GAME_OVER,
} EstadoJogo;


int main(void)
{

    //JANELA
    const int width = 800; 
    const int height = 600;

    Texture2D mesa;
    Music ambiente;
    Sound vitoria;
    Sound loss; 

    InitAudioDevice();

    EstadoJogo estadoAtual = MENU;

    

    //1 Estado
    int gameState = 0;
    //2 Contagens
    int contagemP = 0;
    int contagemD = 0;
    //3 Placar
    int vitorias = 0;
    int derrotas = 0;
    char resultado;
    
    //BOTOES    
    Rectangle hitB = {20,500,200,70}; //HIT
    Rectangle standB = {250,500,200,70}; //STAND
    Rectangle restartB = {250, height/2, 300,100}; //RESTART

    //SRC
    InitWindow(width, height, "BlackJack ALP - IDP");

    vitoria = LoadSound("Victory!.wav");
    loss = LoadSound("loss.ogg");
    ambiente = LoadMusicStream("ambiente.mp3");
     mesa = LoadTexture("mesa.png");


    PlayMusicStream(ambiente);
    SetMusicVolume(ambiente, 0.2f);


    SetTargetFPS(30);

    // Loop principal do jogo
    while (!WindowShouldClose())
    {
        UpdateMusicStream(ambiente);
        
        // CONTROLE DE ESTADOS
        if(estadoAtual == MENU){
            if(IsKeyPressed(KEY_SPACE)){
                estadoAtual = JOGO;
                gameState = 0; //Reinicia o jogo
            }
            if(IsKeyPressed(KEY_P)){
                estadoAtual = INSTRUCT;
            }
        }
        else if(estadoAtual == INSTRUCT){
            if(IsKeyPressed(KEY_SPACE)){
                estadoAtual = JOGO;
                gameState = 0; //Reinicia o jogo
            }
        }
        
        BeginDrawing();
        ClearBackground(DARKGREEN);
        DrawTexture(mesa, 70, 0, WHITE);
        
        Vector2 mousePos = GetMousePosition(); //Pegar a posição do mouse
        
        // MENU
        if(estadoAtual == MENU){
            DrawRectangle(0,0,600,600, LIME);
            DrawText("BLACKJACK", width/2 - 150, 100, 60, GOLD);
            DrawText("Pressione ESPACO para jogar", width/2 - 200, height/2 - 50, 25, WHITE);
            DrawText("Pressione P para instrucoes", width/2 - 200, height/2 + 20, 25, WHITE);
        }
        // INSTRUÇÕES
        else if(estadoAtual == INSTRUCT){
            DrawText("COMO JOGAR BLACKJACK", width/2 - 250, 50, 40, GOLD);
            
            DrawText("OBJETIVO: Chegar o mais perto possivel de 21 pontos", 50, 120, 18, WHITE);
            DrawText("sem ultrapassar (sem 'BUST')", 50, 145, 18, WHITE);
            
            DrawText("REGRAS:", 50, 200, 20, YELLOW);
            DrawText("- Voce recebe 2 cartas inicialmente", 70, 230, 16, WHITE);
            DrawText("- O dealer recebe 1 carta visivel", 70, 255, 16, WHITE);
            DrawText("- Escolha HIT para receber mais uma carta", 70, 280, 16, WHITE);
            DrawText("- Escolha STAND para parar de receber cartas", 70, 305, 16, WHITE);
            DrawText("- O dealer recebe cartas ate ter 17 ou mais", 70, 330, 16, WHITE);
            DrawText("- Quem ficar mais proximo de 21 vence!", 70, 355, 16, WHITE);
            
            DrawText("Pressione ESPACO para voltar ao jogo", width/2 - 250, height - 80, 20, LIME);
        }
        // JOGO
        else if(estadoAtual == JOGO){
            switch(gameState){ //Fluxo entre os estados do jogo
                case 0: //Jogadores recebem suas cartas
                    contagemP = entregarCarta(2);
                    contagemD = entregarCarta(1);
                    verificar21(&contagemP, &contagemD, &gameState, &resultado);
                    if(gameState==0){gameState =1;} 
                    break;
                case 1: //Jogador escolhe HIT OU STAND
                    Botao(hitB, "HIT", GREEN);
                    Botao(standB, "STAND", GREEN);

                    //Lógica do click em HIT
                    if(CheckCollisionPointRec(mousePos, hitB)&& IsMouseButtonPressed(MOUSE_LEFT_BUTTON)){
                        contagemP += entregarCarta(1);
                        verificar21(&contagemP, &contagemD, &gameState, &resultado);
                        verificarEstouro(&contagemP, &contagemD, &gameState, &resultado);
                    }
                    //Lógica do click em STAND
                    if(CheckCollisionPointRec(mousePos, standB)&& IsMouseButtonPressed(MOUSE_LEFT_BUTTON)){
                        gameState = 2;
                    }
                    break;
                case 2: //Dealer recebe suas cartas até que sua contagem seja maior que 17
                    if(contagemD < 17){
                        contagemD += entregarCarta(1);
                    }
                    
                    else{ 
                        verificar21(&contagemP, &contagemD, &gameState, &resultado);
                        verificarEstouro(&contagemP, &contagemD, &gameState, &resultado);
                        //Validar vencedor 
                        if(gameState != 3){
                            resultado = verificarMaior(&contagemP, &contagemD);
                        }
                        
                        gameState = 3;
                
                    }
                    break;
                case 3:
                    //Exibir o resultado
                    if (resultado == 'p') {
                        vitorias +=1;
                        DrawText("VOCE VENCEU!", width/2 - 150, height/2 - 100, 40, GOLD);
                        gameState = 4;
                        StopMusicStream(ambiente);
                        PlaySound(vitoria);
                    } 
                    else{
                        derrotas +=1;
                        DrawText("CASA VENCEU!", width/2 - 150, height/2 - 100, 40, RED);
                        gameState = 4;
                        StopMusicStream(ambiente);
                        PlaySound(loss);
                    }
                    break;
                case 4:
                    if (resultado == 'p') {
                        DrawText("VOCE VENCEU!", width/2 - 150, height/2 - 100, 40, GOLD);
                        
                    } 
                    else{
                        DrawText("CASA VENCEU!", width/2 - 150, height/2 - 100, 40, RED);
                    }
                    //Recomeçar o jogo
                    Botao(restartB, "RESTART", RED);
                    if(CheckCollisionPointRec(mousePos, restartB)&&IsMouseButtonPressed(MOUSE_BUTTON_LEFT)){
                        StopSound(vitoria);   
                        StopSound(loss);      
                        PlayMusicStream(ambiente);
                        reiniciar(&contagemP, &contagemD, &gameState, &resultado);
                    }
                    break;
            }

            DrawText(TextFormat("VOCÊ: %i",contagemP), 480, 500, 20, BLACK);
            DrawText(TextFormat("CASA: %i",contagemD), 480, 540, 20, BLACK);
            DrawText(TextFormat("Vitórias: %i", vitorias), 600, 500, 20, BLACK);
            DrawText(TextFormat("Derrotas: %i",derrotas), 600, 540, 20, BLACK);
        }

        EndDrawing();
    }

    // 3. Fecha tudo
    UnloadTexture(mesa);
    UnloadMusicStream(ambiente);
    UnloadSound(vitoria);
    UnloadSound(loss);
    CloseAudioDevice();
    CloseWindow();
    return 0;
}


//gcc main.c -o main.exe -Iraylib/include -Lraylib/lib -lraylib -lopengl32 -lgdi32 -lwinmm
//./main.exe