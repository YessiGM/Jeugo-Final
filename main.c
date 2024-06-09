#include "raylib.h"
#include "niveles.h"
#include "plataformas.h"
// Definición de estados del juego
typedef enum PantallaJuego
{
    MENU = 0,
    NIVELES,
    SALIR,
    NIVELEASY,
    NIVELNORMAL,
    NIVELHARD
} PantallaJuego;
float volumenActual = 0.5f; // Valor inicial de volumen (por ejemplo, la mitad del volumen máximo)
Color cafeOscuro = {139, 69, 19, 255};
Color cafeOscuroB = {121, 55, 8, 255};
Color Rojos = {192, 6, 4, 255};
Color Verde = {38, 76, 13, 0.8};

// Declaraciones de funciones
void DibujarMenu(PantallaJuego *pantallaActual, Font font, Sound sound2, Sound *soundmenu);
void DibujarPreguntas(Font font);
void DibujarNiveles(PantallaJuego *pantallaActual, Font font, Sound sound2, Sound *soudnmenu);
void DibujarNE(PantallaJuego *pantallaActual, Font font, Sound sound2);
void DibujarNN(PantallaJuego *pantallaActual, Font font, Sound sound2);
void DibujarNH(PantallaJuego *pantallaActual, Font font, Sound sound2);
void DibujarVolumen(Font font, Sound sound2, Sound soundmenu);
// void sonidoSalto(Sound *sonidoSalto);
void sonido2(Sound *sound2);
void sonidomenu(Sound *soundmenu);
void limpiarRecursos(Texture2D texture, Texture2D texture2, Texture2D texture3, Font font, Sound sound, Sound sound2, Sound soundmenu);
void DrawPlatform(float posX, float posY, int platformType, char platformPart, Texture2D baseTexture, Texture2D esquinaIzqTexture, Texture2D esquinaDerTexture, Texture2D centroBaseTexture, Texture2D centroIzqTexture, Texture2D centroDerTexture, Texture2D sueloBaseTexture, Texture2D sueloIzqTexture, Texture2D sueloDerTexture, Texture2D baseTexture2, Texture2D esquinaIzqTexture2, Texture2D esquinaDerTexture2, Texture2D baseTexture3, Texture2D baseTexture4, Texture2D centroTexture, Texture2D abajoTexture);
void InvertVerticalPlatformBase(float posX, float posY, Texture2D baseTexture4);

