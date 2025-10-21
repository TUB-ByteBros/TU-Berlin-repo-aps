/*
Willkommen zum zweiten Übungsblatt vom Programmierkurs. Alles funktioniert wie auch beim ersten Aufgabenblatt.

Nachdem Sie in einem Terminal mittels des 'cd' Befehls in das Verzeichnis gewechselt sind, in dem diese Datei liegt,
können Sie mit folgendem Befehl ihre Lösungen überprüfen:
clang -std=c11 -g -Wall 02practice_test.c -o 02practice_test.o -lm && ./02practice_test.o

Auf diesem Blatt geht es unter anderem um:

- if, else und else-if
- logisches und und logisches oder (`&&` und `||`)
- verschachtelte while und for loops
*/

#include <stdio.h>

int is_prime(int n)
{
    int result = 0;
    /*
    Eine Primzahl ist eine natürliche Zahl größer gleich 2, deren einzigen ganzzahligen Teiler die eins und die Zahl selbst sind.
    Die ersten Primzahlen sind 2, 3, 5, 7, 11, 13, ...

    Weisen Sie der Variable `result` den Wert `1` zu, falls `n` eine Primzahl ist, und ansonsten `0`.
    */
    /* BEGIN CHANGES */
    if (n < 2)
    {
        result = 0; // Zahlen kleiner als 2 sind keine Primzahlen
    }
    else if (n == 2)
    {
        result = 1; // 2 ist eine Primzahl
    }
    else if (n % 2 == 0)
    {
        result = 0; // Gerade Zahlen größer 2 sind keine Primzahlen
    }
    else
    {
        result = 1; // Annahme: n ist eine Primzahl, bis ein Teiler gefunden wird
        for (int i = 3; i * i <= n; i += 2)
        {
            if (n % i == 0)
            {
                result = 0; // Teiler gefunden, keine Primzahl
                break;
            }
        }
    }
    /* END CHANGES */
    return result;
}

int sum_first_primes(int n)
{
    int result = 0;
    /*
    Weisen Sie der Variable `result` die Summe der ersten `n` Primzahlen zu zu.
    Beispiel für `n = 4`: `2 + 3 + 5 + 7 = 17`.
    */
    /* BEGIN CHANGES */
    int count = 0; // Counter for prime numbers found
    int num = 2;   // Start checking from 2

    while (count < n)
    {
        if (is_prime(num))
        {
            result += num;
            count++;
        }
        num++;
    }
    /* END CHANGES */
    return result;
}

int sum_first_powers(int n)
{
    int result = 0;
    /*
    Sum First Powers:
    Weisen Sie der Variable `result` die Summe `n^0 + n^1 + n^2 + n^3 + ... + n^n` zu.
    Beispiel für `n = 4`: `4^0 + 4^1 + 4^2 + 4^3 + 4^4 = 1 + 4 + 16 + 64 + 256 = 341`.
    */
    /* BEGIN CHANGES */
    int power = 1; // Start with n^0 = 1

    for (int i = 0; i <= n; i++)
    {
        result += power;
        power *= n; // Multiply by n for the next iteration
    }
    /* END CHANGES */
    return result;
}

/*
Schreiben Sie ein paar nette Muster ins Terminal.


Muster 1: k-square (im Beispiel unten ist k := 8)

########
########
########
########
########
########
########
########

Muster 2: k-diagonal (im Beispiel unten ist k := 8)

#
##
###
####
#####
######
#######
########

Muster 3: k-arrow (im Beispiel unten ist k := 8)

#
##
###
####
####
###
##
#

Muster 4: k-chessboard (im Beispiel unten ist k := 8)

 # # # #
# # # #
 # # # #
# # # #
 # # # #
# # # #
 # # # #
# # # #

Muster 5: k-pyramid (im Beispiel unten ist k := 8)

   ##
  ####
 ######
########

Muster 6: k-spiral (im Beispiel unten ist k := 16)

################
               #
############## #
#            # #
# ########## # #
# #        # # #
# # ###### # # #
# # # ## # # # #
# # # #  # # # #
# # # #### # # #
# # #      # # #
# # ######## # #
# #          # #
# ############ #
#              #
################



*/
void k_square(int k)
{
    // Muster 1: k-square
    for (int i = 0; i < k; i++)
    {
        for (int j = 0; j < k; j++)
        {
            printf("#");
        }
        printf("\n");
    }
}

void k_diagonal(int k)
{
    // Muster 2: k-diagonal
    for (int i = 1; i <= k; i++)
    {
        for (int j = 0; j < i; j++)
        {
            printf("#");
        }
        printf("\n");
    }
}

void k_arrow(int k)
{
    // Muster 3: k-arrow
    // First half - increasing
    for (int i = 1; i <= k / 2; i++)
    {
        for (int j = 0; j < i; j++)
        {
            printf("#");
        }
        printf("\n");
    }
    // Second half - decreasing
    for (int i = k / 2; i >= 1; i--)
    {
        for (int j = 0; j < i; j++)
        {
            printf("#");
        }
        printf("\n");
    }
}

void k_chessboard(int k)
{
    // Muster 4: k-chessboard
    for (int i = 0; i < k; i++)
    {
        // Odd rows start with space, even rows start with #
        char start = (i % 2 == 0) ? ' ' : '#';

        for (int j = 0; j < k; j++)
        {
            printf("%c", (j % 2 == 0) ? start : (start == '#' ? ' ' : '#'));
        }
        printf("\n");
    }
}

void k_pyramid(int k)
{
    // Muster 5: k-pyramid
    for (int i = 1; i <= k / 2; i++)
    {
        // Print spaces
        for (int j = 0; j < k / 2 - i; j++)
        {
            printf(" ");
        }
        // Print #'s
        for (int j = 0; j < i * 2; j++)
        {
            printf("#");
        }
        printf("\n");
    }
}

void k_spiral(int k)
{
    // Muster 6: k-spiral
    // This requires a more complex algorithm
    // Create a 2D array to track visited cells
    int grid[k][k];
    for (int i = 0; i < k; i++)
    {
        for (int j = 0; j < k; j++)
        {
            grid[i][j] = 0; // 0 means unvisited
        }
    }

    // Direction vectors for right, down, left, up
    int dr[] = {0, 1, 0, -1};
    int dc[] = {1, 0, -1, 0};

    int r = 0, c = 0, dir = 0;

    // Mark boundaries with '#'
    for (int i = 0; i < k * k; i++)
    {
        grid[r][c] = 1; // Mark as visited

        // Calculate next position
        int nr = r + dr[dir];
        int nc = c + dc[dir];

        // Change direction if necessary
        if (nr < 0 || nr >= k || nc < 0 || nc >= k || grid[nr][nc] == 1)
        {
            dir = (dir + 1) % 4; // Turn 90 degrees
            nr = r + dr[dir];
            nc = c + dc[dir];
        }

        r = nr;
        c = nc;
    }

    // Print the spiral
    for (int i = 0; i < k; i++)
    {
        for (int j = 0; j < k; j++)
        {
            if (i == 0 || i == k - 1 || j == 0 || j == k - 1 || grid[i][j] == 1)
            {
                printf("#");
            }
            else
            {
                printf(" ");
            }
        }
        printf("\n");
    }
}