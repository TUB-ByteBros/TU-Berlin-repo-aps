/*
Willkommen zum fünften Übungsblatt vom Programmierkurs.

Nachdem Sie in einem Terminal mittels des `cd` Befehls in das Verzeichnis gewechselt sind, in dem diese Datei liegt,
können Sie mit folgendem Befehl ihre Lösungen überprüfen:
clang -std=c11 -g -Wall 05practice_test.c -o 05practice_test.o -lm && ./05practice_test.o

Auf diesem Blatt geht es um Rekursion.
*/

#include <stdio.h>
#include "05_canvas.h"

/*
Zeichne eine vertikale Linie der Höhe `height` mit unterstem Pixel an Position `(x, y)`.

Löse die Aufgabe ohne Schleifen zu verwenden.
*/
Canvas vertical_line(Canvas c, int x, int y, int height) {
    if (height <= 0) {
        return c;
    }
    // Prüfe, ob die Koordinate innerhalb der Canvas liegt
    if (y >= canvas_height(c)) {
        return c;
    }
    c = canvas_set_black(c, x, y);
    return vertical_line(c, x, y + 1, height - 1);
}

/*
Wie viele Dezimalstellen hat `n` (`n` ist nicht negativ)?

Löse die Aufgabe ohne Schleifen zu verwenden.
*/
int count_digits(int n) {
    if (n < 10) {
        return 1;
    }
    return 1 + count_digits(n / 10);
}

/*
Zeichne eine Pyramide: die unterste Zeile ist komplett schwarz, die zweitunterste Zeile lässt den ersten und letzten Pixel weiß, die drittunterste Zeile lässt die ersten zwei und die letzten zwei Pixel weiß, usw..

Löse die Aufgabe ohne Schleifen zu verwenden.
*/

// Hilfsfunktion: zeichnet eine horizontale Linie von x_start bis x_end (exklusive) auf Höhe y
Canvas draw_horizontal_line(Canvas c, int x_start, int x_end, int y) {
    if (x_start >= x_end) {
        return c;
    }
    c = canvas_set_black(c, x_start, y);
    return draw_horizontal_line(c, x_start + 1, x_end, y);
}

// Hilfsfunktion: zeichnet die Pyramide rekursiv, Zeile für Zeile
Canvas pyramid_helper(Canvas c, int y, int offset) {
    int width = canvas_width(c);
    int height = canvas_height(c);

    if (y >= height || offset >= width / 2) {
        return c;
    }

    // Zeichne die aktuelle Zeile von offset bis width-offset
    c = draw_horizontal_line(c, offset, width - offset, y);

    // Zeichne die nächste Zeile mit mehr Offset
    return pyramid_helper(c, y + 1, offset + 1);
}

Canvas pyramid(Canvas c) {
    return pyramid_helper(c, 0, 0);
}

/*
Zeichne ein Rechteck der Breite `width` und der Höhe `height` mit einem Schachbrettmuster. Der Pixel der linken unteren Ecke liegt bei `(x, y)` und ist schwarz.

Löse die Aufgabe ohne Schleifen zu verwenden.
*/

// Hilfsfunktion: zeichnet eine Zeile des Schachbretts
Canvas chessboard_row(Canvas c, int x, int y, int width, int start_black) {
    if (width <= 0) {
        return c;
    }

    if (start_black) {
        c = canvas_set_black(c, x, y);
    }

    return chessboard_row(c, x + 1, y, width - 1, !start_black);
}

// Hilfsfunktion: zeichnet das Schachbrett Zeile für Zeile
Canvas chessboard_helper(Canvas c, int x, int y, int width, int height, int start_black) {
    if (height <= 0) {
        return c;
    }

    c = chessboard_row(c, x, y, width, start_black);
    return chessboard_helper(c, x, y + 1, width, height - 1, !start_black);
}

Canvas chessboard_rectangle(Canvas c, int x, int y, int width, int height) {
    return chessboard_helper(c, x, y, width, height, 1);
}

/*
Der Binomialkoeffizient von `n` und `k` ("n über k"), mit `0 <= k <= n` ist wie folgt definiert:

- bin(n, 0) = 1, sonst
- bin(n, n) = 1, sonst
- bin(n, k) = bin(n - 1, k - 1) + bin(n - 1, k)

Berechne `bin(n, k)`.
*/
int binomial_coefficient(int n, int k) {
    if (k == 0) {
        return 1;
    }
    if (k == n) {
        return 1;
    }
    return binomial_coefficient(n - 1, k - 1) + binomial_coefficient(n - 1, k);
}