int main(void)
{
    const int screenWidth = 1000;
    const int screenHeight = 500;

    InitWindow(screenWidth, screenHeight, "JUEGO PRUEBA");

    // Variables del programa
    Image image = LoadImage("logo2.png");
    Font font = LoadFont("The_Last_Shuriken.otf");

    // Escalar la imagen al tamaño de la ventana
    const float scaleFactor = 0.5f;
    ImageResize(&image, (int)(image.width * scaleFactor), (int)(image.height * scaleFactor));

    Texture2D texture = LoadTextureFromImage(image);
    UnloadImage(image);

    float alpha = 0.0f;
    const float fadeSpeed = 1.0f / (12.0f * 60.0f); // 12 segundos de desvanecimiento a 60 FPS

    InitAudioDevice();

    Sound sound = LoadSound("imu.wav");

    PlaySound(sound);

    PantallaJuego pantallaActual = MENU;

    // Animación de desvanecimiento al inicio de la aplicación
    while (alpha < 1.0f && !WindowShouldClose())
    {
        alpha += fadeSpeed;

        BeginDrawing();
        ClearBackground(RAYWHITE);
        DrawRectangle(0, 0, screenWidth, screenHeight, WHITE);
        DrawTexturePro(texture, (Rectangle){0.0f, 0.0f, (float)texture.width, (float)texture.height},
                       (Rectangle){screenWidth / 2 - texture.width / 2, screenHeight / 2 - texture.height / 2,
                                   (float)texture.width, (float)texture.height},
                       (Vector2){0, 0}, 0.0f, Fade(WHITE, alpha));
        EndDrawing();
    }

    // Esperar 2 segundos antes de hacer que la imagen desaparezca
    WaitTime(2.0f);

    // Animación de desvanecimiento para hacer que la imagen desaparezca
    while (alpha > 0.0f && !WindowShouldClose())
    {
        alpha -= fadeSpeed;

        BeginDrawing();
        ClearBackground(RAYWHITE);
        DrawRectangle(0, 0, screenWidth, screenHeight, WHITE);
        DrawTexturePro(texture, (Rectangle){0.0f, 0.0f, (float)texture.width, (float)texture.height},
                       (Rectangle){screenWidth / 2 - texture.width / 2, screenHeight / 2 - texture.height / 2,
                                   (float)texture.width, (float)texture.height},
                       (Vector2){0, 0}, 0.0f, Fade(WHITE, alpha));
        EndDrawing();
    }

    // Reproducir sonido de carga
    Sound sound2;
    sonido2(&sound2);
    // Sound soundSalto;

    Sound soundmenu;
    soundmenu = LoadSound("soundmenu.wav");

    // Mostrar "Cargando..." en un fondo negro
    float loadingTime = 6.0f; // 6 segundos de pantalla de carga
    double startTime = GetTime();
    while ((GetTime() - startTime < loadingTime) && !WindowShouldClose())
    {
        BeginDrawing();
        ClearBackground(BLACK);
        DrawTextEx(font, "C a r g a n d o . . .", (Vector2){screenWidth / 2 - MeasureTextEx(font, "C a r g a n d o . . .", 50, 0).x / 2, screenHeight / 2 - 10}, 50, 0, WHITE);
        EndDrawing();
    }

    // Cargar la textura para "menu.png"
    Image image2 = LoadImage("menu.png");
    Texture2D texture2 = LoadTextureFromImage(image2);
    UnloadImage(image2);

    // Carga la textura para "Niveles"
    Image image3 = LoadImage("Niveles.png");
    int nuevaAncho = 1000, nuevoAltura = 500;
    ImageResize(&image3, nuevaAncho, nuevoAltura);
    Texture2D texture3 = LoadTextureFromImage(image3);
    UnloadImage(image3);

    // Mostrar la imagen "menu.png" en toda la pantalla
    while (pantallaActual != SALIR && !WindowShouldClose())
    {

        if (pantallaActual == MENU)
        {
            DrawTexture(texture2, 0, 0, WHITE);                     // Dibujar el fondo del menú
            DibujarMenu(&pantallaActual, font, sound2, &soundmenu); // Dibujar los elementos del menú
            DibujarVolumen(font, sound2, soundmenu);
        }

        BeginDrawing();
        ClearBackground(RAYWHITE);

        if (pantallaActual == NIVELES)
        {
            DrawTexture(texture3, 0, 0, WHITE); // Dibujar el fondo de los niveles
            DibujarNiveles(&pantallaActual, font, sound2, &soundmenu);
            DibujarVolumen(font, sound2, soundmenu);
        }
        if (pantallaActual == NIVELEASY)
        {
            StopSound(soundmenu); // Detener sonido del menú al cambiar de pantalla
            DibujarNE(&pantallaActual, font, sound2);

            // Inicialización
            const int anchoPantalla = 1000;
            const int altoPantalla = 500;

            InitWindow(anchoPantalla, altoPantalla, "Juego");
            // Cargar texturas de las plataformas
            Texture2D baseTexture = LoadTexture("Sprite-p_base.png");
            Texture2D esquinaIzqTexture = LoadTexture("Sprite-p_esquinaIZQ.png");
            Texture2D esquinaDerTexture = LoadTexture("Sprite-p_esquinaDER.png");
            Texture2D centroBaseTexture = LoadTexture("Sprite-p_centrobase.png");
            Texture2D centroIzqTexture = LoadTexture("Sprite-p_centroIZQ.png");
            Texture2D centroDerTexture = LoadTexture("Sprite-p_centroDER.png");
            Texture2D sueloBaseTexture = LoadTexture("Sprite-p_suelobase.png");
            Texture2D sueloIzqTexture = LoadTexture("Sprite-p_sueloIZQ.png");
            Texture2D sueloDerTexture = LoadTexture("Sprite-p_sueloDER.png");
            Texture2D baseTexture2 = LoadTexture("Sprite-p2_base.png");
            Texture2D esquinaIzqTexture2 = LoadTexture("Sprite-p2_esquinaIZQ.png");
            Texture2D esquinaDerTexture2 = LoadTexture("Sprite-p2_esquinaDER.png");
            Texture2D baseTexture3 = LoadTexture("Sprite-p3_base.png");
            Texture2D baseTexture4 = LoadTexture("Sprite-p4_base.png");
            Texture2D centroTexture = LoadTexture("Sprite-p4_centro.png");
            Texture2D abajoTexture = LoadTexture("Sprite-p4_abajo.png");

            Jugador jugador = {0};
            jugador.posicion = (Vector2){400, 280};
            jugador.velocidad = 0;
            jugador.puedeSaltar = false;

            ObjetoEntorno objetosEntorno[] = {
                {{-10000, 400, 20000, 200}, 1, GRAY},
                {{400, 300, 100, 10}, 1, GRAY}, // 1 plataforma
                {{650, 150, 100, 10}, 1, GRAY},
                {{900, 0, 100, 10}, 1, GRAY},
                {{650, -150, 100, 10}, 1, GRAY},
                {{400, -300, 100, 10}, 1, GRAY},
                {{650, -450, 100, 10}, 1, GRAY},
                // Primera pregunta
                {{400, -600, 400, 10}, 1, DARKGRAY},
                // lado correcto                                                       lado incorrecto
                {{200, -750, 100, 10}, 1, GRAY},
                {{900, -750, 100, 10}, 1, GRAY},
                {{-50, -900, 100, 10}, 1, GRAY},
                {{1150, -900, 100, 10}, 1, GRAY},
                {{-300, -1050, 100, 10}, 1, GRAY},
                {{1300, -1050, 100, 10}, 1, GRAY},
                {{-550, -1200, 100, 10}, 1, GRAY},
                {{-300, -1350, 100, 10}, 1, GRAY},
                {{-550, -1500, 100, 10}, 1, GRAY},
                // Segunda pregunta
                {{-800, -1650, 400, 10}, 1, DARKGRAY},
                // lado correcto                                                        lado incorrecto
                {{-1000, -1800, 100, 10}, 1, GRAY},
                {{-300, -1800, 100, 10}, 1, GRAY},
                {{-1250, -1950, 100, 10}, 1, GRAY},
                {{-50, -1950, 100, 10}, 1, GRAY},
                {{-1000, -2100, 100, 10}, 1, GRAY},
                {{200, -2100, 100, 10}, 1, GRAY},
                {{-1250, -2250, 100, 10}, 1, GRAY},
                {{-1500, -2400, 100, 10}, 1, GRAY},
                {{-1750, -2550, 100, 10}, 1, GRAY},
                // Tercera pregunta
                {{-1500, -2700, 400, 10}, 1, DARKGRAY},
                // lado correcto                                                        lado incorrecto
                {{-1000, -2850, 100, 10}, 1, GRAY},
                {{-1700, -2850, 100, 10}, 1, GRAY},
                {{-750, -3000, 100, 10}, 1, GRAY},
                {{-1950, -3000, 100, 10}, 1, GRAY},
                {{-1000, -3150, 100, 10}, 1, GRAY},
                {{-2200, -3150, 100, 10}, 1, GRAY},
                {{-750, -3300, 100, 10}, 1, GRAY},
                {{-500, -3450, 100, 10}, 1, GRAY},
                {{-250, -3600, 100, 10}, 1, GRAY},
                {{0, -3750, 600, 10}, 1, DARKGRAY}, // fin

            };
            
            // Definir las plataformas
            Platform platforms[] = {
                {325, 270, 2, 'i'}, //{{400, 300, 100, 10}, 1, GRAY}, // 1 plataforma
                {357, 270, 2, 'b'}, //   x    y
                {389, 270, 2, 'b'}, // x=posicion-75 e y = posicion - 30
                {421, 273, 2, 'd'}, // espacio entre textura = 22
                {575, 120, 2, 'i'},
                {607, 120, 2, 'b'},
                {639, 120, 2, 'b'},
                {671, 123, 2, 'd'},
                {825, -30, 2, 'i'},
                {857, -30, 2, 'b'},
                {889, -30, 2, 'b'},
                {921, -27, 2, 'd'},
                {575, -180, 2, 'i'},
                {607, -180, 2, 'b'},
                {639, -180, 2, 'b'},
                {671, -177, 2, 'd'},
                {325, -330, 2, 'i'},
                {357, -330, 2, 'b'},
                {389, -330, 2, 'b'},
                {421, -327, 2, 'd'},
                {575, -480, 2, 'i'},
                {607, -480, 2, 'b'},
                {639, -480, 2, 'b'},
                {671, -477, 2, 'd'},
                {325, -630, 2, 'i'},
                {357, -630, 2, 'b'},
                {389, -630, 2, 'b'},
                {421, -630, 2, 'b'},
                {453, -630, 2, 'b'},
                {485, -630, 2, 'b'},
                {517, -630, 2, 'b'},
                {549, -630, 2, 'b'},
                {549, -630, 2, 'b'},
                {581, -630, 2, 'b'},
                {613, -630, 2, 'b'},
                {645, -630, 2, 'b'},
                {677, -630, 2, 'b'},
                {709, -630, 2, 'b'},
                {741, -627, 2, 'd'},
                {575, 120, 2, 'i'},
                {607, 120, 2, 'b'},
                {639, 120, 2, 'b'},
                {671, 123, 2, 'd'},

                {125, -780, 2, 'i'},
                {157, -780, 2, 'b'},
                {189, -780, 2, 'b'},
                {221, -777, 2, 'd'},
                {825, -780, 2, 'i'},
                {857, -780, 2, 'b'},
                {889, -780, 2, 'b'},
                {921, -777, 2, 'd'},
                {-125, -930, 2, 'i'},
                {-93, -930, 2, 'b'},
                {-61, -930, 2, 'b'},
                {-29, -927, 2, 'd'},
                {1075, -930, 2, 'i'},
                {1107, -930, 2, 'b'},
                {1139, -930, 2, 'b'},
                {1171, -927, 2, 'd'},
                {-375, -1080, 2, 'i'},
                {-343, -1080, 2, 'b'},
                {-311, -1080, 2, 'b'},
                {-279, -1077, 2, 'd'},
                {1225, -1080, 2, 'i'},
                {1257, -1080, 2, 'b'},
                {1289, -1080, 2, 'b'},
                {1321, -1077, 2, 'd'},
                {-625, -1230, 2, 'i'},
                {-593, -1230, 2, 'b'},
                {-561, -1230, 2, 'b'},
                {-529, -1227, 2, 'd'},
                {-375, -1380, 2, 'i'},
                {-343, -1380, 2, 'b'},
                {-311, -1380, 2, 'b'},
                {-279, -1377, 2, 'd'},
                {-625, -1530, 2, 'i'},
                {-593, -1530, 2, 'b'},
                {-561, -1530, 2, 'b'},
                {-529, -1527, 2, 'd'},

                {-875, -630, 2, 'i'},
                {-843, -630, 2, 'b'},
                {-811, -630, 2, 'b'},
                {-779, -630, 2, 'b'},
                {-747, -630, 2, 'b'},
                {-715, -630, 2, 'b'},
                {-683, -630, 2, 'b'},
                {-651, -630, 2, 'b'},
                {-619, -630, 2, 'b'},
                {-587, -630, 2, 'b'},
                {-555, -630, 2, 'b'},
                {-523, -630, 2, 'b'},
                {-491, -630, 2, 'b'},
                {-459, -630, 2, 'b'},
                {-427, -627, 2, 'd'},
            };

            int longitudObjetosEntorno = sizeof(objetosEntorno) / sizeof(objetosEntorno[0]);

            Camera2D camara = {0};
            camara.target = jugador.posicion;
            camara.offset = (Vector2){anchoPantalla / 2.0f, altoPantalla / 2.0f};
            camara.rotation = 0.0f;
            camara.zoom = 1.0f;

            SetTargetFPS(60);

            // Bucle principal del juego
            while (!WindowShouldClose())
            {
                // Actualizar
                float deltaTiempo = GetFrameTime();

                ActualizarJugador(&jugador, objetosEntorno, longitudObjetosEntorno, deltaTiempo);
                ActualizarCamaraCentro(&camara, &jugador, objetosEntorno, longitudObjetosEntorno, deltaTiempo, anchoPantalla, altoPantalla);

                // Dibujar
                BeginDrawing();

                ClearBackground(LIGHTGRAY);

                BeginMode2D(camara);

                for (int i = 0; i < longitudObjetosEntorno; i++)
                {
                    DrawRectangleRec(objetosEntorno[i].rect, objetosEntorno[i].color);
                }

                // Dibujar Preguntas
                DibujarPreguntas(font);
                // Dibujar todas las plataformas
                for (int i = 0; i < sizeof(platforms) / sizeof(Platform); i++)
                {
                    DrawPlatform(platforms[i].x, platforms[i].y, platforms[i].type, platforms[i].part,
                                 baseTexture, esquinaIzqTexture, esquinaDerTexture,
                                 centroBaseTexture, centroIzqTexture, centroDerTexture,
                                 sueloBaseTexture, sueloIzqTexture, sueloDerTexture,
                                 baseTexture2, esquinaIzqTexture2, esquinaDerTexture2,
                                 baseTexture3, baseTexture4, centroTexture, abajoTexture);
                }
                Rectangle rectJugador = {jugador.posicion.x - 20, jugador.posicion.y - 40, 40, 40};
                DrawRectangleRec(rectJugador, GREEN);

                EndMode2D();
                DrawText("Controles:", 20, 20, 10, BLACK);
                DrawText("- Derecha/Izquierda para moverse", 40, 40, 10, DARKGRAY);
                DrawText("- Espacio para saltar", 40, 60, 10, DARKGRAY);

                EndDrawing();
            }
            UnloadTexture(baseTexture);
            UnloadTexture(esquinaIzqTexture);
            UnloadTexture(esquinaDerTexture);
            UnloadTexture(centroBaseTexture);
            UnloadTexture(centroIzqTexture);
            UnloadTexture(centroDerTexture);
            UnloadTexture(sueloBaseTexture);
            UnloadTexture(sueloIzqTexture);
            UnloadTexture(sueloDerTexture);
            UnloadTexture(baseTexture2);
            UnloadTexture(esquinaIzqTexture2);
            UnloadTexture(esquinaDerTexture2);
            UnloadTexture(baseTexture3);
            UnloadTexture(baseTexture4);
            UnloadTexture(centroTexture);
            UnloadTexture(abajoTexture);
        }

        if (pantallaActual == NIVELNORMAL)
        {
            StopSound(soundmenu); // Detener sonido del menú al cambiar de pantalla
            DibujarNN(&pantallaActual, font, sound2);
        }
        if (pantallaActual == NIVELHARD)
        {
            StopSound(soundmenu); // Detener sonido del menú al cambiar de pantalla
            DibujarNH(&pantallaActual, font, sound2);
        }

        EndDrawing();
    }

    // Liberar recursos
    limpiarRecursos(texture, texture2, texture3, font, sound, sound2, soundmenu);

    return 0;
}

