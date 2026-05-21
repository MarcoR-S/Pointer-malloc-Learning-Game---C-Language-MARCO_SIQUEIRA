# 13 - Complete Game

# Jogo dos Ponteiros, malloc e realloc em Raylib (C)

# Objetivo da Aula

Nesta aula iremos juntar praticamente TODOS os conceitos aprendidos anteriormente:

- janela
- renderização
- FPS
- input
- colisão
- structs
- arrays
- ponteiros
- heap
- malloc
- realloc
- free
- gameplay loop
- entidades dinâmicas

Agora deixamos de criar apenas “exemplos isolados”.

Estamos criando:

```text
um jogo completo usando memória dinâmica
```

---

# O que esse jogo representa

Esse projeto simula:

```text
um sistema real de entidades dinâmicas
```

Ou seja:

- objetos nascem
- memória cresce
- memória é realocada
- entidades aparecem dinamicamente

Isso é MUITO parecido com:
- engines reais
- sistemas ECS
- jogos profissionais

---

# Código Completo

```c
// Importa a biblioteca gráfica Raylib
#include "raylib.h"

// Importa funções de memória dinâmica
#include <stdlib.h>

// Importa funções de texto como printf
#include <stdio.h>

// =========================================
// ESTRUTURA DO BLOCO DE MEMÓRIA
// =========================================

// Cria uma estrutura chamada BlocoMemoria
typedef struct BlocoMemoria {

    // Guarda posição X e Y
    Vector2 posicao;

    // Guarda tamanho do bloco
    float tamanho;

    // Define se bloco está ativo
    bool ativo;

} BlocoMemoria;

// =========================================
// FUNÇÃO PRINCIPAL
// =========================================

int main(void)
{
    // Cria janela do jogo
    InitWindow(800, 450, "Jogo dos Ponteiros e malloc");

    // Define FPS
    SetTargetFPS(60);

    // =========================================
    // JOGADOR
    // =========================================

    // Posição inicial do jogador
    Vector2 jogador = { 400, 225 };

    // Velocidade do jogador
    float velocidade = 4.0f;

    // =========================================
    // CONTROLE DE MEMÓRIA
    // =========================================

    // Capacidade máxima inicial
    int capacidade = 5;

    // Quantidade atual de blocos
    int quantidade = 5;

    // Pontuação do jogador
    int pontos = 0;

    // =========================================
    // MALLOC
    // =========================================

    // malloc:
    // cria vetor dinâmico na heap
    BlocoMemoria *blocos =
        malloc(capacidade * sizeof(BlocoMemoria));

    // Verifica erro de memória
    if (blocos == NULL)
    {
        // Mostra erro
        printf("Erro ao alocar memoria!\n");

        // Encerra programa
        return 1;
    }

    // =========================================
    // INICIALIZAÇÃO DOS BLOCOS
    // =========================================

    // Percorre todos os blocos
    for (int i = 0; i < quantidade; i++)
    {
        // Define posição X aleatória
        blocos[i].posicao.x =
            GetRandomValue(50, 750);

        // Define posição Y aleatória
        blocos[i].posicao.y =
            GetRandomValue(50, 400);

        // Define tamanho do bloco
        blocos[i].tamanho = 25;

        // Ativa bloco
        blocos[i].ativo = true;
    }

    // =========================================
    // GAME LOOP
    // =========================================

    while (!WindowShouldClose())
    {
        // =========================================
        // INPUT
        // =========================================

        // Move jogador para direita
        if (IsKeyDown(KEY_RIGHT))
            jogador.x += velocidade;

        // Move jogador para esquerda
        if (IsKeyDown(KEY_LEFT))
            jogador.x -= velocidade;

        // Move jogador para cima
        if (IsKeyDown(KEY_UP))
            jogador.y -= velocidade;

        // Move jogador para baixo
        if (IsKeyDown(KEY_DOWN))
            jogador.y += velocidade;

        // =========================================
        // HITBOX DO JOGADOR
        // =========================================

        Rectangle rectJogador =
        {
            jogador.x,
            jogador.y,
            30,
            30
        };

        // =========================================
        // LOOP DE COLISÃO
        // =========================================

        for (int i = 0; i < quantidade; i++)
        {
            // Verifica se bloco está ativo
            if (blocos[i].ativo)
            {
                // Cria hitbox do bloco
                Rectangle rectBloco =
                {
                    blocos[i].posicao.x,
                    blocos[i].posicao.y,
                    blocos[i].tamanho,
                    blocos[i].tamanho
                };

                // Detecta colisão
                if (CheckCollisionRecs(rectJogador,
                                       rectBloco))
                {
                    // Desativa bloco
                    blocos[i].ativo = false;

                    // Aumenta pontuação
                    pontos++;
                }
            }
        }

        // =========================================
        // REALLOCAÇÃO DINÂMICA
        // =========================================

        // Quando todos os blocos forem coletados
        if (pontos == quantidade)
        {
            // Aumenta capacidade total
            capacidade += 5;

            // Aumenta quantidade atual
            quantidade += 5;

            // realloc:
            // aumenta vetor dinamicamente
            BlocoMemoria *novoEndereco =
                realloc(blocos,
                        capacidade *
                        sizeof(BlocoMemoria));

            // Verifica erro
            if (novoEndereco == NULL)
            {
                printf("Erro ao realocar memoria!\n");

                // Libera memória antiga
                free(blocos);

                // Fecha janela
                CloseWindow();

                return 1;
            }

            // Atualiza ponteiro
            blocos = novoEndereco;

            // Inicializa novos blocos
            for (int i = pontos;
                 i < quantidade;
                 i++)
            {
                // Nova posição X
                blocos[i].posicao.x =
                    GetRandomValue(50, 750);

                // Nova posição Y
                blocos[i].posicao.y =
                    GetRandomValue(50, 400);

                // Tamanho do bloco
                blocos[i].tamanho = 25;

                // Ativa bloco
                blocos[i].ativo = true;
            }
        }

        // =========================================
        // RENDERIZAÇÃO
        // =========================================

        // Inicia renderização
        BeginDrawing();

        // Limpa tela
        ClearBackground(RAYWHITE);

        // Título do jogo
        DrawText("Jogo dos Ponteiros e malloc",
                 20,
                 20,
                 24,
                 DARKBLUE);

        // Instruções
        DrawText(
            "Use as setas para coletar blocos de memoria",
            20,
            55,
            18,
            DARKGRAY
        );

        // Mostra pontuação
        DrawText(
            TextFormat("Pontos: %d", pontos),
            20,
            90,
            20,
            BLACK
        );

        // Mostra quantidade de blocos
        DrawText(
            TextFormat("Blocos alocados: %d",
                       quantidade),
            20,
            115,
            20,
            BLACK
        );

        // Mostra capacidade total
        DrawText(
            TextFormat("Capacidade da memoria: %d",
                       capacidade),
            20,
            140,
            20,
            BLACK
        );

        // Desenha jogador
        DrawRectangleV(
            jogador,
            (Vector2){30, 30},
            BLUE
        );

        // =========================================
        // DESENHA BLOCOS
        // =========================================

        for (int i = 0; i < quantidade; i++)
        {
            // Verifica se bloco está ativo
            if (blocos[i].ativo)
            {
                // Desenha bloco verde
                DrawRectangleV(
                    blocos[i].posicao,
                    (Vector2)
                    {
                        blocos[i].tamanho,
                        blocos[i].tamanho
                    },
                    GREEN
                );
            }
        }

        // Explicação visual
        DrawText(
            "malloc cria os blocos | realloc aumenta | free libera no final",
            20,
            410,
            18,
            MAROON
        );

        // Finaliza renderização
        EndDrawing();
    }

    // =========================================
    // FREE
    // =========================================

    // free:
    // libera memória usada pelos blocos
    free(blocos);

    // Fecha janela
    CloseWindow();

    // Encerra programa
    return 0;
}
```

