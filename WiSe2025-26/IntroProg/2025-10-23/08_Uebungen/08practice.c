/*
Willkommen zum achten Übungsblatt vom Programmierkurs.

Nachdem Sie in einem Terminal mittels des `cd` Befehls in das Verzeichnis gewechselt sind, in dem diese Datei liegt,
können Sie mit folgendem Befehl ihre Lösungen überprüfen:
clang -std=c11 -g -Wall 08practice_test.c -o 08practice_test.o -lm && ./08practice_test.o

Auf diesem Blatt geht es um Arrays.
*/

#include <stdio.h>
#include <stdint.h>
#include <stdbool.h>
#include <math.h>

/*
Geben Sie die kleinste Zahl im Eingabearray zurück.
*/
uint16_t get_minimum(uint16_t numbers[], size_t numbers_len) {
    uint16_t min = numbers[0];
    for (size_t i = 1; i < numbers_len; i++) {
        if (numbers[i] < min) {
            min = numbers[i];
        }
    }
    return min;
}

/*
Geben Sie einen Pointer auf das erste Vorkommen der Zahl `7` im Eingabearray zurück, oder `NULL` falls die `7`
nicht vorkommt.
*/
uint16_t *find_seven(uint16_t numbers[], size_t numbers_len) {
    for (size_t i = 0; i < numbers_len; i++) {
        if (numbers[i] == 7) {
            return &numbers[i];
        }
    }
    return NULL;
}

/*
Schreiben Sie einen Countdown in das gegebene Array `numbers`.
Bespiel: ist `numbers_len` drei, sollte das Array am Ende die Werte 2, 1, und 0 enthalten (in dieser Reihenfolge).
*/
void countdown(uint16_t numbers[], size_t numbers_len) {
   for (size_t i = 0; i  < numbers_len; i++) {
        numbers[i] = numbers_len - 1 - i;
}
    return;
}

/*
Wir können zweidimensionale Arrays bequem als eindimensionale Arrays darstellen, indem wir
die Zellen durchnummerieren.
Beispiel:

+-+-+-+
|3|4|5|            +-+-+-+-+-+-+
+-+-+-+ entspricht |0|1|2|3|4|5|
|0|1|2|            +-+-+-+-+-+-+
+-+-+-+

Wie können zweidimensionale Koordinaten in eindimensionale Koordinaten umgerechnet werden?
z.B. addressiert die 2d-Koordinate (0, 0) die Zelle 0, (1, 0) addressiert Zelle 1, (2, 0) Zelle 2, (0, 1) Zelle 3,
(1, 1) Zelle 4, und (2, 1) Zelle 5.

Diese Funktion erhält ein eindimensionales Array `arr`, welches ein 2d Array der Breite `width` und Höhe `height`
repräsentiert.
Geben Sie den Wert an der Koordinate (x, y) zurück.
*/
uint16_t get_value(uint16_t arr[], size_t width, size_t height, size_t x, size_t y) {
    return arr[y * width + x];
}

/*
Ein _lateinisches Quadrat_ ist ein Quadrat, in dem jeder Wert innerhalb seiner Zeile und seiner Spalte nur ein mal vorkommt.
Ist das gegebene Array `arr` ein lateinisches Quadrat der Seitenlängen `length`?
Hinweis: die Transformation ins Zweidimensionale ist wie in der Voraufgabe.
*/
bool is_latin_square(int *array, size_t n) {
  if (n == 0) return false;
  if (n == 1) return true;

  // √n = Seitenlänge
  size_t size = (size_t)sqrt((double)n);
  if (size * size != n)
    return false; // Kein echtes Quadrat

  // Zeilen prüfen
  for (size_t y = 0; y < size; y++) {
    for (size_t x1 = 0; x1 < size; x1++) {
      int val = array[y * size + x1];

      if (val < 1 || val > (int)size * (int)size)
        return false;

      // Doppelte in Zeile?
      for (size_t x2 = x1 + 1; x2 < size; x2++) {
        if (val == array[y * size + x2])
          return false;
      }
    }
  }

  // Spalten prüfen
  for (size_t x = 0; x < size; x++) {
    for (size_t y1 = 0; y1 < size; y1++) {
      int val = array[y1 * size + x];
      for (size_t y2 = y1 + 1; y2 < size; y2++) {
        if (val == array[y2 * size + x])
          return false;
      }
    }
  }

  return true;
}

/*
Ein _magisches Quadrat_ ist ein Quadrat, in dem die Summe der Werte in jeder Zeile, Spalte, und der beiden großen
Diagonalen, identisch ist.
Ist das gegebene Array `arr` ein magisches Quadrat der Seitenlängen `length`?
Hinweis: die Transformation ins Zweidimensionale ist wie in der Voraufgabe.
*/
bool is_magic_square(uint16_t arr[], size_t length) {
  // Berechne die erwartete Summe aus der ersten Zeile
  uint32_t expected_sum = 0;
  for (size_t j = 0; j < length; j++) {
    expected_sum += arr[j];
  }

  // Überprüfe alle Zeilen
  for (size_t i = 0; i < length; i++) {
    uint32_t row_sum = 0;
    for (size_t j = 0; j < length; j++) {
      row_sum += arr[i * length + j];
    }
    if (row_sum != expected_sum) {
      return false;
    }
  }

  // Überprüfe alle Spalten
  for (size_t j = 0; j < length; j++) {
    uint32_t col_sum = 0;
    for (size_t i = 0; i < length; i++) {
      col_sum += arr[i * length + j];
    }
    if (col_sum != expected_sum) {
      return false;
    }
  }

  // Überprüfe die Hauptdiagonale (von oben links nach unten rechts)
  uint32_t diag1_sum = 0;
  for (size_t i = 0; i < length; i++) {
    diag1_sum += arr[i * length + i];
  }
  if (diag1_sum != expected_sum) {
    return false;
  }

  // Überprüfe die Nebendiagonale (von oben rechts nach unten links)
  uint32_t diag2_sum = 0;
  for (size_t i = 0; i < length; i++) {
    diag2_sum += arr[i * length + (length - 1 - i)];
  }
  if (diag2_sum != expected_sum) {
    return false;
  }

  return true;
}