void DibujarMenu(PantallaJuego *pantallaActual, Font font, Sound sound2, Sound *soundmenu)
{
    // volumenG(font, &volumen);
    Vector2 mousePoint = GetMousePosition();
    Rectangle botonNIVELES = {400, 220, 200, 50};
    Rectangle botonSalir = {400, 300, 200, 50};

    if (CheckCollisionPointRec(mousePoint, botonNIVELES) && IsMouseButtonPressed(MOUSE_LEFT_BUTTON))
    {
        sonido2(&sound2);
        *pantallaActual = NIVELES; // Cambia al estado de juego
    }
    if (CheckCollisionPointRec(mousePoint, botonSalir) && IsMouseButtonPressed(MOUSE_LEFT_BUTTON))
    {
        sonido2(&sound2);
        *pantallaActual = SALIR; // Cambia al estado de salir
    }

    // Añadir la siguiente condición para reproducir el sonido del menú
    if (*pantallaActual == MENU)
    {
        sonidomenu(soundmenu);
    }

    int outlineThickness = 1;
    DrawTextEx(font, "         S H A D O W   D A S H", (Vector2){230, 100}, 35, 0, BLACK);

    // Dibujar botón "JUGAR"
    for (int i = -outlineThickness; i <= outlineThickness; i++)
    {
        for (int j = -outlineThickness; j <= outlineThickness; j++)
        {
            if (i != 0 || j != 0)
            {
                DrawRectangle(400 + i, 220 + j, 200 + i, 50 + j, BLACK);
            }
        }
    }
    DrawRectangle(400, 220, 200, 50, LIGHTGRAY);

    // Dibujar texto con contorno
    for (int i = -outlineThickness; i <= outlineThickness; i++)
    {
        for (int j = -outlineThickness; j <= outlineThickness; j++)
        {
            if (i != 0 || j != 0)
            {
                DrawTextEx(font, "J U G A R", (Vector2){455 + i, 235 + j}, 20, 0, BLACK);
            }
        }
    }
    DrawTextEx(font, "J U G A R", (Vector2){455, 235}, 20, 0, GRAY);

    // Dibujar botón "Salir"
    for (int i = -outlineThickness; i <= outlineThickness; i++)
    {
        for (int j = -outlineThickness; j <= outlineThickness; j++)
        {
            if (i != 0 || j != 0)
            {
                DrawRectangle(400 + i, 300 + j, 200 + i, 50 + j, BLACK);
            }
        }
    }
    DrawRectangle(400, 300, 200, 50, LIGHTGRAY);

    // Dibujar texto con contorno
    for (int i = -outlineThickness; i <= outlineThickness; i++)
    {
        for (int j = -outlineThickness; j <= outlineThickness; j++)
        {
            if (i != 0 || j != 0)
            {
                DrawTextEx(font, "S A L I R", (Vector2){455 + i, 318 + j}, 20, 0, BLACK);
            }
        }
    }
    // Dibujar botón "Salir"
    DrawTextEx(font, "S A L I R", (Vector2){455, 318}, 20, 0, GRAY);
}

