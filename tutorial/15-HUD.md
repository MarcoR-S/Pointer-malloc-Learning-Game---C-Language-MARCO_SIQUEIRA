# 15 - HUD

# Criando HUD (Interface do Jogador) em Raylib (C)

# Objetivo da Aula

Nesta aula iremos aprender a criar uma:

```text
HUD
```

HUD significa:

```text
Heads-Up Display
```

Ou seja:

```text
interface visual do jogador
```

A HUD mostra informações importantes durante o jogo:

- vida
- score
- munição
- tempo
- energia
- minimapa
- itens
- status

---

# O que iremos aprender

Nesta aula vamos criar:

- score
- vida
- barra de vida
- munição
- tempo
- mensagens na tela
- interface fixa

Tudo isso será desenhado sobre o jogo.

---

# O que é HUD nos jogos

Exemplos famosos:

| Jogo | HUD |
|---|---|
| Mario | moedas e vidas |
| Doom | vida e munição |
| GTA | mapa e dinheiro |
| Fortnite | vida e inventário |
| Minecraft | coração e fome |

---

# Código Completo

```c
// =========================================
// IMPORTA RAYLIB
// =========================================

#include "raylib.h"

// =========================================
// MAIN
// =========================================

int main(void)
{
    // Cria janela
    InitWindow(1000, 600, "HUD em Raylib");

    // Define FPS
    SetTargetFPS(60);

    // =========================================
    // JOGADOR
    // =========================================

    // Posição inicial
    Vector2 jogador = { 480, 300 };

    // Velocidade
    float velocidade = 4.0f;

    // =========================================
    // HUD
    // =========================================

    // Pontuação
    int score = 0;

    // Vida atual
    int vida = 100;

    // Munição
    int municao = 30;

    // Tempo de jogo
    float tempo = 0;

    // =========================================
    // LOOP PRINCIPAL
    // =========================================

    while (!WindowShouldClose())
    {
        // =========================================
        // UPDATE
        // =========================================

        // Atualiza tempo
        tempo += GetFrameTime();

        // Movimento direita
        if (IsKeyDown(KEY_RIGHT))
            jogador.x += velocidade;

        // Movimento esquerda
        if (IsKeyDown(KEY_LEFT))
            jogador.x -= velocidade;

        // Movimento cima
        if (IsKeyDown(KEY_UP))
            jogador.y -= velocidade;

        // Movimento baixo
        if (IsKeyDown(KEY_DOWN))
            jogador.y += velocidade;

        // Simula ganhar pontos
        if (IsKeyPressed(KEY_P))
        {
            score += 10;
        }

        // Simula tomar dano
        if (IsKeyPressed(KEY_H))
        {
            vida -= 10;

            if (vida < 0)
                vida = 0;
        }

        // Simula gastar munição
        if (IsKeyPressed(KEY_SPACE))
        {
            municao--;

            if (municao < 0)
                municao = 0;
        }

        // =========================================
        // DRAW
        // =========================================

        BeginDrawing();

        // Fundo
        ClearBackground(RAYWHITE);

        // =========================================
        // MUNDO DO JOGO
        // =========================================

        // Desenha jogador
        DrawRectangleV(
            jogador,
            (Vector2){40, 40},
            BLUE
        );

        // =========================================
        // HUD
        // =========================================

        // Fundo da HUD
        DrawRectangle(
            0,
            0,
            1000,
            115,
            LIGHTGRAY
        );

        // Linha separadora
        DrawLine(
            0,
            115,
            1000,
            115,
            DARKGRAY
        );

        // Título
        DrawText(
            "HUD DO JOGO",
            20,
            15,
            28,
            DARKBLUE
        );

        // Score
        DrawText(
            TextFormat("Score: %d", score),
            20,
            65,
            20,
            BLACK
        );

        // Vida
        DrawText(
            TextFormat("Vida: %d", vida),
            220,
            65,
            20,
            BLACK
        );

        // =========================================
        // BARRA DE VIDA
        // =========================================

        // Fundo vermelho da barra
        DrawRectangle(
            220,
            40,
            200,
            20,
            RED
        );

        // Vida verde
        DrawRectangle(
            220,
            40,
            vida * 2,
            20,
            GREEN
        );

        // Borda da barra
        DrawRectangleLines(
            220,
            40,
            200,
            20,
            BLACK
        );

        // Munição
        DrawText(
            TextFormat("Municao: %d", municao),
            470,
            65,
            20,
            BLACK
        );

        // Tempo
        DrawText(
            TextFormat("Tempo: %.1f", tempo),
            700,
            65,
            20,
            BLACK
        );

        // Texto explicativo
        DrawText(
            "P = Pontos | H = Dano | ESPACO = Gasta Municao",
            20,
            560,
            18,
            MAROON
        );

        EndDrawing();
    }

    // Fecha janela
    CloseWindow();

    return 0;
}
```

