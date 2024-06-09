<<<<<<< HEAD
#ifndef PLATAFORMAS_H
#define PLATAFORMAS_H

#include "raylib.h"

// Estructura para representar una plataforma
typedef struct
{
    float x;   // Posición x
    float y;   // Posición y
    int type;  // Tipo de plataforma (1 = plataforma de suelo, 2 = plataforma horizontal, 3 = plataforma sola, 4 = plataforma vertical)
    char part; // Parte de la plataforma ('b' = base, 'i' = esquina izquierda, 'd' = esquina derecha, 'c' = centro, 'l' = centro izquierda, 'r' = centro derecha, 's' = suelo base, 'h' = suelo izquierda, 'm' = suelo derecha)
} Platform;

// Función para dibujar una plataforma
void DrawPlatform(float posX, float posY, int platformType, char platformPart,
                  Texture2D baseTexture, Texture2D esquinaIzqTexture, Texture2D esquinaDerTexture,
                  Texture2D centroBaseTexture, Texture2D centroIzqTexture, Texture2D centroDerTexture,
                  Texture2D sueloBaseTexture, Texture2D sueloIzqTexture, Texture2D sueloDerTexture,
                  Texture2D baseTexture2, Texture2D esquinaIzqTexture2, Texture2D esquinaDerTexture2,
                  Texture2D baseTexture3, Texture2D baseTexture4, Texture2D centroTexture, Texture2D abajoTexture)
{
    Rectangle destRect = {posX, posY, 0, 0}; // Rectángulo destino (posición x, posición y, ancho, alto)
    Texture2D texture;                       // Textura a dibujar
    float scale = 1.0f;                      // Escala para aumentar el tamaño de la textura

    // Seleccionar la textura correspondiente según el tipo de plataforma y la parte deseada
    switch (platformType)
    {
    case 1:
        // Plataforma de suelo
        switch (platformPart)
        {
        case 'b':
            texture = baseTexture;
            break;
        case 'i':
            texture = esquinaIzqTexture;
            break;
        case 'd':
            texture = esquinaDerTexture;
            break;
        case 'c':
            texture = centroBaseTexture;
            break;
        case 'l':
            texture = centroIzqTexture;
            break;
        case 'r':
            texture = centroDerTexture;
            break;
        case 's':
            texture = sueloBaseTexture;
            break;
        case 'h':
            texture = sueloIzqTexture;
            break;
        case 'm':
            texture = sueloDerTexture;
            break;
        default:
            // Parte de plataforma no reconocida
            return;
        }
        break;
    case 2:
        // Plataforma horizontal
        switch (platformPart)
        {
        case 'b':
            texture = baseTexture2;
            break;
        case 'i':
            texture = esquinaIzqTexture2;
            break;
        case 'd':
            texture = esquinaDerTexture2;
            break;
        default:
            // Parte de plataforma no reconocida
            return;
        }
        break;
    case 3:
        // Plataforma sola
        texture = baseTexture3;
        break;
    case 4:
        // Plataforma vertical
        switch (platformPart)
        {
        case 'b':
            texture = baseTexture4;
            break;
        case 'c':
            texture = centroTexture;
            break;
        case 'a':
            texture = abajoTexture;
            break;
        default:
            // Parte de plataforma no reconocida
            return;
        }
        break;
    default:
        // Tipo de plataforma no reconocido
        return;
    }

    // Dibujar la plataforma
    DrawTextureEx(texture, (Vector2){destRect.x, destRect.y}, 0.0f, scale, WHITE);
}

// Función para invertir la base de una plataforma vertical
void InvertVerticalPlatformBase(float posX, float posY, Texture2D baseTexture4)
{
    float scale = 1.5f; // Escala para aumentar el tamaño de la textura
    // Dibujar la plataforma invertida
    DrawTextureEx(baseTexture4, (Vector2){posX, posY}, 180.0f, scale, WHITE);
}