void DibujarNiveles(PantallaJuego *pantallaActual, Font font, Sound sound2, Sound *soundmenu)
{
    // volumenG(font, &volumen);
    sonidomenu(soundmenu);
    DrawTextEx(font, "NIVEL 1", (Vector2){670, 70}, 30, 5, cafeOscuro);
    DrawTextEx(font, "  PROXIMAMENTE", (Vector2){570, 175}, 30, 5, cafeOscuro);
    DrawTextEx(font, "PROXIMAMENTE", (Vector2){590, 280}, 30, 5, cafeOscuroB);
    DrawTextEx(font, "REGRESAR", (Vector2){645, 375}, 30, 5, Rojos);

    Vector2 mousePosicion = GetMousePosition();
    Rectangle botonEASY = {700, 70, 100, 30};
    Rectangle botonNORMAL = {670, 175, 160, 30};
    Rectangle botonHARD = {690, 280, 110, 30};
    Rectangle botonREGRESAR = {645, 375, 225, 30};

    if (CheckCollisionPointRec(mousePosicion, botonEASY) && IsMouseButtonPressed(MOUSE_LEFT_BUTTON))
    {
        sonido2(&sound2);
        *pantallaActual = NIVELEASY; // Cambia al estado de juego
    }
    if (CheckCollisionPointRec(mousePosicion, botonNORMAL) && IsMouseButtonPressed(MOUSE_LEFT_BUTTON))
    {
        sonido2(&sound2);
        *pantallaActual = NIVELNORMAL; // Cambia al estado de juego
    }
    if (CheckCollisionPointRec(mousePosicion, botonHARD) && IsMouseButtonPressed(MOUSE_LEFT_BUTTON))
    {
        sonido2(&sound2);
        *pantallaActual = NIVELHARD; // Cambia al estado de juego
    }
    if (CheckCollisionPointRec(mousePosicion, botonREGRESAR) && IsMouseButtonPressed(MOUSE_LEFT_BUTTON))
    {
        sonido2(&sound2);
        *pantallaActual = MENU; // Cambia al estado de juego
    }
}

