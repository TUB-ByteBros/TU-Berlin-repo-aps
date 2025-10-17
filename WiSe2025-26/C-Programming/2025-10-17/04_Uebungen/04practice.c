/*
Willkommen zum vierten Übungsblatt vom Programmierkurs.

Nachdem Sie in einem Terminal mittels des 'cd' Befehls in das Verzeichnis gewechselt sind, in dem diese Datei liegt,
können Sie mit folgendem Befehl ihre Lösungen überprüfen:
clang -std=c11 -g -Wall 04practice_test.c -o 04practice_test.o -lm && ./04practice_test.o

Auf diesem Blatt geht es primär darum, komplexe Probleme erfolgreich anzugehen.
*/

#include "04_canvas.h"
#include <stdio.h>

/*
Nehme eine dreistellige Zahl, sortiere ihre Ziffern absteigend, und subtrahiere von dieser Zahl die Zahl die
sich aus den aufsteigend sortierten Ziffern ergibt.
Wiederhole, bis zwei mal in Folge die gleiche Zahl herauskommt.

Beispiel:

792 ~> 972 - 279 = 693
693 ~> 963 - 369 = 594
594 ~> 954 - 459 = 495
495 ~> 954 - 459 = 495

Gebe in dieser Funktion zurück, wie viele Schritte die dreistellige Eingabezahl 'n' braucht, um bei einer Zahl anzukommen,
bei der die sortiere-und-subtrahiere Prozedur wieder die Zahl selbst ausgibt.

Beispiele: 'kaprekar_count_steps(792) == 3', 'kaprekar_count_steps(693) == 2',
           'kaprekar_count_steps(594) == 1', 'kaprekar_count_steps(495) == 0'

Hinweis: Sollte die Eingabe 'x' kleiner als 100 sein (also weniger als 3 Dezimalstellen besitzen), sollte sie trotzdem
dreistellig behandelt werden, indem Nullen vorangesetzt werden. D.H. 64 ~> 640 - 046 = 594.
*/
int kaprekar_count_steps(int x)
{
    int steps = 0;

    for (;;)
    {
        // Extrahiere die drei Ziffern
        int d1 = x / 100;
        int d2 = (x / 10) % 10;
        int d3 = x % 10;

        // Sortiere Ziffern in aufsteigender Reihenfolge
        int temp;
        if (d1 > d2)
        {
            temp = d1;
            d1 = d2;
            d2 = temp;
        }
        if (d2 > d3)
        {
            temp = d2;
            d2 = d3;
            d3 = temp;
        }
        if (d1 > d2)
        {
            temp = d1;
            d1 = d2;
            d2 = temp;
        }

        // Bilde die aufsteigende und absteigende Zahl
        int asc = d1 * 100 + d2 * 10 + d3;
        int desc = d3 * 100 + d2 * 10 + d1;

        // Berechne die Differenz
        int result = desc - asc;

        // Prüfe, ob wir einen Fixpunkt erreicht haben
        if (result == x)
        {
            return steps;
        }

        x = result;
        steps++;
    }
}

/*
Färbe alle Pixel (mit den Koordinaten '(x, y)') auf dem Canvas schwarz, für welche die sortiere-und-subtrahiere Aktion
von 'x' die Zahl 'y' ergibt.

Bonus: Gibt es ein Muster, dass man ausnutzen kann um 'kaprekar_count_steps' effizienter zu implementieren als
alle Schritte durchzuführen?
*/
Canvas plot_kaprekar(Canvas c)
{
    int width = canvas_width(c);
    int height = canvas_height(c);

    // Iteriere über alle möglichen x-Koordinaten
    for (int x = 0; x < width; x++)
    {
        // Berechne das Kaprekar-Ergebnis für x
        int d1 = x / 100;
        int d2 = (x / 10) % 10;
        int d3 = x % 10;

        // Sortiere Ziffern in aufsteigender Reihenfolge
        int temp;
        if (d1 > d2)
        {
            temp = d1;
            d1 = d2;
            d2 = temp;
        }
        if (d2 > d3)
        {
            temp = d2;
            d2 = d3;
            d3 = temp;
        }
        if (d1 > d2)
        {
            temp = d1;
            d1 = d2;
            d2 = temp;
        }

        // Bilde aufsteigende und absteigende Zahl
        int asc = d1 * 100 + d2 * 10 + d3;
        int desc = d3 * 100 + d2 * 10 + d1;

        // Berechne die Differenz (das Kaprekar-Ergebnis)
        int result = desc - asc;

        // Wenn das Ergebnis innerhalb der Canvas-Höhe liegt, färbe den Pixel schwarz
        if (result >= 0 && result < height)
        {
            c = canvas_set_black(c, x, result);
        }
    }

    return c;
}
