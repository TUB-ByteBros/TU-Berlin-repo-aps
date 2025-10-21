/*
Willkommen zum sechsten Übungsblatt vom Programmierkurs.

Nachdem Sie in einem Terminal mittels des 'cd' Befehls in das Verzeichnis gewechselt sind, in dem diese Datei liegt,
können Sie mit folgendem Befehl ihre Lösungen überprüfen:
clang -std=c11 -g -Wall 06practice_test.c -o 06practice_test.o -lm && ./06practice_test.o

Auf diesem Blatt geht es um Typen.
*/

#ifndef M_PI
#define M_PI (3.14159265358979323846264338327950288)
#endif

#include "06_canvas.h"
#include <stdio.h>
#include <stdint.h>
#include <math.h>


typedef struct RGB_ {
    float r;
    float g;
    float b;
} RGB;

/*
Färben Sie alle Pixel, deren x-Koordinate kleiner gleich ihrer y-Koordinate sind mit der Farbe 'color1', und alle anderen
Koordinaten mit der Farbe 'color2'.
*/
Canvas right_triangle(Canvas c, RGB color1, RGB color2) {
  for (int y = 0; y < canvas_height(c); y++) {
        for (int x = 0; x < canvas_width(c); x++) {
            if (x <= y) {
                canvas_set_r(c, x, y, color1.r);
                canvas_set_g(c, x, y, color1.g);
                canvas_set_b(c, x, y, color1.b);
            } else {
                canvas_set_r(c, x, y, color2.r);
                canvas_set_g(c, x, y, color2.g);
                canvas_set_b(c, x, y, color2.b);
            }
        }
    }
  return c;
}

/*
Mischen Sie 'color1' und 'color2', indem Sie jeden Farbkanal auf den Mittelpunkt zwischen den Werten der entsprechenden
Farbkanäle von 'color1' und 'color2' setzen.
*/
RGB mix_colors(RGB color1, RGB color2) {
    RGB result;
    result.r = (color1.r + color2.r) / 2.0f;
    result.g = (color1.g + color2.g) / 2.0f;
    result.b = (color1.b + color2.b) / 2.0f;
    return result;
}

/*
Färben Sie alle Pixel wie in der 'right_triangle'-Übung, aber benutzen Sie die Mischung zwischen 'color1' und 'color2' für
die Pixel der direkt aneinander grenzenden Kanten der entstehenden Dreiecke.
*/
Canvas antialiased_right_triangle(Canvas c, RGB color1, RGB color2) {
    // Berechne die Mischfarbe
    RGB mixed;
    mixed.r = (color1.r + color2.r) / 2.0f;
    mixed.g = (color1.g + color2.g) / 2.0f;
    mixed.b = (color1.b + color2.b) / 2.0f;

    // Färbe alle Pixel
    for (int y = 0; y < canvas_height(c); y++) {
        for (int x = 0; x < canvas_width(c); x++) {
            if (x == y) {
                // Diagonale: Mischfarbe
                c = canvas_set_r(c, x, y, mixed.r);
                c = canvas_set_g(c, x, y, mixed.g);
                c = canvas_set_b(c, x, y, mixed.b);
            } else if (x < y) {
                // x < y: color1
                c = canvas_set_r(c, x, y, color1.r);
                c = canvas_set_g(c, x, y, color1.g);
                c = canvas_set_b(c, x, y, color1.b);
            } else {
                // x > y: color2
                c = canvas_set_r(c, x, y, color2.r);
                c = canvas_set_g(c, x, y, color2.g);
                c = canvas_set_b(c, x, y, color2.b);
            }
        }
    }
    return c;
}

/*
Berechnen Sie das 627-fache von 'n', aber geben Sie '-1' zurück, falls 'n' negativ ist, oder falls die Lösung nicht
in einem 'int16_t' dargestellt werden kann.
*/
int16_t times627(int16_t n) {
    if (n < 0) return -1;
    int32_t result = (int32_t)n * 627;
    if (result < INT16_MIN || result > INT16_MAX) return -1;
    return (int16_t)result;
}

/*
Berechnen Sie den Winkel (in Grad) zwischen der Linie von Punkt (0, 0) nach Punkt (x, y) und der Linie von Punkt
(0, 0) nach Punkt (1, 0), also der X-Achse.

Hinweis: Wir haben weder beigebracht wie die Mathematik dafür funktioniert, noch wie die benötigten Funktionen
im <math.h> Header lauten. Beides lässt sich im Web suchen oder mit KomillitonInnen besprechen.
Das ist explizit gewünscht, nur abzuschreiben ohne selber nachzudenken wäre schade.
*/
float compute_angle(float x, float y) {
    float angle_radians = atan2f(y, x);
    float a = angle_radians * (180.0f / M_PI);
    return a;
}