void DibujarNE(PantallaJuego *pantallaActual, Font font, Sound sound2)
{
    Vector2 mousePosicion = GetMousePosition();
    DrawTextEx(font, "REGRESAR", (Vector2){645, 375}, 30, 5, Rojos);
    Rectangle botonREGRESAR = {645, 375, 225, 30};
    if (CheckCollisionPointRec(mousePosicion, botonREGRESAR) && IsMouseButtonPressed(MOUSE_LEFT_BUTTON))
    {
        sonido2(&sound2);
        *pantallaActual = NIVELES; // Cambia al estado de juego
    }
}

void DibujarNN(PantallaJuego *pantallaActual, Font font, Sound sound2)
{
    Vector2 mousePosicion = GetMousePosition();
    DrawTextEx(font, "REGRESAR", (Vector2){645, 375}, 30, 5, Rojos);
    Rectangle botonREGRESAR = {645, 375, 225, 30};
    if (CheckCollisionPointRec(mousePosicion, botonREGRESAR) && IsMouseButtonPressed(MOUSE_LEFT_BUTTON))
    {
        sonido2(&sound2);
        *pantallaActual = NIVELES; // Cambia al estado de juego
    }
}

void DibujarNH(PantallaJuego *pantallaActual, Font font, Sound sound2)
{
    Vector2 mousePosicion = GetMousePosition();
    DrawTextEx(font, "REGRESAR", (Vector2){645, 375}, 30, 5, Rojos);
    Rectangle botonREGRESAR = {645, 375, 225, 30};
    if (CheckCollisionPointRec(mousePosicion, botonREGRESAR) && IsMouseButtonPressed(MOUSE_LEFT_BUTTON))
    {
        sonido2(&sound2);
        *pantallaActual = NIVELES; // Cambia al estado de juego
    }
}

