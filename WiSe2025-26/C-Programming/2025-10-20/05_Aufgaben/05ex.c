/*
Willkommen zum fünften Aufgabenblatt vom Programmierkurs. Auf diesem Aufabenblatt geht es um Rekursion.

Um die Tests für dieses Blatt zu kompilieren und zu starten, führen Sie den folgenden Befehl aus:
clang -std=c11 -g -Wall 05ex_test.c -o 05ex_test.o -lm && ./05ex_test.o
*/

#include "05_canvas.h"
#include <stdio.h>
#include <math.h>

/*
Aufgabe 1a:
Zeichnen Sie eine horizontale Linie der Länge `width`, deren am weitesten links liegender Pixel bei `(x, y)` ist.
Wenn Teile der Linie außerhalb der Canvas liegen, dann sollen diese Teile ignoriert werden. Alles was in die Canvas passt, muss aber gezeichnet werden.

_Benutzen Sie keine Schleifen - Die Aufgabe soll über Rekursion gelöst werden!_

*/
Canvas recursive_line(Canvas c, int x, int y, int width) {
    // Basisfall: Keine Pixel mehr zu zeichnen
    if (width <= 0) {
        return c;
    }

    // Zeichne aktuellen Pixel, falls er innerhalb der Canvas liegt
    if (x >= 0 && x < canvas_width(c) && y >= 0 && y < canvas_height(c)) {
        c = canvas_set_black(c, x, y);
    }

    // Rekursiver Aufruf für den nächsten Pixel
    return recursive_line(c, x + 1, y, width - 1);
}

/*
Aufgabe 1b:
Zeichnen Sie ein Rechteck mit der Breite `width` und der Höhe `height`. Der Pixel der linken unteren Ecke liegt bei `(x, y)`.
Wenn Teile des Rechtecks außerhalb der Canvas liegen, dann sollen diese Teile ignoriert werden. Alles was in die Canvas passt, muss aber gezeichnet werden.

_Benutzen Sie keine Schleifen, die Aufgabe soll über Rekursion gelöst werden!_
*/
Canvas recursive_rectangle(Canvas c, int x, int y, int width, int height) {
    // Basisfall: Keine Zeilen mehr zu zeichnen
    if (height <= 0) {
        return c;
    }

    // Zeichne eine horizontale Linie auf der aktuellen Höhe
    c = recursive_line(c, x, y, width);

    // Rekursiver Aufruf für die nächste Zeile (eine Zeile höher)
    return recursive_rectangle(c, x, y + 1, width, height - 1);
}

/*
Aufgabe 2:
Die Fibonaccizahlen sind wie folgt definiert:

- die nullte Fibonaccizahl ist 1,
- die erste Fibonaccizahl ist ebenfalls 1, und
- jede weitere Fibonaccizahl ist die Summe der zwei vorigen Fibonaccizahlen.

Berechne die `n`-te Fibonaccizahl.
*/
int fibonacci(int n) {
    // Basisfälle: F(0) = 1 und F(1) = 1
    if (n == 0 || n == 1) {
        return 1;
    }

    // Rekursiver Fall: F(n) = F(n-1) + F(n-2)
    return fibonacci(n - 1) + fibonacci(n - 2);
}

/*
Aufgabe 3:
Implementieren Sie einen schwarzen Fülleimer. Gegeben eine Koordinate `(x, y)` auf einer (bereits bemalten) Canvas, soll die komplette
zusammenhängende Fläche aller Pixel der selben Farbe (schwarz oder weiß) schwarz gefärbt werden.
Zwei Pixel sind Teil der selben Fläche wenn sie die selbe Farbe haben und direkt benachbart sind. Jeder Pixel hat bis
zu vier direkte Nachbarn - die Diagonalen zählen nicht.

Funktionen, um die Farbe eines Pixels auf der Canvas zu bestimmen, sind im Headerfile der Canvas dokumentiert.
*/
Canvas bucket_fill(Canvas c, int x, int y) {
    // Basisfall: Koordinaten außerhalb der Canvas
    if (x < 0 || x >= canvas_width(c) || y < 0 || y >= canvas_height(c)) {
        return c;
    }

    // Merke die ursprüngliche Farbe an dieser Position
    int original_is_black = pixel_is_black(c, x, y);
    int original_is_white = pixel_is_white(c, x, y);

    // Basisfall: Pixel ist bereits schwarz (bereits besucht)
    if (original_is_black) {
        return c;
    }

    // Färbe aktuellen Pixel schwarz
    c = canvas_set_black(c, x, y);

    // Rekursiv die 4 Nachbarn füllen, wenn sie die gleiche Originalfarbe haben
    // Prüfe, ob Nachbar existiert und die Originalfarbe hat

    // Rechts
    if (x + 1 < canvas_width(c)) {
        if (original_is_white && pixel_is_white(c, x + 1, y)) {
            c = bucket_fill(c, x + 1, y);
        }
    }

    // Links
    if (x - 1 >= 0) {
        if (original_is_white && pixel_is_white(c, x - 1, y)) {
            c = bucket_fill(c, x - 1, y);
        }
    }

    // Oben
    if (y + 1 < canvas_height(c)) {
        if (original_is_white && pixel_is_white(c, x, y + 1)) {
            c = bucket_fill(c, x, y + 1);
        }
    }

    // Unten
    if (y - 1 >= 0) {
        if (original_is_white && pixel_is_white(c, x, y - 1)) {
            c = bucket_fill(c, x, y - 1);
        }
    }

    return c;
}