---

# Explicação COMPLETA da Arquitetura

# 1. O que é HUD

HUD significa:

```text
informações desenhadas sobre o jogo
```

A HUD normalmente:

- não faz parte do mundo
- fica fixa na tela
- acompanha jogador

---

# Exemplo visual

```text
┌──────────────────────────────────────────────┐
│ HUD DO JOGO                                  │
│ Score: 0  Vida: 100  Munição: 30  Tempo: 0  │
├──────────────────────────────────────────────┤
│                                              │
│                                              │
│              MUNDO DO JOGO                   │
│                                              │
│                                              │
└──────────────────────────────────────────────┘
```

---

# 2. Variáveis da HUD

```c
int score = 0;
int vida = 100;
int municao = 30;
float tempo = 0;
```

Essas variáveis representam:

| Variável | Função |
|---|---|
| score | pontuação |
| vida | HP do jogador |
| municao | tiros restantes |
| tempo | tempo de jogo |

---

# 3. Atualizando tempo

```c
tempo += GetFrameTime();
```

---

# O que GetFrameTime faz

```c
GetFrameTime()
```

retorna:

```text
tempo entre um frame e outro
```

Exemplo:

```text
0.016 segundos
```

em 60 FPS.

---

# Resultado

O tempo cresce suavemente:

```text
0.1
0.2
0.3
0.4
```

Isso significa que estamos usando tempo real, e não apenas contagem de frames.

---

# 4. Sistema de Score

```c
if (IsKeyPressed(KEY_P))
{
    score += 10;
}
```

Cada vez que o jogador aperta `P`:

```text
ganha 10 pontos
```

Esse valor aparece na HUD usando:

```c
DrawText(
    TextFormat("Score: %d", score),
    20,
    65,
    20,
    BLACK
);
```

---

# 5. Sistema de Vida

```c
if (IsKeyPressed(KEY_H))
{
    vida -= 10;

    if (vida < 0)
        vida = 0;
}
```

Cada vez que o jogador aperta `H`:

```text
perde 10 pontos de vida
```

---

# Proteção contra vida negativa

```c
if (vida < 0)
    vida = 0;
```

Evita:

```text
vida negativa
```

Sem isso, a HUD poderia mostrar:

```text
Vida: -10
Vida: -20
Vida: -30
```

O que não faz sentido para o jogador.

---

# 6. Sistema de Munição

```c
if (IsKeyPressed(KEY_SPACE))
{
    municao--;

    if (municao < 0)
        municao = 0;
}
```

Simula:

- uso de munição
- disparo
- gasto de recurso

---

# Proteção contra munição negativa

```c
if (municao < 0)
    municao = 0;
```

Evita:

```text
Municao: -1
Municao: -2
Municao: -3
```

---

# 7. Fundo da HUD

```c
DrawRectangle(
    0,
    0,
    1000,
    115,
    LIGHTGRAY
);
```

Cria:

```text
um painel superior cinza
```

Esse painel funciona como a área visual da HUD.

---

# Por que aumentamos de 90 para 115?

Na versão anterior, a barra de vida ficava muito próxima dos textos.

Agora usamos:

```c
altura = 115
```

para dar mais espaço visual.

Isso melhora:

- legibilidade
- organização
- separação entre HUD e mundo do jogo

---

# 8. Linha separadora

```c
DrawLine(
    0,
    115,
    1000,
    115,
    DARKGRAY
);
```

Desenha uma linha horizontal.

Ela separa:

- HUD
- mundo do jogo

---

# 9. TextFormat()

```c
TextFormat("Score: %d", score)
```

Permite inserir:

```text
variáveis dentro de textos
```

---

# O que significa %d

```text
%d = número inteiro
```

Usamos `%d` para:

- score
- vida
- munição

Exemplo:

```c
TextFormat("Vida: %d", vida)
```

