#include "raylib.h"
#include <cstdlib> // Para malloc y free
#include <cstddef> // Para NULL

// Constantes definidas
#define LONGITUD_SNAKE   256
#define TAMANO_CUADRADO     31
#define FRAMES_PARA_MOVER 10

// Estructuras
typedef struct {
    Vector2 posicion;
    Vector2 tamaño;
    Vector2 velocidad;
    Color color;
} Serpiente;

typedef struct {
    Vector2 posicion;
    Vector2 tamaño;
    bool activo;
    Color color;
} Comida;

// Declaración de funciones
static void InicializarJuego(void);
static void ActualizarJuego(void);
static void DibujarJuego(void);
static void LiberarJuego(void);
static void ActualizarDibujarFrame(void);

// Variables principales
static const int anchoPantalla = 800;
static const int altoPantalla = 450;

// Variables de estado del juego
static int contadorFrames = 0;
static bool juegoTerminado = false;
static bool pausa = false;

// Entidades del juego
static Comida *fruta = NULL;
static Serpiente serpiente[LONGITUD_SNAKE];
static Vector2 *posicionSerpiente = NULL;
static bool permitirMovimiento = false;
static Vector2 desplazamiento = { 0 };
static int contadorCola = 0;

int main(void)
{
    // Inicialización
    InitWindow(anchoPantalla, altoPantalla, "Juego clásico: Serpiente");
    InicializarJuego();
    SetTargetFPS(60);

    // Bucle principal del juego
    while (!WindowShouldClose())
    {
        ActualizarDibujarFrame();
    }

    // Desinicialización
    LiberarJuego();
    CloseWindow();
    return 0;
}

// Inicializar variables del juego
static void InicializarJuego(void)
{
    contadorFrames = 0;
    juegoTerminado = false;
    pausa = false;

    contadorCola = 1;
    permitirMovimiento = false;

    desplazamiento.x = anchoPantalla % TAMANO_CUADRADO;
    desplazamiento.y = altoPantalla % TAMANO_CUADRADO;

    // Uso de memoria dinámica
    posicionSerpiente = (Vector2 *)malloc(LONGITUD_SNAKE * sizeof(Vector2));
    fruta = (Comida *)malloc(sizeof(Comida));

    for (int i = 0; i < LONGITUD_SNAKE; i++)
    {
        serpiente[i].posicion = (Vector2){desplazamiento.x / 2, desplazamiento.y / 2};
        serpiente[i].tamaño = (Vector2){TAMANO_CUADRADO, TAMANO_CUADRADO};
        serpiente[i].velocidad = (Vector2){TAMANO_CUADRADO, 0};

        if (i == 0)
            serpiente[i].color = YELLOW;
        else
            serpiente[i].color = (Color){(unsigned char)GetRandomValue(0, 255), (unsigned char)GetRandomValue(0, 255), (unsigned char)GetRandomValue(0, 255), 255};
    }

    fruta->tamaño = (Vector2){TAMANO_CUADRADO, TAMANO_CUADRADO};
    fruta->color = RED;
    fruta->activo = false;
}

// Actualizar juego (un frame)
static void ActualizarJuego(void)
{
    if (!juegoTerminado)
    {
        if (IsKeyPressed('P'))
            pausa = !pausa;

        if (!pausa)
        {
            // Control del jugador
            if (IsKeyPressed(KEY_RIGHT) && (serpiente[0].velocidad.x == 0) && permitirMovimiento)
            {
                serpiente[0].velocidad = (Vector2){TAMANO_CUADRADO, 0};
                permitirMovimiento = false;
            }
            if (IsKeyPressed(KEY_LEFT) && (serpiente[0].velocidad.x == 0) && permitirMovimiento)
            {
                serpiente[0].velocidad = (Vector2){-TAMANO_CUADRADO, 0};
                permitirMovimiento = false;
            }
            if (IsKeyPressed(KEY_UP) && (serpiente[0].velocidad.y == 0) && permitirMovimiento)
            {
                serpiente[0].velocidad = (Vector2){0, -TAMANO_CUADRADO};
                permitirMovimiento = false;
            }
            if (IsKeyPressed(KEY_DOWN) && (serpiente[0].velocidad.y == 0) && permitirMovimiento)
            {
                serpiente[0].velocidad = (Vector2){0, TAMANO_CUADRADO};
                permitirMovimiento = false;
            }

            // Movimiento de la serpiente
            for (int i = 0; i < contadorCola; i++)
                posicionSerpiente[i] = serpiente[i].posicion;

            if ((contadorFrames % FRAMES_PARA_MOVER) == 0)
            {
                for (int i = 0; i < contadorCola; i++)
                {
                    if (i == 0)
                    {
                        serpiente[0].posicion.x += serpiente[0].velocidad.x;
                        serpiente[0].posicion.y += serpiente[0].velocidad.y;
                        permitirMovimiento = true;
                    }
                    else
                        serpiente[i].posicion = posicionSerpiente[i - 1];
                }
            }

            // Comportamiento de la pared
            if (((serpiente[0].posicion.x) > (anchoPantalla - desplazamiento.x)) ||
                ((serpiente[0].posicion.y) > (altoPantalla - desplazamiento.y)) ||
                (serpiente[0].posicion.x < 0) || (serpiente[0].posicion.y < 0))
            {
                juegoTerminado = true;
            }

            // Colisión con uno mismo
            for (int i = 1; i < contadorCola; i++)
            {
                if ((serpiente[0].posicion.x == serpiente[i].posicion.x) && (serpiente[0].posicion.y == serpiente[i].posicion.y))
                    juegoTerminado = true;
            }

            // Cálculo de la posición de la fruta
            if (!fruta->activo)
            {
                fruta->activo = true;
                fruta->posicion = (Vector2){GetRandomValue(0, (anchoPantalla / TAMANO_CUADRADO) - 1) * TAMANO_CUADRADO + desplazamiento.x / 2, GetRandomValue(0, (altoPantalla / TAMANO_CUADRADO) - 1) * TAMANO_CUADRADO + desplazamiento.y / 2};

                for (int i = 0; i < contadorCola; i++)
                {
                    while ((fruta->posicion.x == serpiente[i].posicion.x) && (fruta->posicion.y == serpiente[i].posicion.y))
                    {
                        fruta->posicion = (Vector2){GetRandomValue(0, (anchoPantalla / TAMANO_CUADRADO) - 1) * TAMANO_CUADRADO + desplazamiento.x / 2, GetRandomValue(0, (altoPantalla / TAMANO_CUADRADO) - 1) * TAMANO_CUADRADO + desplazamiento.y / 2};
                        i = 0;
                    }
                }
            }

            // Colisión
            if ((serpiente[0].posicion.x < (fruta->posicion.x + fruta->tamaño.x) && (serpiente[0].posicion.x + serpiente[0].tamaño.x) > fruta->posicion.x) &&
                (serpiente[0].posicion.y < (fruta->posicion.y + fruta->tamaño.y) && (serpiente[0].posicion.y + serpiente[0].tamaño.y) > fruta->posicion.y))
            {
                serpiente[contadorCola].posicion = posicionSerpiente[contadorCola - 1];
                contadorCola += 1;
                fruta->activo = false;
            }

            contadorFrames++;
        }
    }
    else
    {
        if (IsKeyPressed(KEY_ENTER))
        {
            InicializarJuego();
            juegoTerminado = false;
        }
    }
}