#endif // PLATAFORMAS_H
=======
#ifndef PLATAFORMAS_H
#define PLATAFORMAS_H

#include "raylib.h"

// Estructura para representar una plataforma
typedef struct
{
    float x;   // Posición x
    float y;   // Posición y
    int type;  // Tipo de plataforma (1 = plataforma de suelo, 2 = plataforma horizontal, 3 = plataforma sola, 4 = plataforma vertical)
    char part; // Parte de la plataforma ('b' = base, 'i' = esquina izquierda, 'd' = esquina derecha, 'c' = centro, 'l' = centro izquierda, 'r' = centro derecha, 's' = suelo base, 'h' = suelo izquierda, 'm' = suelo derecha)
} Platform;

// Función para dibujar una plataforma
void DrawPlatform(float posX, float posY, int platformType, char platformPart,
                  Texture2D baseTexture, Texture2D esquinaIzqTexture, Texture2D esquinaDerTexture,
                  Texture2D centroBaseTexture, Texture2D centroIzqTexture, Texture2D centroDerTexture,
                  Texture2D sueloBaseTexture, Texture2D sueloIzqTexture, Texture2D sueloDerTexture,
                  Texture2D baseTexture2, Texture2D esquinaIzqTexture2, Texture2D esquinaDerTexture2,
                  Texture2D baseTexture3, Texture2D baseTexture4, Texture2D centroTexture, Texture2D abajoTexture)
{
    Rectangle destRect = {posX, posY, 0, 0}; // Rectángulo destino (posición x, posición y, ancho, alto)
    Texture2D texture;                       // Textura a dibujar
    float scale = 1.0f;                      // Escala para aumentar el tamaño de la textura

    // Seleccionar la textura correspondiente según el tipo de plataforma y la parte deseada
    switch (platformType)
    {
    case 1:
        // Plataforma de suelo
        switch (platformPart)
        {
        case 'b':
            texture = baseTexture;
            break;
        case 'i':
            texture = esquinaIzqTexture;
            break;
        case 'd':
            texture = esquinaDerTexture;
            break;
        case 'c':
            texture = centroBaseTexture;
            break;
        case 'l':
            texture = centroIzqTexture;
            break;
        case 'r':
            texture = centroDerTexture;
            break;
        case 's':
            texture = sueloBaseTexture;
            break;
        case 'h':
            texture = sueloIzqTexture;
            break;
        case 'm':
            texture = sueloDerTexture;
            break;
        default:
            // Parte de plataforma no reconocida
            return;
        }
        break;
    case 2:
        // Plataforma horizontal
        switch (platformPart)
        {
        case 'b':
            texture = baseTexture2;
            break;
        case 'i':
            texture = esquinaIzqTexture2;
            break;
        case 'd':
            texture = esquinaDerTexture2;
            break;
        default:
            // Parte de plataforma no reconocida
            return;
        }
        break;
    case 3:
        // Plataforma sola
        texture = baseTexture3;
        break;
    case 4:
        // Plataforma vertical
        switch (platformPart)
        {
        case 'b':
            texture = baseTexture4;
            break;
        case 'c':
            texture = centroTexture;
            break;
        case 'a':
            texture = abajoTexture;
            break;
        default:
            // Parte de plataforma no reconocida
            return;
        }
        break;
    default:
        // Tipo de plataforma no reconocido
        return;
    }

    // Dibujar la plataforma
    DrawTextureEx(texture, (Vector2){destRect.x, destRect.y}, 0.0f, scale, WHITE);
}

// Función para invertir la base de una plataforma vertical
void InvertVerticalPlatformBase(float posX, float posY, Texture2D baseTexture4)
{
    float scale = 1.5f; // Escala para aumentar el tamaño de la textura
    // Dibujar la plataforma invertida
    DrawTextureEx(baseTexture4, (Vector2){posX, posY}, 180.0f, scale, WHITE);
}

#endif // PLATAFORMAS_H
>>>>>>> 1d05b59d84fd9d4872e34505c137df75a89d1f72
