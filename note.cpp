#include <iostream>
#include <string>
#include <ctime>
using namespace std;

int main () {

    int tab[10][10];
    srand(time(NULL));

    for (int i = 0; i < 10; i++) {
        for (int j = 0; j < 10; j++) {
            tab[i][j] = 0;
        }
    }

    int mine = 10;
    int place = 0;

    while (place < mine) {
        int x = rand() % 10;
        int y = rand() % 10;

        if (tab[x][y] != -1) {
            tab[x][y] = -1;
            place++;
        }
    }

    for (int i = 0; i < 10; i++) {
        for (int j =0; j <10; j++) {
            cout << tab[i][j] << " ";
        }
        cout << endl;
    }

    return 0;
}

int GetNumberOfBombs;
void FloodFill(int x, int y, int* Grille, int NbrLignes, int NbrColonnes) {

    if (x < 0 || x >= NbrLignes || y < 0 || y >= NbrColonnes)
        return;

    int INDEX = x * NbrColonnes + y;

    if (Grille[INDEX] != 0)
        return;

    int NumBombs = GetNumberOfBombs(x, y, Grille, NbrLignes, NbrColonnes);

    if (NumBombs > 0) {
        Grille[INDEX] = NumBombs;
        return;
    }

    Grille[INDEX] = -2;
    FloodFill(x + 1, y,     Grille, NbrLignes, NbrColonnes);
    FloodFill(x - 1, y,     Grille, NbrLignes, NbrColonnes);
    FloodFill(x,     y + 1, Grille, NbrLignes, NbrColonnes);
    FloodFill(x,     y - 1, Grille, NbrLignes, NbrColonnes);

    FloodFill(x + 1, y + 1, Grille, NbrLignes, NbrColonnes);
    FloodFill(x - 1, y + 1, Grille, NbrLignes, NbrColonnes);
    FloodFill(x + 1, y - 1, Grille, NbrLignes, NbrColonnes);
    FloodFill(x - 1, y - 1, Grille, NbrLignes, NbrColonnes);
}