void DibujarVolumen(Font font, Sound sound2, Sound soundmenu)
{
    Vector2 mousePosicion = GetMousePosition();

    // Botones para subir y bajar volumen
    Rectangle botonVS = {20, 15, 20, 20};
    Rectangle botonVB = {70, 15, 20, 20};
    DrawTextEx(font, "+", (Vector2){20, 15}, 40, 5, Rojos);
    DrawTextEx(font, "-", (Vector2){70, 15}, 40, 5, Rojos);

    if (CheckCollisionPointRec(mousePosicion, botonVS) && IsMouseButtonPressed(MOUSE_LEFT_BUTTON))
    {
        volumenActual += 0.1f; // Incrementar el volumen
        if (volumenActual > 1.0f)
        {
            volumenActual = 1.0f; // Asegurar que el volumen no supere el máximo
        }
        SetSoundVolume(sound2, volumenActual);    // Aplicar el nuevo volumen al sonido
        SetSoundVolume(soundmenu, volumenActual); // Ajusta el volumen del sonido del menú
    }

    if (CheckCollisionPointRec(mousePosicion, botonVB) && IsMouseButtonPressed(MOUSE_LEFT_BUTTON))
    {
        volumenActual -= 0.1f; // Decrementar el volumen
        if (volumenActual < 0.0f)
        {
            volumenActual = 0.0f; // Asegurar que el volumen no sea negativo
        }
        SetSoundVolume(sound2, volumenActual);    // Aplicar el nuevo volumen al sonido
        SetSoundVolume(soundmenu, volumenActual); // Ajusta el volumen del sonido del menú
    }

    // Dibujar el valor del volumen actual en la pantalla
    char volumenTexto[20];
    sprintf(volumenTexto, "Volumen: %.0f", volumenActual * 10);
    DrawTextEx(font, volumenTexto, (Vector2){0, 0}, 20, 2, BLACK);
}
/*void sonidoSalto(Sound *sonidoSalto)
{
    *soundSalto = LoadSound("salto.wav");
    PlaySound(*soundSalto);
}
*/
void sonido2(Sound *sound2)
{
    *sound2 = LoadSound("carga.wav");
    PlaySound(*sound2);
}