---

# Explicação COMPLETA da Arquitetura do Jogo

# 1. Struct BlocoMemoria

```c
typedef struct BlocoMemoria
```

Cria:

```text
um tipo personalizado
```

Cada bloco possui:

| Campo | Função |
|---|---|
| posicao | localização |
| tamanho | tamanho do quadrado |
| ativo | se ainda existe |

---

# 2. O que é Vector2

```c
Vector2
```

É uma struct da Raylib:

```c
typedef struct Vector2
{
    float x;
    float y;
} Vector2;
```

Usada para:
- posição
- movimento
- velocidade
- direção

---

# 3. O que malloc faz

```c
malloc()
```

faz:

```text
alocação dinâmica de memória
```

---

# O que acontece internamente

O sistema operacional:

1. reserva RAM
2. retorna endereço
3. ponteiro guarda endereço

---

# Heap

malloc usa:

```text
HEAP
```

Heap é:
- memória dinâmica
- usada para objetos variáveis

---

# Visualização da Heap

```text
HEAP
┌──────────────┐
│ Bloco 0      │
├──────────────┤
│ Bloco 1      │
├──────────────┤
│ Bloco 2      │
├──────────────┤
│ Bloco 3      │
├──────────────┤
│ Bloco 4      │
└──────────────┘
```