---

# O que significa %.1f

```text
%.1f = número decimal com 1 casa
```

Usamos em:

```c
TextFormat("Tempo: %.1f", tempo)
```

Isso mostra:

```text
Tempo: 3.1
Tempo: 3.2
Tempo: 3.3
```

em vez de mostrar muitas casas decimais.

---

# 10. Barra de vida

Primeiro desenhamos o fundo vermelho:

```c
DrawRectangle(
    220,
    40,
    200,
    20,
    RED
);
```

Esse fundo representa:

```text
vida total possível
```

---

Depois desenhamos a vida atual em verde:

```c
DrawRectangle(
    220,
    40,
    vida * 2,
    20,
    GREEN
);
```

Esse retângulo verde representa:

```text
vida restante
```

---

Depois desenhamos a borda:

```c
DrawRectangleLines(
    220,
    40,
    200,
    20,
    BLACK
);
```

A borda ajuda o jogador a enxergar melhor o limite da barra.

---

# O mais importante

Observe:

```c
vida * 2
```

Isso transforma:

```text
100 de vida
```

em:

```text
200 pixels
```

Porque:

```text
100 * 2 = 200
```

---

# Quando perde vida

Se a vida cair para 80:

```text
80 * 2 = 160 pixels
```

Se cair para 50:

```text
50 * 2 = 100 pixels
```

Se cair para 25:

```text
25 * 2 = 50 pixels
```

---

# Visualização da barra

Vida cheia:

```text
████████████████████
```

Vida pela metade:

```text
██████████
```

Vida baixa:

```text
████
```

---

# 11. HUD fixa

A HUD:

- NÃO se move
- NÃO depende da posição do jogador
- NÃO depende do mundo
- fica sempre no mesmo lugar da tela

Isso é MUITO importante em jogos.

Mesmo que o personagem se mova, a HUD continua fixa.

---

# 12. Mundo do jogo

```c
DrawRectangleV(
    jogador,
    (Vector2){40, 40},
    BLUE
);
```

Desenha o jogador como um quadrado azul.

Essa parte representa:

```text
o mundo do jogo
```

---

# Diferença entre HUD e mundo

| Parte | Função |
|---|---|
| Mundo | onde o jogo acontece |
| HUD | mostra informações do jogo |

---

# Fluxo do programa

```text
INPUT
   ↓
Atualiza score/vida/munição/tempo
   ↓
Move jogador
   ↓
Renderiza mundo
   ↓
Renderiza HUD
   ↓
Mostra tudo na tela
```

---

# Conceitos profissionais aprendidos

| Conceito | Foi usado |
|---|---|
| HUD | ✔ |
| Barra de Vida | ✔ |
| Score | ✔ |
| Tempo | ✔ |
| Munição | ✔ |
| Interface | ✔ |
| TextFormat | ✔ |
| UI Básica | ✔ |
| Overlay | ✔ |
| Feedback Visual | ✔ |

---

# O que você aprende de verdade

você começa a entender:

```text
jogo não é apenas personagem andando
```

Jogos também possuem:

- interface
- feedback visual
- informações em tempo real
- estado do jogador
- comunicação visual com usuário

---

# Curiosidade MUITO importante

Mesmo jogos grandes usam:

- HUDs
- overlays
- barras
- indicadores
- feedback visual

A HUD é uma das partes mais importantes para:

- UX
- gameplay
- experiência do jogador
- tomada de decisão durante a partida

---

# Resultado esperado

Você verá:

✅ jogador azul  
✅ score  
✅ barra de vida com borda  
✅ munição  
✅ tempo de jogo  
✅ HUD fixa no topo  
✅ instruções na parte inferior  

---

# Atividade da Aula

## Exercício 1

Adicione:

- moedas
- energia
- XP

---

## Exercício 2

Crie:

- minimapa simples

---

## Exercício 3

Faça:

- barra de mana

---

# Desafio Extra

Adicione:

- ícones
- imagens
- sprites na HUD

---

# Super Desafio

Crie uma HUD completa com:

```text
vida
mana
xp
nível
mini mapa
arma atual
inventário
```

---

# Próximo passo

Na próxima aula podemos evoluir para:

```text
16 - Particles.md
```

onde iremos aprender:

- partículas
- explosões
- efeitos visuais
- fumaça
- brilho
- feedback visual avançado
