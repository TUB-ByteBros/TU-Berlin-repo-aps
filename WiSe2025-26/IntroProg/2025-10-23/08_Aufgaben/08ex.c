/*
Willkommen zum achten Aufgabenblatt vom Programmierkurs. Auf diesem Aufabenblatt geht es um Pointer und Arrays.

Um die Tests für dieses Blatt zu kompilieren und zu starten, führen Sie den folgenden Befehl aus:
clang -std=c11 -g -Wall 08ex_test.c -o 08ex_test.o -lm && ./08ex_test.o
*/

#include <stdio.h>
#include <stdint.h>
#include <stdbool.h>
#include "turtlecanvas.h"

/*
Aufgabe 1a:
Lesen Sie das Headerfile `turtlecanvas.h`. Diese Funktion soll die Turtle `d` Schritte vorwärts machen lassen.
*/
void turtle_advance_by(TurtleCanvas *c, uint32_t d) {
    for (uint32_t i = 0; i < d; i++) {
        turtle_advance(c);
    }
    return;
}

/*
Aufgabe 1b:
Füllen Sie die Turtlecanvas mit horizontalen, abwechselnd schwarzen und weißen Linien (die unterste Zeile soll
schwarz gefärbt werden). Die Turtle ist anfangs an Position (0, 0), ist nach rechts orientiert, und zeichnet schwarz.
*/
void turtle_stripes(TurtleCanvas *c) {
  size_t height = turtle_canvas_height(c);
  size_t width = turtle_canvas_width(c);

  for (size_t y = 0; y < height; y++) {
    // Zeichne eine ganze Zeile
    turtle_advance_by(c, width);

    // Wenn noch Zeilen übrig sind: zur nächsten Zeile wechseln
    if (y < height - 1) {
      if (y % 2 == 0) {
        // Am Ende einer schwarzen (geraden) Zeile:
        turtle_rotate_left(c);
        turtle_advance(c);
        turtle_rotate_left(c);
      } else {
        // Am Ende einer weißen (ungeraden) Zeile:
        turtle_rotate_right(c);
        turtle_advance(c);
        turtle_rotate_right(c);
      }

      // Farbe umschalten, um nächste Zeile zu zeichnen
      turtle_toggle_color(c);
    }
  }
}


/*
Aufgabe 1c:
Lesen Sie die Implementierungen der Turtlecanvas-Funktionen weiter unten in der "turtlecanvas.h".
Der Quellcode sollte vollständig verständlich und unüberraschend sein.
Hinweis: Diese Aufgabe wird nicht bewertet.
*/

/*
Aufgabe 2a:
Geben Sie einen Pointer auf das erste Vorkommen der größten Zahl im Eingabearray zurück.
*/
uint16_t *find_maximal_number(uint16_t numbers[], size_t numbers_len) {
    uint16_t *max = &numbers[0];
    for (size_t i = 1; i < numbers_len; i++) {
        if (numbers[i] > *max) {
            max = &numbers[i];
        }
    }
    return max;
}

/*
Aufgabe 2b:
Geben Sie (einen Pointer auf) das Teilarray zurück, welches ab dem ersten Vorkommen der größten Zahl im Eingabearray beginnt.
*/
uint16_t *find_subarray_starting_at_maximal_number(uint16_t numbers[], size_t numbers_len) {
    return find_maximal_number(numbers, numbers_len);
}

/*
Aufgabe 2c:
Geben Sie die größtmögliche Distanz zwischen zwei Zahlenwerten aus dem Array `numbers` zurück.
Beispiel: Im Array {1, 3, 7, 4} ist die größte Distanz die zwischen 1 und 7, und beträgt damit `6`.
*/
uint16_t find_maximum_distance(uint16_t numbers[], size_t numbers_len) {
    uint16_t distance = UINT16_MAX;
    uint16_t min =numbers[0];
    uint16_t max = numbers[0];
    for (size_t i = 1; i < numbers_len; i++) {
        if (numbers[i] < min) {
            min = numbers[i];
        }
        if (numbers[i] > max) {
            max = numbers[i];
        }
    }
    distance = max - min;


    return distance;
}

/*
Aufgabe 2d:
Geben Sie die kleinstmögliche Distanz zwischen zwei Zahlenwerten aus dem Array `numbers` zurück.
Beispiel: Im Array {1, 3, 7, 4} ist die kleinste Distanz die zwischen 3 und 4, und beträgt damit `1`.
*/
uint16_t find_minimum_distance(uint16_t numbers[], size_t numbers_len) {
    uint16_t min_distance = UINT16_MAX;
    for (size_t i = 0; i < numbers_len; i++) {
        for (size_t j = i + 1; j < numbers_len; j++) {
            uint16_t distance = (numbers[i] > numbers[j]) ? (numbers[i] - numbers[j]) : (numbers[j] - numbers[i]);
            if (distance < min_distance) {
                min_distance = distance;
            }
        }
    }
    return min_distance;
}

/*
Aufgabe 2e:
Schreiben Sie die ersten `numbers_len` Quadratzahlen aufsteigend in das gegebene Array `numbers`.
Hinweis: Wir starten bei `1`. Sollte numbers_len also `5` sein, sind die ersten 5 Quadratzahlen bis
einschließlich die von 5 gemeint: 1, 4, 9, 16, 25.
*/
void square_ascending(uint16_t numbers[], size_t numbers_len) {
    for (size_t i = 1; i <= numbers_len; i++) {
        numbers[i-1] = (i) * (i);
    }
    return;
}

/*
Aufgabe 2f:
Füllen Sie das Array `out` mit den aufsteigend sortierten Zahlen aus dem `in` Array. Beide Arrays haben die Länge `len`.
Beispiel: Ist `in` {1, 4, 3, 7, 4}, so soll `out` am Ende {1, 3, 4, 4, 7} sein.
*/
void sort_ascending(uint16_t in[], uint16_t out[], size_t len) {
    uint16_t temp[len];
    for (size_t i = 0; i < len; i++) {
        temp[i] = in[i];
    }
    for (size_t i = 0; i < len - 1; i++) {
        for (size_t j = 0; j < len - i - 1; j++) {
            if (temp[j] > temp[j + 1]) {
                uint16_t swap = temp[j];
                temp[j] = temp[j + 1];
                temp[j + 1] = swap;
            }
        }
    }
    for (size_t i = 0; i < len; i++) {
        out[i] = temp[i];
    }

    return;
}