void sonidomenu(Sound *soundmenu)
{
    if (!IsSoundPlaying(*soundmenu))
    { // Verifica si el sonido del menú no se está reproduciendo actualmente
        PlaySound(*soundmenu);
    }
}
void DibujarPreguntas(Font font)
{
    // Dibujar Preguntas
    //.-1
    DrawText("  ¿Cuál es el plural de gato? ", 400, -575, 25, Rojos);
    DrawText(" Gatos", 200, -725, 25, Rojos);
    DrawText(" Gatas ", 900, -725, 25, Rojos);
    //.-2
    DrawText("  ¿Cuál es la tilde correcta para la palabra -camion- ?", -950, -1625, 25, Rojos);
    DrawText(" Camión", -1000, -1775, 25, Rojos);
    DrawText(" Camíon", -300, -1775, 25, Rojos);
    ///.-3
    DrawText("  ¿Cuál es el sinónimo de la palabra -bonito-?", -1600, -2675, 25, Rojos);
    DrawText(" Feo", -1000, -2825, 25, Rojos);
    DrawText(" Lindo", -1700, -2825, 25, Rojos);
    // Final
    DrawText("FELICIDADES!!! GANASTE!!!", -10, -4000, 50, Rojos);
}

void limpiarRecursos(Texture2D texture, Texture2D texture2, Texture2D texture3, Font font, Sound sound, Sound sound2, Sound soundmenu)
{
    UnloadSound(sound);
    UnloadSound(sound2);
    UnloadSound(soundmenu);
    UnloadTexture(texture);
    UnloadTexture(texture2);
    UnloadTexture(texture3);
    UnloadFont(font);
    CloseAudioDevice();
    CloseWindow();
}
