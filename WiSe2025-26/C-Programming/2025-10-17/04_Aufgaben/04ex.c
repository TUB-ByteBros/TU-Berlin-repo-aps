/*
Willkommen zum vierten Aufgabenblatt vom Programmierkurs. Auf diesem Aufabenblatt geht es darum, ein komplizierteres Problem wiederholt in Teilprobleme zu zerlegen.

Um die Tests für dieses Blatt zu kompilieren und zu starten, führen Sie den folgenden Befehl aus:
clang -std=c11 -g -Wall 04ex_test.c 04ex_helpers.c -o 04ex_test.o -lm && ./04ex_test.o
*/

#include "04_canvas.h"
#include "04ex_helpers.c"
#include "04ex_helpers.h"
#include <assert.h>
#include <stdio.h>

/*
Aufgabe 1a:
In diesem Aufgabenblatt schreiben wir eine Funktion, um auf der Canvas gefüllte Kreise zu zeichnen. Kreise sind konzeptionell einfach:
Haben wir einen Mittelpunkt und einen Radius, können wir alle Punkte schwarz färben, deren Distanz zum
Mittelpunkt kleiner oder gleich des Radius ist.

Für diese Aufgabe, implementieren Sie eine Funktion die genau das tut. Gegeben sind die Koordinaten `x` und `y` des
Mittelpixels und ein Radius. Nun sollen alle Pixel, die innerhalb der Distanz um diesen Mittelpixel liegen schwarz
gefärbt werden. Durch diese Methode entstehen immer Kreise mit ungeradem Durchmesser, da wir mit diskreten Pixeln arbeiten.
Der Mittelpixel hat eine Distanz von 0 zu sich selbst, und daher muss er immer schwarz gefärbt werden, selbst bei Radius 0.
Nutzen Sie für die Distanzbestimmung die `distance` Funktion aus `04ex_helpers.h`.
Headerfile und die zugehörige Implementierung sind bereits eingebunden, die Funktion kann
also einfach verwendet werden.
*/
Canvas draw_odd_circle(Canvas c, int x, int y, int radius_from_middle)
{
    // Get canvas dimensions
    int width = canvas_width(c);
    int height = canvas_height(c);

    // Iterate through a square area around the center
    for (int current_x = x - radius_from_middle; current_x <= x + radius_from_middle; current_x++)
    {
        for (int current_y = y - radius_from_middle; current_y <= y + radius_from_middle; current_y++)
        {
            // Check if the current position is within the canvas bounds
            if (current_x >= 0 && current_x < width && current_y >= 0 && current_y < height)
            {
                // Calculate the distance from the center
                int dist = distance(x, y, current_x, current_y);

                // If the distance is less than or equal to the radius, set the pixel to black
                if (dist <= radius_from_middle)
                {
                    c = canvas_set_black(c, current_x, current_y);
                }
            }
        }
    }

    return c;
}

/*
Aufgabe 1b:
Implementieren Sie nun selbst eine Funktion, welche die abgerundete Distanz zwischen zwei Punkten (`x0`, `y0`)
und (`x1`, `y1`) berechnet.
Sei `a := x1 - x0` und `b := y1 - y0`. Dann liefert uns der Satz des Pythagoras die Distanz zwischen den Punkten als
`c := quadratwurzel(a^2 + b^2)`.
Die Datei `04ex_helpers.h` mit den Hilsfunktionen enthält eine Funktion `squareroot`. Nutzen Sie diese Funktion, um die
Distanz zu berechnen.
*/
int my_distance(int x0, int y0, int x1, int y1)
{
    // Calculate a = x1 - x0
    int a = x1 - x0;

    // Calculate b = y1 - y0
    int b = y1 - y0;

    // Calculate a^2 + b^2
    int sum_of_squares = a * a + b * b;

    // Calculate the square root using the provided function
    int distance = squareroot(sum_of_squares);

    return distance;
}

int my_squareroot(int n)
{
    // Handle special cases
    if (n <= 1)
    {
        return n;
    }

    // Find largest integer i where i*i <= n
    int i = 1;
    while (i * i <= n)
    {
        i++;
    }

    // Return the integer whose square is less than or equal to n
    return i - 1;
}

