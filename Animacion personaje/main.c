#include "raylib.h"
#include <stdio.h>

#define GRAVEDAD 1200
#define SALTO_VELOCIDAD 600.0f
#define VELOCIDAD_HORIZONTAL 300.0f
#define ALTURA_SUELO 50 // Ajustar para que el suelo esté más abajo

typedef struct Jugador {
    Rectangle rect;
    Vector2 velocidad;
    bool enSuelo;
    int estado; // 0: descansando, 1: saltando, 2: caminando, 3: muerte
    bool mirandoDerecha; // Indica si el jugador está mirando a la derecha
} Jugador;

// Estructura para una animación de textura
typedef struct {
    Texture2D *textures;
    int frameCount;
    int currentFrame;
    float frameDuration;
    float frameTime;
} TextureAnimation;

void ActualizarJugador(Jugador *jugador, float delta);

int main(void)
{
    // Inicializar ventana
    const int screenWidth = 1000;
    const int screenHeight = 500;
    InitWindow(screenWidth, screenHeight, "Ejemplo - Dibujar y Mover PNG");

    // Cargar las texturas del sprite
    Texture2D descanso[4];
    descanso[0] = LoadTexture("Sprite-descanso01.png");
    descanso[1] = LoadTexture("Sprite-descanso02.png");
    descanso[2] = LoadTexture("Sprite-descanso03.png");
    descanso[3] = LoadTexture("Sprite-descanso04.png");

    Texture2D caminar[4];
    caminar[0] = LoadTexture("Sprite-caminar01.png");
    caminar[1] = LoadTexture("Sprite-caminar02.png");
    caminar[2] = LoadTexture("Sprite-caminar01.png");
    caminar[3] = LoadTexture("Sprite-caminar04.png");

    Texture2D salto[5];
    salto[0] = LoadTexture("Sprite-salto01.png");
    salto[1] = LoadTexture("Sprite-salto02.png");
    salto[2] = LoadTexture("Sprite-salto03.png");
    salto[3] = LoadTexture("Sprite-salto04.png");
    salto[4] = LoadTexture("Sprite-salto05.png");

    Texture2D muerte[4];
    muerte[0] = LoadTexture("Sprite-muerte01.png");
    muerte[1] = LoadTexture("Sprite-muerte02.png");
    muerte[2] = LoadTexture("Sprite-muerte03.png");
    muerte[3] = LoadTexture("Sprite-muerte04.png");

    Texture2D slime[5];
    slime[0] = LoadTexture("Sprite-slime01.png");
    slime[1] = LoadTexture("Sprite-slime02.png");
    slime[2] = LoadTexture("Sprite-slime03.png");
    slime[3] = LoadTexture("Sprite-slime04.png");
    slime[4] = LoadTexture("Sprite-slime0.png");

    Texture2D pico = LoadTexture("Sprite-picos.png");
    // Comprobar si las texturas se han cargado correctamente
    bool texturesLoaded = true;
    for (int i = 0; i < 4; i++) {
        if (descanso[i].id == 0 || caminar[i].id == 0) {
            texturesLoaded = false;
            printf("Error al cargar la textura descanso[%d] o caminar[%d].\n", i, i);
            break;
        }
    }

    for (int i = 0; i < 5; i++) {
        if (salto[i].id == 0) {
            texturesLoaded = false;
            printf("Error al cargar la textura salto[%d].\n", i);
            break;
        }
    }

    for (int i = 0; i < 4; i++) {
        if (muerte[i].id == 0) {
            texturesLoaded = false;
            printf("Error al cargar la textura muerte[%d].\n", i);
            break;
        }
    }

    if (!texturesLoaded) {
        printf("Error al cargar una de las texturas.\n");
        CloseWindow();
        return 1;
    }

    // Inicializar las animaciones de textura
    TextureAnimation animaciones[4];
    animaciones[0] = (TextureAnimation){descanso, 4, 0, 0.25f, 0.0f};
    animaciones[1] = (TextureAnimation){salto, 5, 0, 0.2f, 0.0f}; // Cada frame dura 0.2 segundos
    animaciones[2] = (TextureAnimation){caminar, 4, 0, 0.1f, 0.0f}; // Cada frame dura 0.1 segundos
    animaciones[3] = (TextureAnimation){muerte, 4, 0, 0.3f, 0.0f}; // Cada frame dura 0.3 segundos

    // Inicializar el jugador
    Jugador jugador = { 0 };
    jugador.rect = (Rectangle){ screenWidth / 2 - descanso[0].width * 3 / 2, screenHeight - ALTURA_SUELO - descanso[0].height * 3, descanso[0].width * 3, descanso[0].height * 3 };
    jugador.velocidad = (Vector2){ 0, 0 };
    jugador.enSuelo = true;
    jugador.estado = 0; // Inicialmente está descansando
    jugador.mirandoDerecha = true; // Inicialmente está mirando a la derecha

    // Establecer objetivo de frames por segundo
    SetTargetFPS(60);

    // Bucle principal del juego
    while (!WindowShouldClose())
    {
        float deltaTime = GetFrameTime();

        // Actualizar animación de muerte si está en estado de muerte
        if (jugador.estado == 3) {
            TextureAnimation *animacionActual = &animaciones[jugador.estado];
            animacionActual->frameTime += deltaTime;
            if (animacionActual->frameTime >= animacionActual->frameDuration) {
                animacionActual->frameTime = 0.0f;
                animacionActual->currentFrame++;
                if (animacionActual->currentFrame >= animacionActual->frameCount) {
                    // Reiniciar jugador después de la animación de muerte
                    jugador.rect.x = screenWidth / 2 - descanso[0].width * 3 / 2;
                    jugador.rect.y = screenHeight - ALTURA_SUELO - descanso[0].height * 3;
                    jugador.velocidad = (Vector2){ 0, 0 };
                    jugador.enSuelo = true;
                    jugador.estado = 0; // Volver a descansar
                    jugador.mirandoDerecha = true; // Volver a mirar a la derecha
                    animacionActual->currentFrame = 0; // Reiniciar la animación de muerte
                }
            }
        } else {
            ActualizarJugador(&jugador, deltaTime);
        }

        // Limitar el movimiento dentro de la ventana
        if (jugador.rect.x < 0) jugador.rect.x = 0;
        if (jugador.rect.x + jugador.rect.width > screenWidth) jugador.rect.x = screenWidth - jugador.rect.width;

        // Actualizar animación
        if (jugador.estado != 3) {
            TextureAnimation *animacionActual = &animaciones[jugador.estado];
            animacionActual->frameTime += deltaTime;
            if (animacionActual->frameTime >= animacionActual->frameDuration) {
                animacionActual->frameTime = 0.0f;
                animacionActual->currentFrame++;
                if (animacionActual->currentFrame >= animacionActual->frameCount) {
                    animacionActual->currentFrame = 0;
                }
            }
        }

        // Dibujar
        BeginDrawing();
        ClearBackground(BLACK);

        // Dibujar la imagen usando la textura y escalando
        TextureAnimation *animacionActual = &animaciones[jugador.estado];
        Rectangle source = { 0.0f, 0.0f, (float)animacionActual->textures[animacionActual->currentFrame].width, (float)animacionActual->textures[animacionActual->currentFrame].height };
        Rectangle dest = { jugador.rect.x, jugador.rect.y, jugador.rect.width, jugador.rect.height };
        Vector2 origin = { 0.0f, 0.0f };
        if (!jugador.mirandoDerecha) {
            source.width *= -1; // Invertir la imagen horizontalmente
        }

        DrawTexturePro(animacionActual->textures[animacionActual->currentFrame], source, dest, origin, 0.0f, WHITE);

        DrawText("¡Hola, Raylib!", 10, 10, 20, DARKGRAY);

        EndDrawing();
    }

    // Descargar las texturas
    for (int i = 0; i < 4; i++) {
        UnloadTexture(descanso[i]);
        UnloadTexture(caminar[i]);
    }
    for (int i = 0; i < 5; i++) {
        UnloadTexture(salto[i]);
    }
    for (int i = 0; i < 4; i++) {
        UnloadTexture(muerte[i]);
    }

    // Cerrar ventana
    CloseWindow();

    return 0;
}

