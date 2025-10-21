/*
Willkommen zum dritten Übungsblatt vom Programmierkurs.

Nachdem Sie in einem Terminal mittels des 'cd' Befehls in das Verzeichnis gewechselt sind, in dem diese Datei liegt,
können Sie mit folgendem Befehl ihre Lösungen überprüfen:
clang -std=c11 -g -Wall 03practice_test.c -o 03practice_test.o -lm && ./03practice_test.o

Auf diesem Blatt geht es unter anderem um:

- Funktionsaufrufe
- Die Canvas
*/

#include "03_canvas.h"
#include <stdio.h>

/*
Geben Sie '1' zurück falls 'x' gerade ist, und '0' falls 'x' ungerade ist.
*/
int is_even(int x)
{
    return x % 2 == 0;
}

/*
Geben Sie '1' zurück falls 'x' ungerade ist, und '0' falls 'x' gerade ist.
Die Ziffer '2' soll nicht direkt in Ihrer Lösung vorkommen. Nutzen Sie stattdessen 'is_even'.
*/
int is_odd(int x)
{
    return !is_even(x);
}

/*
Erstellen Sie folgende Zeichnung auf der Canvas:
(Jedes X symbolisiert einen schwarzen Pixel an den jeweiligen (x,y)-Koordinaten)

5---------
4-X-----X-
3---------
2-X-----X-
1--XXXXX--
0---------
/012345678

Nutzen Sie am besten eine Schleife für die Mundlinie.
*/
Canvas draw_smiley(Canvas c)
{
    canvas_set_black(c, 1, 4);
    canvas_set_black(c, 7, 4);

    canvas_set_black(c, 1, 2);
    canvas_set_black(c, 7, 2);

    for (int x = 2; x <= 6; x++)
    {
        canvas_set_black(c, x, 1);
    }
    return c;
}

/*
Zeichnen Sie ein klassisches Schachbrettmuster, startend bei (0,0) mit Schwarz
*/
Canvas draw_chessboard(Canvas c)
{
    for (int y = 0; y < canvas_height(c); y++)
    {
        for (int x = 0; x < canvas_width(c); x++)
        {
            if ((x + y) % 2 == 0)
            {
                canvas_set_black(c, x, y);
            }
        }
    }
    return c;
}

/*
Diese Funktion soll gefüllte Stufen zeichnen, welche von unten links anfangend nach rechts aufsteigen.
Jede Stufe soll eine Breite von `step_width` haben und eine Höhe von `step_height` (beide sind immer größer als null).
Für mehr Details schauen Sie einfach in das Test-Feedback für den ersten Testfall.
*/
Canvas i_told_you_about_stairs(Canvas c, int step_width, int step_height)
{
    int c_width = canvas_width(c);
    int c_height = canvas_height(c);

    for (int x = 0; x < c_width; x++)
    {
        // Bestimme, in welcher Stufe wir uns befinden
        int step = x / step_width;
        int max_y = (step + 1) * step_height;
        if (max_y > c_height)
            max_y = c_height;

        // Färbe alle Pixel unterhalb der aktuellen Stufe
        for (int y = 0; y < max_y; y++)
        {
            c = canvas_set_black(c, x, y);
        }
    }

    return c;
}