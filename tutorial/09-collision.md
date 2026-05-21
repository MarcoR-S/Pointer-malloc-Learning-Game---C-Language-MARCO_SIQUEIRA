# 09 - Collision

# Colisão em Raylib (C)

```c
#include "raylib.h"

int main()
{
    InitWindow(800, 600, "Collision");

    Rectangle player = {100, 200, 100, 100};
    Rectangle enemy = {500, 200, 100, 100};

    while (!WindowShouldClose())
    {
        if (IsKeyDown(KEY_RIGHT)) player.x += 5;
        if (IsKeyDown(KEY_LEFT)) player.x -= 5;

        bool collision = CheckCollisionRecs(player, enemy);

        BeginDrawing();

        ClearBackground(RAYWHITE);

        DrawRectangleRec(player, BLUE);

        if (collision)
            DrawRectangleRec(enemy, RED);
        else
            DrawRectangleRec(enemy, GREEN);

        DrawText("Encoste no bloco", 10, 10, 20, BLACK);

        EndDrawing();
    }

    CloseWindow();

    return 0;
}
```

---

# O que foi adicionado nesta etapa

Aprendemos:
- colisão
- hitbox
- Rectangle
- interação entre objetos

---

# O que é colisão

Colisão significa:

> detectar quando dois objetos se encostam.

---

# Estrutura Rectangle

```c
Rectangle player
```

Guarda:
- posição
- largura
- altura

---

# CheckCollisionRecs

```c
CheckCollisionRecs(player, enemy);
```

Verifica:
- se os retângulos se tocaram.

---

# Resultado esperado

Quando o jogador tocar:
- inimigo fica vermelho.

---

# Conceito novo aprendido

| Conceito | Explicação |
|---|---|
| Colisão | contato entre objetos |
| Hitbox | área invisível |
| Rectangle | estrutura geométrica |

---

# Desafio

## Desafio 1

Adicione colisão vertical.

## Desafio 2

Crie vários inimigos.

## Desafio 3

Mostre mensagem ao colidir.

---

# Próximo passo

Na próxima etapa iremos aprender:
- tiros
- projéteis
- shooting