// Dibujar juego (un frame)
static void DibujarJuego(void)
{
    BeginDrawing();
    ClearBackground(RAYWHITE);

    if (!juegoTerminado)
    {
        // Dibujar líneas de la cuadrícula
        for (int i = 0; i < anchoPantalla / TAMANO_CUADRADO + 1; i++)
        {
            DrawLineV((Vector2){TAMANO_CUADRADO * i + desplazamiento.x / 2, desplazamiento.y / 2}, (Vector2){TAMANO_CUADRADO * i + desplazamiento.x / 2, altoPantalla - desplazamiento.y / 2}, LIGHTGRAY);
        }

        for (int i = 0; i < altoPantalla / TAMANO_CUADRADO + 1; i++)
        {
            DrawLineV((Vector2){desplazamiento.x / 2, TAMANO_CUADRADO * i + desplazamiento.y / 2}, (Vector2){anchoPantalla - desplazamiento.x / 2, TAMANO_CUADRADO * i + desplazamiento.y / 2}, LIGHTGRAY);
        }

        // Dibujar serpiente
        for (int i = 0; i < contadorCola; i++) {
            if (i == 0) {
                DrawRectangleV(serpiente[i].posicion, serpiente[i].tamaño, serpiente[i].color);
                DrawCircleV((Vector2){serpiente[i].posicion.x + TAMANO_CUADRADO / 4, serpiente[i].posicion.y + TAMANO_CUADRADO / 4}, TAMANO_CUADRADO / 4, BLACK); // ojo izquierdo
                DrawCircleV((Vector2){serpiente[i].posicion.x + TAMANO_CUADRADO * 3 / 4, serpiente[i].posicion.y + TAMANO_CUADRADO / 4}, TAMANO_CUADRADO / 4, BLACK); // ojo derecho
                DrawCircleV((Vector2){serpiente[i].posicion.x + TAMANO_CUADRADO / 2, serpiente[i].posicion.y + TAMANO_CUADRADO * 3 / 4}, TAMANO_CUADRADO / 4, RED); // boca
            } else {
                DrawRectangleV(serpiente[i].posicion, serpiente[i].tamaño, serpiente[i].color);
            }
        }

        // Dibujar fruta para recoger
        DrawRectangleV(fruta->posicion, fruta->tamaño, fruta->color);

        if (pausa)
            DrawText("JUEGO EN PAUSA", anchoPantalla / 2 - MeasureText("JUEGO EN PAUSA", 40) / 2, altoPantalla / 2 - 40, 40, GRAY);
    }
    else
        DrawText("PRESIONA [ENTER] PARA JUGAR DE NUEVO", anchoPantalla / 2 - MeasureText("PRESIONA [ENTER] PARA JUGAR DE NUEVO", 20) / 2, altoPantalla / 2 - 50, 20, GRAY);

    EndDrawing();
}

// Liberar variables del juego
static void LiberarJuego(void)
{
    free(fruta);
    free(posicionSerpiente);
}

// Actualizar y Dibujar (un frame)
static void ActualizarDibujarFrame(void)
{
    ActualizarJuego();
    DibujarJuego();
}