void ActualizarJugador(Jugador *jugador, float delta) {
    bool moviendoHorizontal = false;

    if (IsKeyDown(KEY_LEFT)) {
        jugador->rect.x -= VELOCIDAD_HORIZONTAL * delta;
        jugador->mirandoDerecha = false; // Mirar a la izquierda
        moviendoHorizontal = true;
    }
    if (IsKeyDown(KEY_RIGHT)) {
        jugador->rect.x += VELOCIDAD_HORIZONTAL * delta;
        jugador->mirandoDerecha = true; // Mirar a la derecha
        moviendoHorizontal = true;
    }

    if (moviendoHorizontal && jugador->enSuelo) {
        jugador->estado = 2; // Caminando
    } else if (!moviendoHorizontal && jugador->enSuelo) {
        jugador->estado = 0; // Descansando
    }

    if (!jugador->enSuelo) {
        jugador->velocidad.y += GRAVEDAD * delta;
    }

    if ((IsKeyPressed(KEY_SPACE) || IsKeyPressed(KEY_W) || IsKeyPressed(KEY_UP)) && jugador->enSuelo) {
        jugador->velocidad.y = -SALTO_VELOCIDAD;
        jugador->enSuelo = false;
        jugador->estado = 1; // Saltando
    }

    jugador->rect.y += jugador->velocidad.y * delta;

    if (jugador->rect.y >= GetScreenHeight() - ALTURA_SUELO - jugador->rect.height) {
        jugador->enSuelo = true;
        jugador->rect.y = GetScreenHeight() - ALTURA_SUELO - jugador->rect.height;
        jugador->velocidad.y = 0;
        if (!moviendoHorizontal) {
            jugador->estado = 0; // Descansando
        }
    } else {
        jugador->enSuelo = false;
    }

    // Activar animación de muerte y reiniciar jugador
    if (IsKeyPressed(KEY_X)) {
        jugador->estado = 3; // Muerte
        jugador->velocidad = (Vector2){0, 0}; // Detener al jugador
    }
}