/*
Aufgabe 2:
Der *Sierpinski Carpet der Ordnung 0* ist ein einzelnes schwarzes Pixel.
Der *Sierpinski Carpet der Ordnung n+1* besteht aus acht Sierpinski Carpets der Ordnung n, angeordnet als drei-mal-drei
Quadrat dessen Mittelstück fehlt.

Beispiele (`X` stellt schwarze Pixel dar)
=========================================

Ordnung 0:

X

Ordnung 1:

XXX
X X
XXX

Ordnung 2:

XXXXXXXXX
X XX XX X
XXXXXXXXX
XXX   XXX
X X   X X
XXX   XXX
XXXXXXXXX
X XX XX X
XXXXXXXXX

Siehe auch die Datei `05sierpinski.jpg`

Um in der nächsten Aufgabe den Sierpinski-Carpet auf die Canvas zeichnen zu können müssen Potenzen berechnet werden.
Implementieren Sie die Berechnung der Potenz einer nicht-negativen, ganzzahligen Basis `b` mit einem
nicht-negativen, ganzzahligen Exponenten `exp`.

_Benutzen Sie keine Schleifen, die Aufgabe soll über Rekursion gelöst werden!_
*/
int power(int b, int exp){
    if (exp == 0) {
        return 1;
    }
    return b * power(b, exp - 1);
}

/*
Diese Funktion soll den Sierpinski Carpet der Ordnung `n` auf die Canvas zeichnen, mit unterer linker Ecke an Koordinate `(x, y)`.

_Benutzen Sie keine Schleifen, die Aufgabe soll über Rekursion gelöst werden!_
*/
Canvas sierpinski_carpet(Canvas c, int n, int x, int y){
    if (n == 0) {
        return canvas_set_black(c, x, y);
    }

    int size = power(3, n - 1);

    // Zeichne 8 Sierpinski Carpets in einem 3x3 Gitter, ohne die Mitte
    // Untere Reihe: links, mitte, rechts
    c = sierpinski_carpet(c, n - 1, x, y);
    c = sierpinski_carpet(c, n - 1, x + size, y);
    c = sierpinski_carpet(c, n - 1, x + 2 * size, y);

    // Mittlere Reihe: links, mitte LEER, rechts
    c = sierpinski_carpet(c, n - 1, x, y + size);
    // Mitte leer: x + size, y + size wird nicht gezeichnet
    c = sierpinski_carpet(c, n - 1, x + 2 * size, y + size);

    // Obere Reihe: links, mitte, rechts
    c = sierpinski_carpet(c, n - 1, x, y + 2 * size);
    c = sierpinski_carpet(c, n - 1, x + size, y + 2 * size);
    c = sierpinski_carpet(c, n - 1, x + 2 * size, y + 2 * size);

    return c;
}

/*
Hinweis: Diese Aufgabe ist deutlich schwieriger als die vorangegangen, und ist als besondere Herausforderung gedacht :)
Eine *knifflige* Zahl ist eine Zahl deren einzige Dezimalziffern die Vier und die Sieben sind, und in der nie zwei
Siebenen aufeinander folgen.
Berechne die Anzahl der kniffligen Zahlen mit genau `n` Dezimalziffern.

Beispiel: die kniffligen Zahlen mit drei Dezimalziffern sind 444, 447, 474, 744, 747.
*/

// Hilfsfunktion: zählt knifflige Zahlen mit `remaining` Stellen
// last_was_seven: 1 wenn die letzte Ziffer eine 7 war, sonst 0
int tricky_helper(int remaining, int last_was_seven) {
    if (remaining == 0) {
        return 1;
    }

    if (last_was_seven) {
        // Nach einer 7 kann nur eine 4 kommen
        return tricky_helper(remaining - 1, 0);
    } else {
        // Nach einer 4 (oder am Anfang) können wir 4 oder 7 anhängen
        return tricky_helper(remaining - 1, 0) + tricky_helper(remaining - 1, 1);
    }
}

int tricky_numbers(int n) {
    if (n == 0) {
        return 1;
    }

    // Starte mit 4 oder 7 als erste Ziffer
    // Mit 4 starten (last_was_seven = 0)
    int start_with_4 = tricky_helper(n - 1, 0);
    // Mit 7 starten (last_was_seven = 1)
    int start_with_7 = tricky_helper(n - 1, 1);

    return start_with_4 + start_with_7;
}