/*
Aufgabe 1d:
Die Kreisfunktion aus Aufgabe 1a erstellt immer nur Kreise mit ungeradem Durchmesser. Kreise mit einem
geraden Durchmesser haben keinen einzelnen Mittelpixel, demnach benötigen wir eine flexiblere Kreis-Zeichnungs Funktion
mit anderen Parametern, um diese Kreise zeichnen zu können.
`x` ist die x-Koordinate der linkesten Pixel des Kreises, `y` ist die y-koordinate der untersten Pixel des Kreises,
`diameter` ist der Durchmesser. Dadurch ist `(x,y)` die Koordinate der unteren linken Ecke des kleinsten Quadrats (der
Länge und Breite `diameter`) welches den erwünschten Kreis vollständig enthält.

Um Kreise mit _ungeradem_ Durchmesser zu erstellen, können Sie einfach Ihre `draw_odd_circle` Funktion ein mal aufrufen.
Für Kreise mit _geradem_ Durchmesser rufen Sie Ihre `draw_odd_circle` vier mal auf: Einmal für jeden der vier Pixel
welche den exakten Mittelpunkt des erwünschten Kreises umgeben.
*/
Canvas draw_circle(Canvas c, int x, int y, int diameter)
{
    // Check if diameter is odd or even
    if (diameter % 2 == 1)
    {
        // For odd diameter: call draw_odd_circle once with the middle pixel as center
        int center_x = x + diameter / 2;
        int center_y = y + diameter / 2;
        int radius = diameter / 2;
        c = draw_odd_circle(c, center_x, center_y, radius);
    }
    else
    {
        // For even diameter: call draw_odd_circle four times, once for each of the
        // four pixels surrounding the center
        int half_diameter = diameter / 2;
        int radius = half_diameter - 1;

        // Top right pixel
        c = draw_odd_circle(c, x + half_diameter, y + half_diameter, radius);

        // Top left pixel
        c = draw_odd_circle(c, x + half_diameter - 1, y + half_diameter, radius);

        // Bottom right pixel
        c = draw_odd_circle(c, x + half_diameter, y + half_diameter - 1, radius);

        // Bottom left pixel
        c = draw_odd_circle(c, x + half_diameter - 1, y + half_diameter - 1, radius);
    }

    return c;
}

/*
Aufgabe 1e:
Dadurch, dass Sie das Problem in kleinere Subprobleme geteilt haben, haben Sie gerade eine vollständige Funktion zum
Kreisezeichnen implementiert. Das ist ziemlich cool!
Geben Sie zur Feier `5` zurück.
*/
int high_five()
{
    return 5;
}

/*
Aufgabe 2a:
Gegeben sei eine natürliche Zahl `n`. Falls sie gerade ist, teilen Sie sie durch zwei, ansonsten multiplizieren Sie sie
mit drei und addieren eins. Wiederholen Sie dies bis Sie als Ergebnis die Zahl `1` erreichen. Die Anzahl Wiederholungen
die Sie dafür benötigen ist die _Hailstone-Zahl von `n`_.
Zum Beispiel `hailstone(1) == 0`, `hailstone(4) == 2` (4 -> 2 -> 1), und `hailstone(5) == 5` (5 -> 16 -> 8 -> 4 -> 2 -> 1).
Berechnen Sie die Hailstone-Zahl vom Parameter `n`.
*/
int hailstone(int n)
{
    // Count number of steps
    int steps = 0;

    // Continue until we reach 1
    while (n > 1)
    {
        // If n is even, divide by 2
        if (n % 2 == 0)
        {
            n = n / 2;
        }
        // If n is odd, multiply by 3 and add 1
        else
        {
            n = 3 * n + 1;
        }

        // Increment step count
        steps++;
    }

    return steps;
}

/*
Aufgabe 2b:
Unser Testrunner hat keine Tests für Aufgabe 2a. Falls Sie Ihre Lösung selber testen wollen, erstellen Sie am besten
eine separate C-Datei wo Sie Ihre Lösung hineinkopieren und gegen einige Beispielwerte testen.
Falls Sie keine Beispielwerte von Hand berechnen wollen, schauen Sie am besten hier nach:  https://oeis.org/A006577

Für die _Bewertung_ von diesem Aufgabenblatt lassen wir Tests für Aufgabe 2a laufen, zum Debuggen müssen Sie
allerdings Ihre eigenen Tests schreiben.
Lassen Sie `99` von dieser Funktion zurückgeben um zu zeigen, dass Sie das verstanden haben.
*/
int bring_your_own_tests()
{
    printf("hailstone(7) = %d\n", hailstone(7)); // Expected: 16
    assert(hailstone(7) == 16);
    return 99;
}
