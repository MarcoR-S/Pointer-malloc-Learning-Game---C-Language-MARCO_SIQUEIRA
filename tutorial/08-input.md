# 08 - Input

# Trabalhando com Input de Teclado em Raylib (C)

```c
#include "raylib.h"

int main()
{
    InitWindow(800, 600, "Keyboard Input");

    int x = 350;
    int y = 250;
    int velocidade = 5;

    while (!WindowShouldClose())
    {
        if (IsKeyDown(KEY_RIGHT)) x += velocidade;
        if (IsKeyDown(KEY_LEFT)) x -= velocidade;
        if (IsKeyDown(KEY_UP)) y -= velocidade;
        if (IsKeyDown(KEY_DOWN)) y += velocidade;

        BeginDrawing();

        ClearBackground(RAYWHITE);

        DrawRectangle(x, y, 100, 100, BLUE);

        DrawText("Use as setas do teclado", 10, 10, 20, BLACK);

        EndDrawing();
    }

    CloseWindow();

    return 0;
}
```

---

# O que foi adicionado nesta etapa

Nesta etapa aprendemos:

- teclado
- input
- movimentação controlada pelo jogador
- coordenadas dinâmicas
- atualização de posição
- interação em tempo real

Agora o jogador consegue controlar diretamente o personagem.

---

# Explicação linha por linha

# Importando a Raylib

```c
#include "raylib.h"
```

Importa a biblioteca Raylib.

Ela fornece:
- gráficos
- áudio
- teclado
- mouse
- texturas
- renderização

---

# Função principal

```c
int main()
```

Todo programa em C começa aqui.

O sistema operacional executa:
- `main()`

quando o programa inicia.

---

# Criando a janela

```c
InitWindow(800, 600, "Keyboard Input");
```

Cria a janela do jogo.

Parâmetros:

| Valor | Significado |
|---|---|
| 800 | largura |
| 600 | altura |
| "Keyboard Input" | título |

---

# Variáveis de posição

```c
int x = 350;
int y = 250;
```

Essas variáveis guardam:

| Variável | Função |
|---|---|
| x | posição horizontal |
| y | posição vertical |

---

# O que significa posição

A tela funciona como um plano cartesiano simplificado:

```text
(0,0)
┌────────────────────→ X
│
│
│
↓
Y
```

Importante:
- X cresce para direita
- Y cresce para baixo

---

# Variável velocidade

```c
int velocidade = 5;
```

Define quantos pixels o objeto irá mover por frame.

Neste caso:

```text
5 pixels por frame
```

---

# Loop principal do jogo

```c
while (!WindowShouldClose())
```

Executa continuamente:

- input
- lógica
- renderização
- atualização da tela

Todo jogo funciona assim.

---

# Detectando tecla DIREITA

```c
if (IsKeyDown(KEY_RIGHT)) x += velocidade;
```

Verifica:

```text
“A tecla DIREITA está pressionada?”
```

Se estiver:

```c
x += velocidade;
```

move o quadrado para direita.

---

# Entendendo x += velocidade

Isso significa:

```c
x = x + velocidade;
```

Ou seja:

```text
aumente a posição X
```

---

# Detectando tecla ESQUERDA

```c
if (IsKeyDown(KEY_LEFT)) x -= velocidade;
```

Diminui o valor de:
- X

fazendo o objeto mover para esquerda.

---

# Detectando tecla CIMA

```c
if (IsKeyDown(KEY_UP)) y -= velocidade;
```

Diminui:
- Y

fazendo subir na tela.

Importante:

```text
Y negativo sobe
```

porque no sistema gráfico:
- o topo da tela é zero.

---

# Detectando tecla BAIXO

```c
if (IsKeyDown(KEY_DOWN)) y += velocidade;
```

Aumenta:
- Y

fazendo o objeto descer.

---

# O que é input contínuo

```c
IsKeyDown()
```

significa:

```text
“enquanto a tecla estiver pressionada”
```

Isso gera:
- movimento contínuo

---

# Iniciando renderização

```c
BeginDrawing();
```

Começa o frame atual.

---

# Limpando o fundo

```c
ClearBackground(RAYWHITE);
```

Apaga o frame anterior.

Sem isso:
- o quadrado deixaria rastros

---

# Desenhando o jogador

```c
DrawRectangle(x, y, 100, 100, BLUE);
```

Parâmetros:

| Valor | Significado |
|---|---|
| x | posição horizontal |
| y | posição vertical |
| 100 | largura |
| 100 | altura |
| BLUE | cor |

---

# O mais importante deste código

Observe:

```c
DrawRectangle(x, y, ...)
```

As variáveis:
- x
- y

mudam constantemente.

Isso significa:

```text
o desenho muda de posição a cada frame
```

E isso gera:
- movimento
- animação
- gameplay

---

# Desenhando instruções

```c
DrawText("Use as setas do teclado", 10, 10, 20, BLACK);
```

Mostra texto na tela.

---

# Finalizando renderização

```c
EndDrawing();
```

Entrega o frame pronto para GPU.

---

# Fechando janela

```c
CloseWindow();
```

Libera recursos corretamente.

---

# Fluxo visual do programa

```text
Teclado
   ↓
IsKeyDown()
   ↓
Atualiza X/Y
   ↓
DrawRectangle()
   ↓
GPU desenha
   ↓
Monitor exibe
```

---

# O que acontece internamente

Quando o jogador aperta uma tecla:

1. sistema operacional detecta teclado
2. Raylib lê input
3. CPU atualiza posição
4. GPU desenha novo frame
5. monitor mostra movimento

Tudo isso acontece:
- dezenas de vezes por segundo

---

# Conceito novo aprendido

| Conceito | Explicação |
|---|---|
| Input | entrada do jogador |
| Coordenadas | posição na tela |
| Atualização contínua | mudança frame a frame |
| Movimento | alteração de posição |
| Estado | valores atuais do jogo |

---

# Curiosidade MUITO importante

Quando fazemos:

```c
x += velocidade;
```

o compilador acessa:
- memória RAM
- variáveis internas
- posição armazenada

Ou seja:

```text
movimento é literalmente alteração de memória
```

Isso prepara o cérebro para:
- structs
- ponteiros
- malloc
- memória dinâmica

que veremos futuramente.

---

# Resultado esperado

Você verá:

- um quadrado azul
- controlado pelas setas do teclado
- movendo livremente pela tela

---

# Desafio

## Desafio 1

Aumente velocidade:

```c
int velocidade = 15;
```

---

## Desafio 2

Troque a cor:

```c
BLUE
```

por:

```c
RED
```

---

## Desafio 3

Permita movimento diagonal.

---

## Desafio 4

Impeça o jogador de sair da tela.

Dica:

```c
if (x < 0)
{
    x = 0;
}
```

---

## Super Desafio

Crie:

- Player 1 usando WASD
- Player 2 usando SETAS

---

# Próximo passo

Na próxima etapa iremos aprender:

- colisão
- hitbox
- interação entre objetos

usando:

```c
CheckCollisionRecs();
```