---

# 4. O que significa:

```c
BlocoMemoria *blocos
```

Isso significa:

```text
“ponteiro para BlocoMemoria”
```

---

# 5. O que é realloc

```c
realloc()
```

Aumenta:
- memória dinâmica já existente

---

# O que realloc faz internamente

O sistema:

1. tenta aumentar espaço atual
2. se não conseguir:
   - cria nova área
   - copia dados antigos
   - libera área antiga

---

# Visualização do realloc

## Antes

```text
5 blocos
```

---

## Depois

```text
10 blocos
```

---

# 6. O que free faz

```c
free()
```

Libera:
- memória heap

---

# Sem free acontece:

- memory leak
- vazamento de RAM
- travamentos
- consumo infinito

---

# O que é Gameplay Loop

Observe:

```text
mover
↓
colidir
↓
ganhar ponto
↓
mais blocos aparecem
↓
repetir
```

Isso é:

```text
GAMEPLAY LOOP
```

---

# Conceitos profissionais aprendidos

| Conceito | Foi usado |
|---|---|
| Heap | ✔ |
| malloc | ✔ |
| realloc | ✔ |
| free | ✔ |
| Structs | ✔ |
| Collision | ✔ |
| Dynamic Entities | ✔ |
| Gameplay Loop | ✔ |
| Arrays Dinâmicos | ✔ |
| Ponteiros | ✔ |

---

# O que você aprende de verdade

Você entende visualmente:

```text
malloc cria entidades
```

```text
realloc aumenta entidades
```

```text
free libera entidades
```

Isso é MUITO mais forte do que:

```c
int *p;
```

isolado no terminal.

---

# Curiosidade MUITO importante

Esse código já se aproxima de:

- ECS
- Entity Systems
- Data-Oriented Design
- arquiteturas de engines reais

---

# Resultado esperado

Você verá:

- jogador azul
- blocos verdes
- colisão
- score
- crescimento dinâmico de memória

E visualizará:

```text
malloc e realloc funcionando AO VIVO
```

---

# Desafios

## Desafio 1

Adicione:
- música

---

## Desafio 2

Adicione:
- partículas

---

## Desafio 3

Faça:
- inimigos perseguirem jogador

---

## Desafio 4

Use:
- calloc()

---

## Super Desafio

Transforme em:

- survival game
- shooter
- coleta infinita
- mini ECS engine

---

# Próximos passos profissionais

Agora você pode estudar:

| Tema | Nível |
|---|---|
| ECS | Avançado |
| OpenGL | Avançado |
| Physics | Avançado |
| Shaders | Avançado |
| Multiplayer | Avançado |
| Engine Architecture | Avançado |

---

# Parabéns

Você agora já entende:

✅ gameplay loop  
✅ renderização  
✅ colisão  
✅ structs  
✅ ponteiros  
✅ heap  
✅ malloc  
✅ realloc  
✅ free  
✅ entidades dinâmicas  

Isso já é:
- programação profissional
- arquitetura de jogos
- base de game engines reais
